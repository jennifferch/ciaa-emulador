const http = require('http');
const fs = require('fs');

const hostname = '134.209.168.175';
const port = 7829;  // Reemplaza con el puerto que has habilitado

const server = http.createServer((req, res) => {
  res.statusCode = 200;
  res.setHeader('Content-Type', 'text/html');

  // Lee el archivo HTML y envíalo como respuesta
  fs.readFile('index.html', (err, data) => {
    if (err) {
      res.statusCode = 500;
      res.end('Error interno del servidor');
    } else {
      res.end(data);
    }
  });
});

server.listen(port, hostname, () => {
  console.log(`Server running at http://${hostname}:${port}/`);
});
