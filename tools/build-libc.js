const fs = require('fs');
const Path = require('path');
const spawn = require('child_process').spawn;
const { exists, getAllDirectories, getAllCFiles, ignoreAndFilter } = require('./util');
const helpers = require('./util');
const EventEmitter = require('events');
const commandExists = require('command-exists');
const promisify = require('es6-promisify').promisify;

const outFolder = Path.join(__dirname, '..', 'hal');
const outFile = Path.resolve(Path.join(outFolder, 'libc.bc')); 
const ignoreFile = Path.join(outFolder, '.ignore');


let libc = {
    getAllDirectories: async function() {
        let cacheFile = Path.join(outFolder, 'directories.cache');

        if (await exists(cacheFile)) {
            return JSON.parse(await promisify(fs.readFile)(cacheFile), 'utf-8');
        }

        let dirs = await ignoreAndFilter(await getAllDirectories(outFolder), ignoreFile);


        dirs = dirs.sort((a, b) => b.length - a.length);

        let dirsToRemove = []; 
        for (let d of dirs) {
            let hasHeaderFiles = (await promisify(fs.readdir)(d)).some(f => ['.h', '.js'].indexOf(Path.extname(f)) > -1);
            let hasChildren = dirs.filter(sd => sd !== d && sd.indexOf(d) > -1 && dirsToRemove.indexOf(sd) === -1).length > 0;

            if (!hasHeaderFiles && !hasChildren) {
                dirsToRemove.push(d);
            }
        }

        dirs = dirs.filter(d => dirsToRemove.indexOf(d) === -1);
        await promisify(fs.writeFile)(cacheFile, JSON.stringify(dirs), 'utf-8');
        return dirs;
    },

    getAllCFiles: async function() {
        let cacheFile = Path.join(outFolder, 'cfiles.cache');
        console.log("cacheFile ", cacheFile);

        if (await exists(cacheFile)) {
            return JSON.parse(await promisify(fs.readFile)(cacheFile), 'utf-8');
        }

        let dirs = await ignoreAndFilter(await getAllCFiles(outFolder), ignoreFile);
        await promisify(fs.writeFile)(cacheFile, JSON.stringify(dirs), 'utf-8');
        return dirs;
    },

    getPath: function() {
        return outFile;
    },

    exists: function() {
        return exists(outFile);
    },

    deploy: async function() {
        let cacheFile = Path.join(outFolder, 'deploy.cache');

        if (await exists(cacheFile)) {
            return;
        }

        return new Promise((resolve, reject) => {

            let stdout = '';
            let cmd = spawn('mbed', [ 'deploy' ], { cwd: Path.join(__dirname, '..') });

            cmd.stdout.on('data', data => stdout += data.toString('utf-8'));
            cmd.stderr.on('data', data => stdout += data.toString('utf-8'));

            cmd.on('close', code => {
                if (code === 0) {
                    fs.writeFile(cacheFile, stdout, 'utf-8', function(err) {
                        if (err) return reject(err);
                        resolve(null);
                    });
                }
                else {
                    return reject('No se pudo ejecutar `mbed deploy` (' + code + ')\n' + stdout);
                }
            });
        });
    },

    checkDependencies: async function() {
        try {
            await commandExists('emcc');
        }
        catch (ex) {
            throw 'Emscripten (emcc) no se encuentra instalado. https://kripken.github.io/emscripten-site/docs/getting_started/downloads.html';
        }
    },

    build: async function(verbose) {
        await this.checkDependencies();

        let cacheFiles = [
            Path.join(outFolder, 'directories.cache'),
            Path.join(outFolder, 'cfiles.cache')
        ];
        await Promise.all(cacheFiles.map(async function(c) {
            if (await(exists(c))) {
                promisify(fs.unlink)(c);
            }
        }));

        await this.deploy();

        let includeDirectories = await this.getAllDirectories();
        let cFiles = await this.getAllCFiles();
        let emterpretify = false; // no need for this yet

        let args = cFiles
            .concat(includeDirectories.map(i => '-I' + i))
            .concat(helpers.defaultBuildFlags)
            .concat([
                '-DMBEDTLS_TEST_NULL_ENTROPY',
                '-DMBEDTLS_NO_DEFAULT_ENTROPY_SOURCES',

                '-O2',
                '-o', outFile
            ]);

        if (emterpretify) {
            args = args.concat(helpers.emterpretifyFlags);
        }
        else {
            args = args.concat(helpers.nonEmterpretifyFlags);
        }

        args = args.filter(a => a !== '--emterpretify');

        if (verbose) {
            console.log(helpers.emccCmd + ' ' + args.join(' '));
            args.push('-v');
        }

        let cmd = await helpers.spawnEmcc(args);

        return new Promise((resolve, reject) => {
            let stdout = '';

            cmd.stdout.on('data', data => stdout += data.toString('utf-8'));
            cmd.stderr.on('data', data => stdout += data.toString('utf-8'));

            cmd.on('close', code => {
                if (code === 0) {
                    return resolve();
                }
                else {
                    return reject('Fallo libc (' + code + ')\n' + stdout);
                }
            });
        });
    }
};

module.exports = libc;