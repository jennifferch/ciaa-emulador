const fs = require('fs');
const Path = require('path');
const { exists, getAllDirectories, getAllCFiles } = require('./util');
const helpers = require('./util');
const libc = require('./build-libc');
const EventEmitter = require('events');
const promisify = require('es6-promisify').promisify;

let findPeripherals = async function() {
    let dirs  = await libc.getAllDirectories();

    let hal = [];
    let ui = [];

    // iterate over hal folders
    for (let d of dirs.filter(d => Path.basename(d) === 'js-hal')) {
        // read all files that end with js and add them
        hal = hal.concat((await promisify(fs.readdir)(d)).filter(f => /\.js$/.test(f)).map(f => Path.join(d, f)));
    }

    // iterate over ui folders
    for (let d of dirs.filter(d => Path.basename(d) === 'js-ui')) {
        // read all files that end with js and add them
        ui = ui.concat((await promisify(fs.readdir)(d)).filter(f => /\.js$/.test(f)).map(f => Path.join(d, f)));
    }

    // get relative to root
    hal = hal.map(f => Path.relative(Path.join(__dirname, '..'), f));
    ui = ui.map(f => Path.relative(Path.join(__dirname, '..'), f));

    return {
        hal: hal,
        ui: ui
    };
};

let build = async function(outFile, extraArgs, emterpretify, verbose, includeDirectories, cFiles, peripherals, componentFiles, disableTlsNullEntropy) {
    let componentsOutName = Path.join(Path.dirname(outFile), Path.basename(outFile) + '.components');

    let builtinPeripherals = await findPeripherals();
    let components = {
        jshal: builtinPeripherals.hal.concat(componentFiles.jshal || []),
        jsui: builtinPeripherals.ui.concat(componentFiles.jsui || []),
        peripherals: peripherals
    };

    let args = cFiles
        .concat(includeDirectories.map(i => '-I' + i))
        .concat(helpers.defaultBuildFlags)
        .concat(extraArgs)
        .concat([
            '-o', outFile
        ]);

    if (!disableTlsNullEntropy) {
        args = args.concat([
            '-DMBEDTLS_TEST_NULL_ENTROPY',
            '-DMBEDTLS_NO_DEFAULT_ENTROPY_SOURCES',
        ]);
    }

    if (emterpretify) {
        args = args.concat(helpers.emterpretifyFlags);
    }
    else {
        args = args.concat(helpers.nonEmterpretifyFlags);
    }

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
                fs.writeFile(componentsOutName, JSON.stringify(components, null, 4), 'utf-8', function(err) {
                    if (err) return reject(err);

                    resolve(outFile);
                });
            }
            else {
                reject('Application failed to build (' + code + ')\n' + stdout);
            }
        });
    });
}

let buildDirectory = async function (inputDir, outFile, extraArgs, emterpretify, verbose) {
    inputDir = Path.resolve(inputDir);
    outFile = Path.resolve(outFile);

    console.log("buildDirectory inputDir ",inputDir);
    console.log("buildDirectory outFile ",outFile);

    let includeDirectories = (await getAllDirectories(inputDir)).concat(await libc.getAllDirectories()).map(c => Path.resolve(c));;
    let cFiles = [ libc.getPath() ].concat(await getAllCFiles(inputDir)).map(c => Path.resolve(c));

    let emuladorconfig = await exists(Path.join(inputDir, 'emuladorconfig.json'))
                        ? JSON.parse(await promisify(fs.readFile)(Path.join(inputDir, 'emuladorconfig.json')))
                        : {};

    console.log("configuracion emulador antes ",emuladorconfig);

    emuladorconfig['compiler-args'] = emuladorconfig['compiler-args'] || [];

    console.log("configuracion emulador despues ",emuladorconfig);

    console.log("configuracion emulador emterpretify ",emuladorconfig.emterpretify);

    if (emuladorconfig.emterpretify) {
        emterpretify = true;
    }

    let toRemove = [
        'BUILD'
    ].map(d => Path.join(inputDir, d) + Path.sep);

    toRemove = toRemove.concat((emuladorconfig.ignore || []).map(f => {
        return Path.join(inputDir, f);
    }));

    console.log("eliminar ",toRemove);
    includeDirectories = includeDirectories.map(d => d + Path.sep);

    includeDirectories = includeDirectories.filter(d => !toRemove.some(r => d.indexOf(r) !== -1));
    console.log("directorios incluidos ",includeDirectories);

    cFiles = cFiles.filter(d => !toRemove.some(r => d.indexOf(r) !== -1));
    console.log("cFiles ",cFiles);

    extraArgs = extraArgs
                    .concat(emuladorconfig['compiler-args']);

    console.log("argumentos ",extraArgs);

    let copyComponents = async function (fileList, postfix) {
        let files = fileList.map(f => Path.join(inputDir, f));

        console.log("componentes ", files);
        let targetFolder = Path.join(Path.dirname(outFile), Path.basename(outFile, '.js') + postfix);
        console.log("archivos incluidos en targetFolder ", targetFolder);

        let outFiles = [];

        if (!(await exists(targetFolder))) {
            await promisify(fs.mkdir)(targetFolder);
        }
        for (let f of files) {
            let target = Path.join(targetFolder, Path.basename(f));
            await promisify(fs.copyFile)(f, target);
            outFiles.push(Path.relative(Path.dirname(outFile), target));
        }
        return outFiles;
    }
    let jshal = [];
    let jsui = [];
    if (emuladorconfig.components && emuladorconfig.components.jshal) {
        jshal = await copyComponents(emuladorconfig.components.jshal, '-jshal');
    }
    if (emuladorconfig.components && emuladorconfig.components.jsui) {
        jsui = await copyComponents(emuladorconfig.components.jsui, '-jsui');
    }

    console.log("jshal ", jshal);
    console.log("jsui ", jsui);

    return build(outFile,
                 extraArgs,
                 emterpretify,
                 verbose,
                 includeDirectories,
                 cFiles,
                 emuladorconfig.peripherals || [],
                 { jshal: jshal, jsui: jsui },
                 emuladorconfig.disableTlsNullEntropy);
}

let buildFile = async function(inputFile, outFile, extraArgs, emterpretify, verbose) {
    inputFile = Path.resolve(inputFile);
    outFile = Path.resolve(outFile);

    let includeDirectories = [ Path.dirname(inputFile) ].concat(await libc.getAllDirectories()).map(c => Path.resolve(c));;
    let cFiles = [ libc.getPath(), inputFile ].map(c => Path.resolve(c));

    return build(outFile, extraArgs, emterpretify, verbose, includeDirectories, cFiles, [], {});
}

module.exports = {
    _build: async function(buildFn, input, outFile, extraArgs, emterpretify, verbose) {
        if (!await libc.exists()) {
            console.log('libc.bc no existe. Building...');
            await libc.build(verbose);
        }

        await buildFn(input, outFile, extraArgs, emterpretify, verbose);
    },

    buildDirectory: function(inputDir, outFile, extraArgs, emterpretify, verbose) {
        return module.exports._build(buildDirectory, inputDir, outFile, extraArgs, emterpretify, verbose);
    },

    buildFile: function(inputFile, outFile, extraArgs, emterpretify, verbose) {
        return module.exports._build(buildFile, inputFile, outFile, extraArgs, emterpretify, verbose);
    }
};
