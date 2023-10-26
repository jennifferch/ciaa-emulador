# Arquitectura

La emulación a nivel de API proporciona una capa de abstracción para el entorno de desarrollo del usuario, de modo que permite escribir aplicaciones en C y ejecutarlas en la plataforma de emulación. 

Al utilizar esta capa de abstracción, se pudo replicar las funcionalidades y las características de configuración de la biblioteca sAPI del proyecto CIAA en un entorno diferente, en este caso, en un entorno web.

El diagrama de bloques es el siguiente:

![Arquitectura](../img/Arquitectura.png)

La `sAPI` se encuentra en la `Biblioteca C`. La capa de abstracción de hardware en C (C HAL)  permitió replicar el comportamiento del hardware de la placa, lo que a su vez posibilitó la compatibilidad de las bibliotecas de nivel superior escritas en C en el entorno de emulación de la plataforma web.

La capa JavaScript HAL se encuentra en `webapp/js-hal` y distribuye eventos entre los componentes de la interfaz de usuario de JavaScipt y C HAL. Implementa un bus de eventos para permitir que la interfaz de usuario se suscriba a los eventos de C. Por ejemplo, en `js-hal/sapi_gpio.js` se puede ver el manejo de GPIO.

La capa UI se encuentra en `webapp/js-ui`, y realiza el manejo de los eventos de la Interfaz de Usuario, y solamente se comunica con la capa JS HAL.

