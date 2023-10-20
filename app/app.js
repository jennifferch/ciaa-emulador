const http = require('http');
const fs = require('fs');
const path = require('path');

const hostname = '134.209.168.175';
const port = 7900;  // Reemplaza con el puerto que has habilitado

const server = http.createServer((req, res) => {
  if (req.url === '/') {
    // Lee el archivo HTML
    const htmlPath = path.join(__dirname, 'index.html');
    const htmlContent = fs.readFileSync(htmlPath, 'utf8');

    // Escribe la respuesta en el navegador
    res.writeHead(200, { 'Content-Type': 'text/html' });
    res.end(htmlContent);
  } else {
    // Manejar otros casos (por ejemplo, 404 Not Found)
    res.writeHead(404);
    res.end('Archivo no encontrado');
  }
});

server.listen(port, hostname, () => {
  console.log(`Server running at http://${hostname}:${port}/`);
});
