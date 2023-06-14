var request = require('request');
const chai = require("chai");
const { ok } = require('should');
const expect = chai.expect;
const server = 'http://localhost:7900';

chai.should();
chai.use(require("chai-http"));


describe('EDU-CIAA-NXP Emulador ', function() {
        it('Main page content', function(done) {
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

describe('Blinky page content', function() {
  it('Check Blinking page content is executed on first access', function(done) {
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
      it('run example blinky', function(done) {
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

  