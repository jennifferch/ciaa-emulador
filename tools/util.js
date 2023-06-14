const fs = require('fs');
const Path = require('path');
const promisify = require('es6-promisify').promisify;
const spawn = require('child_process').spawn;
const os = require('os');
const crypto = require('crypto');
const emccCmd = process.platform === 'win32' ? 'emcc.bat' : 'emcc';

const exists = function(path) {
    return new Promise((resolve, reject) => {
        fs.exists(path, function(v) {
            resolve(v);
        });
    });
};

const isDirectory = async function(source) {
    return (await promisify(fs.lstat)(source)).isDirectory();
};

const getDirectories = async function(source) {
    let children = await promisify(fs.readdir)(source);

    let res = [];

    for (let d of children) {
        d = Path.join(source, d);
        if (!await isDirectory(d)) continue;
        res.push(d);
    }

    return res;
};

const getCFiles = async function(source) {
    console.log("source:::::", source);
    return (await promisify(fs.readdir)(source))
        .map(name => Path.join(source, name))
        .filter(name => ['.c', '.cpp'].indexOf(Path.extname(name).toLowerCase()) > -1);
};

const getAllDirectories = async function(source) {
    let dirs = [ Path.resolve(source) + Path.sep ];
    for (let d of await getDirectories(source)) {
        dirs = dirs.concat(await getAllDirectories(d));
    }
    return dirs;
};

const getAllCFiles = async function(source) {
    let files = await getCFiles(source);
    console.log("files:::::", files);
    for (let d of await getDirectories(source)) {
        files = files.concat(await getAllCFiles(d));
    }
    return files;
};

const ignoreAndFilter = async function(list, ignoreFile) {
    if (!await exists(ignoreFile)) {
        return list;
    }

    let parsed = (await promisify(fs.readFile)(ignoreFile, 'utf8')).split('\n').filter(f => !!f).map(f => f.trim());

    parsed = parsed.map(l => new RegExp(l));

    list = list.filter(l => {
        if (Path.sep === '\\') {
            l = l.replace(/\\/g, '/');
        }

        return parsed.every(p => !p.test(l));
    });

    return list;
};

const defaultBuildFlags = [
    '-s', 'NO_EXIT_RUNTIME=1',
    '-s', 'ASSERTIONS=2',
    '-s', 'ERROR_ON_UNDEFINED_SYMBOLS=0',
    '-s', 'FORCE_FILESYSTEM=1' ,
    '-DEMSCRIPTEN'
];

const emterpretifyFlags = [
    '-s', 'EMTERPRETIFY=1',
    '-s', 'EMTERPRETIFY_ASYNC=1',
    '-g3'
];

const nonEmterpretifyFlags = [
    '-s', 'ASYNCIFY=1',
    '-g4'
];

const mkdirpSync = function(targetDir) {
    const sep = Path.sep;
    const initDir = Path.isAbsolute(targetDir) ? sep : '';
    const baseDir = '.';

    targetDir.split(sep).reduce((parentDir, childDir) => {
        const curDir = Path.resolve(baseDir, parentDir, childDir);
        if (!fs.existsSync(curDir)) {
            fs.mkdirSync(curDir);
        }
        return curDir;
    }, initDir);
}


const spawnEmcc = async function(args) {
    let tmpFolder = Path.join(os.tmpdir(), (await promisify(crypto.randomBytes.bind(crypto))(32)).toString('hex'));

    let clearUpOnFinally = true;

    async function clear() {
        for (let file of await promisify(fs.readdir.bind(fs))(tmpFolder)) {
            await promisify(fs.unlink.bind(fs))(Path.join(tmpFolder, file));
        }

        await promisify(fs.rmdir.bind(fs))(tmpFolder);
    }

    try {
        await promisify(fs.mkdir.bind(fs))(tmpFolder);

        args = args.map(a => {
            if (Path.sep === '\\') {
                a = a.replace(/\\/g, '\\\\');
            }
            a = a.replace(/"/g, '\\"');
            a = `"${a}"`;
            return a;
        }).join(' ');

        let tmpFile = Path.join(tmpFolder, 'args.txt');
        await promisify(fs.writeFile.bind(fs))(tmpFile, args, 'utf-8');
        clearUpOnFinally = false;
        let cmd = spawn(emccCmd, [ '@' + tmpFile ]);
        cmd.on('close', clear);
        return cmd;
    }
    catch (ex) {
        throw ex;
    }
    finally {
        if (clearUpOnFinally) {
            await clear();
        }
    }
}

module.exports = {
    exists: exists,
    isDirectory: isDirectory,
    getDirectories: getDirectories,
    getCFiles: getCFiles,
    getAllDirectories: getAllDirectories,
    getAllCFiles: getAllCFiles,
    ignoreAndFilter: ignoreAndFilter,
    defaultBuildFlags: defaultBuildFlags,
    emterpretifyFlags: emterpretifyFlags,
    nonEmterpretifyFlags: nonEmterpretifyFlags,
    mkdirpSync: mkdirpSync,
    emccCmd: emccCmd,
    spawnEmcc: spawnEmcc
};