# Debugging

Las aplicaciones del emulador se pueden depurar con el depurador de su navegador, ya que contienen mapas de origen. Para depurar una aplicación:

**Chrome**

![Debugging in Chrome](../img/chrome-debug.png)

1. Abra las Herramientas para desarrolladores a través de **View > Developer > Developer Tools**.
1. Click **Sources**.
1. En 'Red', seleccione el nombre de la aplicación (consulte el hash del navegador).
1. Ahora localiza `main.c`.
    * En una demostración prediseñada, vaya a la `outUser` carpeta, seleccione el nombre del ejemplo  `blinky` y seleccione `main.c`.
    * En una aplicación compilada por el usuario, vaya a la carpeta `outUser` carpeta, y seleccione `main.c`.
1. Haga clic en la ventana para agregar un punto de interrupción.
1. Haga clic en el **↻** icono en el simulador para reiniciar la sesión de depuración.

