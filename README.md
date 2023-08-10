## Emulador para la placa EDU-CIAA-NXP

### Prerequisites

1. Instalar [Mbed CLI](https://github.com/ARMmbed/mbed-cli).
1. Instalar [Python 2.7](https://www.python.org/downloads/windows/).
1. Instalar [Node.js](https://nodejs.org/en/) v8 or higher.
1. Instalar [Emscripten](https://github.com/emscripten-core/emsdk.git) versión 1.38.21.


### Instalación

1. Seguir los siguientes pasos:

    ```
    $ npm install
    $ node cli.js -i examples/blinky -o outUser --launch
    ```

### Atribuciones

* Biblioteca sAPI (http://www.proyecto-ciaa.com.ar/devwiki/doku.php?id=desarrollo:firmware:v3).
* EDU-CIAA-NXP.svg (https://github.com/epernia/board-simulator/blob/gh-pages/img/edu_ciaa_board.svg).

### Acerca del emulador

- [Arquitectura](documentation/architecture.md).