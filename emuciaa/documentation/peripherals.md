# Periféricos

## Cargando periféricos

El emulador viene con periféricos (como pantallas LCD, LED, etc.). Para cargarlos para su proyecto, agregue una sección de "periféricos" al archivo (simconfig.md). Puede cambiar la configuración del periférico en tiempo de ejecución haciendo clic en el **Menu Lateral**. Esto luego es almacenado en caché por el navegador. Para limpiar el caché, ejecute `sessionStorage.removeItem('model-dirty')` desde la consola de su navegador.

## Nuevo periférico

For an example of how a peripheral looks like, see `external_peripherals/temperature_humedity/dht11`.

Todos los archivos `js-hal` y `js-ui` se copiarán en el directorio BUILD.

Para comunicarse entre C y JavaScript utilice las macros `ES_ASM` (C -> JS), o mediante `ccall` (JS -> C). 


