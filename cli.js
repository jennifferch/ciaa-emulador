const fs = require('fs');
const Path = require('path');
const helpers = require('./tools/util');
const application = require('./tools/build-app');
const opn = require('opn');
const commandExistsSync = require('command-exists').sync;
const launchServer = require('./server/launch-server');
const version = JSON.parse(fs.readFileSync(Path.join(__dirname, 'package.json'), 'utf-8')).version;
const puppeteer = require('puppeteer');
const promisify = require('es6-promisify').promisify;

let program = require('commander');

program
    .version(version)
    .option('-i --input-dir <dir>', 'Input directory')
    .option('-f --input-file <file>', 'Input file')
    .option('-o --output-file <file>', 'Output file (or directory)')
    .option('-v --verbose', 'Verbose logging')
    .option('-c --compiler-opts <opts>', 'Compiler options (e.g. -std=c++11)')
    .option('-l --launch', 'Launch the simulator for this project after building (opens a browser)')
    .option('--launch-headless',  'Launch the simulator for this project after building in headless mode (pipes output to console)')
    .option('--skip-build', 'Skip the build step (launch only)')
    .option('--disable-runtime-logs', 'Disable runtime logs (e.g. from the LoRa server or networking proxy)')
    .option('--emterpretify', 'Enable emterpretify mode (required if projects take a long time to compile)')
    .allowUnknownOption(true)
    .parse(process.argv);

if (fs.existsSync(process.argv[2]) && fs.statSync(process.argv[2]).isDirectory()) {
    program.inputDir = Path.resolve(process.argv[2]);

    console.log('s.existsSync(process.argv[2])',  program.inputDir);
    if (!program.launchHeadless) {
        program.launch = true;
    }
}

if (program.inputDir && program.inputFile) {
    console.log('No se puede configurar --input-dir and --input-file');
    process.exit(1);
}

if (!program.inputDir && !program.inputFile) {
    console.log(`El argumento '--input-dir' o '--input-file' es requerido`);
    process.exit(1);
}

if (program.inputDir && !fs.existsSync(program.inputDir)) {
    console.log('Directorio', program.inputDir, 'no existe');
    process.exit(1);
}

if (program.inputDir && !fs.statSync(program.inputDir).isDirectory()) {
    console.log('Directorio', program.inputDir, 'no es un directorio');
    process.exit(1);
}

if (program.inputFile && !fs.existsSync(program.inputFile)) {
    console.log('Archivo', program.inputFile, 'no existe');
    process.exit(1);
}

if (program.inputFile && !fs.statSync(program.inputFile).isFile()) {
    console.log('Archivo', program.inputFile, 'no es un archivo');
    process.exit(1);
}

console.log('program.outputFile',  program.outputFile);

if (!program.outputFile) {
    if (program.inputDir) {
        program.inputDir = Path.resolve(program.inputDir);
        program.outputFile = Path.join(program.inputDir, 'BUILD', 'SIMULATOR', Path.basename(program.inputDir) + '.js');

        console.log('program.outputFile',  program.outputFile);
    }
    else {
        console.log(`Argumento '--output-file' es requerido`);
        process.exit(1);
    }
}

if (!commandExistsSync('emcc')) {
    console.log('No se encuentra emcc');
    console.log('\tEmscripten no esta instalado o no se encuentra en el PATH');
    console.log('\tFollow: https://kripken.github.io/emscripten-site/docs/getting_started/downloads.html');
    process.exit(1);
}

let inputDir = program.inputDir ? Path.resolve(program.inputDir) : Path.resolve(Path.dirname(program.inputFile));
program.inputFile = program.inputFile ? Path.resolve(program.inputFile) : null;
program.outputFile = Path.resolve(program.outputFile);

console.log('program.outputFile',  program.outputFile);

if (fs.existsSync(program.outputFile) && fs.statSync(program.outputFile).isDirectory()) {
    program.outputFile = Path.join(program.outputFile, Path.basename(inputDir) + '.js');
}

const outputDir = Path.dirname(program.outputFile);
helpers.mkdirpSync(outputDir);

let extraArgs = (program.compilerOpts || '').split(' ');

let fn = program.inputDir ? application.buildDirectory : application.buildFile;

if (program.skipBuild) {
    console.log('Skipping build...');
    fn = () => Promise.resolve();
}

fn(program.inputDir || program.inputFile, program.outputFile, extraArgs, program.emterpretify, program.verbose)
    .then(async function() {
        console.log('output file es', program.outputFile);

        if (program.launch || program.launchHeadless) {
            let browser;
            try {
                let port = process.env.PORT || 7900;
                let logsEnabled = !program.disableRuntimeLogs;
                await promisify(launchServer)(outputDir, port, 0, logsEnabled);

                let name = Path.basename(program.outputFile, '.js');

                if (program.launch) {
                    opn(`http://localhost:${port}`);
                }
                else if (program.launchHeadless) {
                    browser = await puppeteer.launch();
                    const page = await browser.newPage();
                    await page.exposeFunction('onPrintEvent', e => {
                        console.log(e);
                    });
                    await page.exposeFunction('onStartExecution', () => {
                        console.log('Aplicacion inicializa');
                    });
                    await page.exposeFunction('onFailedExecution', async function (e) {
                        console.error('Error', e);
                        await browser.close();
                        process.exit(1);
                    });
                    await page.goto(`http://localhost:${port}`);
                }
            }
            catch (ex) {
                console.error('Fallo levantar el servidor', ex);
                if (browser) {
                    await browser.close();
                }
            }
        }
    })
    .catch(err => {
        console.error(err);
        console.error('Aplicacion fallo');
    });