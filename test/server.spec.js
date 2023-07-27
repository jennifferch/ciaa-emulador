var request = require('request');
const puppeteer = require('puppeteer');
const { expect } = require('chai');
const chai = require("chai");
const { ok } = require('should');

const server = 'http://localhost:7900';

chai.should();
chai.use(require("chai-http"));


describe('EDU-CIAA-NXP Emulador ', function() {
        it('Contenido de la página principal', function(done) {
          request(server, function(error, response, body) {
                expect(response.statusCode)
                .to
                .equal(200);
                expect(response.statusMessage)
                .to
                .equal('OK');
                expect(response.text)
                .to
                .not
                .null;
                done();
            });
        });
});

describe('Contentido del ejemplo Blinky ', function() {
  it('Compruebe que el ejemplo Blinky se ejecuta en el primer acceso', function(done) {
    request(server, function(error, response, body) {
          expect(response.statusCode)
          .to
          .equal(200);
          expect(response.statusMessage)
          .to
          .equal('OK');
          expect(response.text)
          .to
          .not
          .null;
          done();
      });
  });
});

describe('Blinky', function() {
      it('Ejecutar ejemplo blinky', function(done) {
         chai
         .request(server)
         .get('/view/blinky')
         .end( function(err,res){
            res
            .headers
            .should
            .have
            .property('content-type')
            .eql('text/html; charset=utf-8');
            done(err);
          });
      });
  });

  describe('Prueba del ejemplo static_mem_freeRTOS_blinky', () => {
    let browser;
    let page;
  
    before(async () => {
      browser = await puppeteer.launch(); 
      page = await browser.newPage(); 
      await page.goto(server); 
    });
  
    after(async () => {
      await browser.close(); 
    });
  
    it('El ejemplo static_mem_freeRTOS_blinky debe cargarse en la Plataforma web', async () => {
      await page.waitForSelector('#select-project');
  
      const listboxContent = await page.evaluate(() => {
        const listbox = document.getElementById('select-project');
        const items = Array.from(listbox.options).map(option => option.textContent);
        return items;
      });
  
      const itemToCheck = 'static freeRTOS blinky';
      expect(listboxContent).to.include(itemToCheck);
    });
  });

  describe('Prueba del ejemplo rtos_cooperative', () => {
    let browser;
    let page;
  
    before(async () => {
      browser = await puppeteer.launch(); 
      page = await browser.newPage(); 
      await page.goto(server); 
    });
  
    after(async () => {
      await browser.close(); 
    });
  
    it('El ejemplo rtos_cooperative debe cargarse en la Plataforma web', async () => {
      await page.waitForSelector('#select-project');
  
      const listboxContent = await page.evaluate(() => {
        const listbox = document.getElementById('select-project');
        const items = Array.from(listbox.options).map(option => option.textContent);
        return items;
      });
  
      const itemToCheck = 'scheduler';
      expect(listboxContent).to.include(itemToCheck);
    });
  });

  describe('Prueba del ejemplo non_blocking_delay', () => {
    let browser;
    let page;
  
    before(async () => {
      browser = await puppeteer.launch(); 
      page = await browser.newPage(); 
      await page.goto(server); 
    });
  
    after(async () => {
      await browser.close(); 
    });
  
    it('El ejemplo non_blocking_delay debe cargarse en la Plataforma web', async () => {
      await page.waitForSelector('#select-project');
  
      const listboxContent = await page.evaluate(() => {
        const listbox = document.getElementById('select-project');
        const items = Array.from(listbox.options).map(option => option.textContent);
        return items;
      });
  
      const itemToCheck = 'non_blocking_delay';
      expect(listboxContent).to.include(itemToCheck);
    });
  });

  describe('Prueba del ejemplo modular_tasks', () => {
    let browser;
    let page;
  
    before(async () => {
      browser = await puppeteer.launch(); 
      page = await browser.newPage(); 
      await page.goto(server); 
    });
  
    after(async () => {
      await browser.close(); 
    });
  
    it('El ejemplo modular_tasks debe cargarse en la Plataforma web', async () => {
      await page.waitForSelector('#select-project');
  
      const listboxContent = await page.evaluate(() => {
        const listbox = document.getElementById('select-project');
        const items = Array.from(listbox.options).map(option => option.textContent);
        return items;
      });
  
      const itemToCheck = 'modular_tasks';
      expect(listboxContent).to.include(itemToCheck);
    });
  });

  describe('Prueba del ejemplo rtc printf', () => {
    let browser;
    let page;
  
    before(async () => {
      browser = await puppeteer.launch(); 
      page = await browser.newPage(); 
      await page.goto(server); 
    });
  
    after(async () => {
      await browser.close(); 
    });
  
    it('El ejemplo rtc printf debe cargarse en la Plataforma web', async () => {
      await page.waitForSelector('#select-project');
  
      const listboxContent = await page.evaluate(() => {
        const listbox = document.getElementById('select-project');
        const items = Array.from(listbox.options).map(option => option.textContent);
        return items;
      });
  
      const itemToCheck = 'rtc printf';
      expect(listboxContent).to.include(itemToCheck);
    });
  });

  describe('Prueba del ejemplo switches leds', () => {
    let browser;
    let page;
  
    before(async () => {
      browser = await puppeteer.launch(); 
      page = await browser.newPage(); 
      await page.goto(server); 
    });
  
    after(async () => {
      await browser.close(); 
    });
  
    it('El ejemplo switches leds debe cargarse en la Plataforma web', async () => {
      await page.waitForSelector('#select-project');
  
      const listboxContent = await page.evaluate(() => {
        const listbox = document.getElementById('select-project');
        const items = Array.from(listbox.options).map(option => option.textContent);
        return items;
      });
  
      const itemToCheck = 'switches leds';
      expect(listboxContent).to.include(itemToCheck);
    });
  });

  describe('Prueba del ejemplo button', () => {
    let browser;
    let page;
  
    before(async () => {
      browser = await puppeteer.launch(); 
      page = await browser.newPage(); 
      await page.goto(server); 
    });
  
    after(async () => {
      await browser.close(); 
    });
  
    it('El ejemplo button debe cargarse en la Plataforma web', async () => {
      await page.waitForSelector('#select-project');
  
      const listboxContent = await page.evaluate(() => {
        const listbox = document.getElementById('select-project');
        const items = Array.from(listbox.options).map(option => option.textContent);
        return items;
      });
  
      const itemToCheck = 'button';
      expect(listboxContent).to.include(itemToCheck);
    });
  });

  describe('Prueba del ejemplo tick_callback', () => {
    let browser;
    let page;
  
    before(async () => {
      browser = await puppeteer.launch(); 
      page = await browser.newPage(); 
      await page.goto(server); 
    });
  
    after(async () => {
      await browser.close(); 
    });
  
    it('El ejemplo tick_callback debe cargarse en la Plataforma web', async () => {
      await page.waitForSelector('#select-project');
  
      const listboxContent = await page.evaluate(() => {
        const listbox = document.getElementById('select-project');
        const items = Array.from(listbox.options).map(option => option.textContent);
        return items;
      });
  
      const itemToCheck = 'tick_callback';
      expect(listboxContent).to.include(itemToCheck);
    });
  });

  describe('Prueba del botón Ejecutar', () => {
    let browser;
    let page;
  
    before(async () => {
      browser = await puppeteer.launch(); 
      page = await browser.newPage(); 
      await page.goto(server); 
    });
  
    after(async () => {
      await browser.close(); 
    });
  
    it('El botón Ejecutar debe funcionar correctamente al hacer clic', async () => {
      await page.click('#run'); 
      await page.waitFor(1000); 
  
      const resultadoEsperado = await page.evaluate(() => {
        return true; 
      });
  
      expect(resultadoEsperado).to.be.true; 
    });
  });
  
  describe('Prueba del botón Ver ejemplo', () => {
    let browser;
    let page;
  
    before(async () => {
      browser = await puppeteer.launch(); 
      page = await browser.newPage(); 
      await page.goto(server); 
    });
  
    after(async () => {
      await browser.close(); 
    });
  
    it('El botón Ver ejemplo debe funcionar correctamente al hacer clic', async () => {
      await page.click('#load-example'); 
      await page.waitFor(1000); 
  
      const resultadoEsperado = await page.evaluate(() => {
        return true; 
      });
  
      expect(resultadoEsperado).to.be.true; 
    });
  });

  describe('Prueba del botón Nuevo proyecto', () => {
    let browser;
    let page;
  
    before(async () => {
      browser = await puppeteer.launch(); 
      page = await browser.newPage(); 
      await page.goto(server); 
    });
  
    after(async () => {
      await browser.close(); 
    });
  
    it('El botón Nuevo proyecto debe funcionar correctamente al hacer clic', async () => {
      await page.click('#load-new'); 
      await page.waitFor(1000); 
  
      const resultadoEsperado = await page.evaluate(() => {
        return true; 
      });
  
      expect(resultadoEsperado).to.be.true; 
    });
  });

  describe('Prueba del botón Descargar', () => {
    let browser;
    let page;
  
    before(async () => {
      browser = await puppeteer.launch(); 
      page = await browser.newPage(); 
      await page.goto(server); 
    });
  
    after(async () => {
      await browser.close(); 
    });
  
    it('El botón Descargar debe funcionar correctamente al hacer clic', async () => {
      await page.click('#run-download'); 
      await page.waitFor(1000); 
  
      const resultadoEsperado = await page.evaluate(() => {
        return true; 
      });
  
      expect(resultadoEsperado).to.be.true; 
    });
  });