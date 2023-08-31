/* mbed TextDisplay Display Library Base Class
 * Copyright (c) 2007-2009 sford
 * Released under the MIT License: http://mbed.org/license/mit
 */

#include "TextDisplay.h"
#include "emscripten.h"

// character location
int _column;
int _row;

// colours
int _foreground;
int _background;
char *_path;


void initTextDisplay(const char *name){
    _row = 0;
    _column = 0;
    if (name == NULL) {
        _path = NULL;
    } else {
      //  _path = new char[strlen(name) + 2];
      //  sprintf(_path, "/%s", name);
    }
}

int _putc(int value) {
    EM_ASM_({ console.log("TextDisplay putc", $0); }, value);
    if(value == '\n') {
        _column = 0;
        _row++;
        if(_row >= rows()) {
            _row = 0;
        }
    } else {
        character(_column, _row, value);
        _column++;
        if(_column >= columns()) {
            _column = 0;
            _row++;
            if(_row >= rows()) {
                _row = 0;
            }
        }
    }
    return value;
}

// crude cls implementation, should generally be overwritten in derived class
void cls_clear() {
    locate_t(0, 0);
    for(int i=0; i<columns()*rows(); i++) {
        putc(' ', 0);
    }
}

void locate_t(int column, int row) {
    _column = column;
    _row = row;
}

int _getc() {
    return -1;
}

void foreground(int colour) {
    _foreground = colour;
}

void background(int colour) {
    _background = colour;
}

int claim (FILE *stream) {
    if ( _path == NULL) {
        fprintf(stderr, "claim requires a name to be given in the instantioator of the TextDisplay instance!\r\n");
        return 0;
    }
    if (freopen(_path, "w", stream) == NULL) {
        // Failed, should not happen
        return 0;
    }
    // make sure we use line buffering
    setvbuf(stdout, NULL, _IOLBF, columns());
    return 1;
}

int getColumn(){
    return _column;
}

int getBackground(){
    return _background;
}

int getForeground(){
    return _foreground;
}
