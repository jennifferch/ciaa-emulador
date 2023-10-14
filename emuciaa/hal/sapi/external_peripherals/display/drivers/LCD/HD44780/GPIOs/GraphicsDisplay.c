#include "GraphicsDisplay.h"

#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#define BPP    1       // Bits per pixel

gpioMap_t _lcdrs;
gpioMap_t _lcden;
gpioMap_t _lcd;

   _lcdrs = LCDRS;
   _lcden = LCDEN;
   _lcd = LCD1;

void initGraphicsDisplay(const char* name) {

    initTextDisplay(name);

    foreground(0xFFFF);
    background(0x0000);
   
    lcd_init( _lcdrs, _lcden, _lcd);
    orientation = 1;
    draw_mode = NORMAL;
    char_x = 0;
    lcd_reset();
}

void fill(int x, int y, int w, int h, int colour) 
{
    window(x, y, w, h);
    for(int i=0; i<w*h; i++) {
        putp(colour);
    }
}

void lcd_reset()
{
    memset(buffer,0x00,4096);  // clear display buffer
    locate(0,0);
    set_font((unsigned char*)lcdSmall);  // standart font

    copy_to_lcd();
}

void copy_to_lcd(void)
{
  lcd_copy_to_lcd( _lcdrs, _lcden, _lcd, buffer);
}


void glcd_print_bitmap(uint8_t* bitmap)
{
   bitmap_to_glcd(bitmap);
}

void copy_char_to_glcd(void)
{
   char_to_glcd(char_x, char_y, buffer16x4);
}

void copy_char_to_lcd(void)
{
   char_to_lcd(char_x, char_y, buffer20x4);
}

void glcd_clear(void)
{
    memset(buffer16x4, 0x00, 64);
    display_clear_glcd();
}

void lcd_clear(void)
{
    memset(buffer20x4, 0x00, 80);
    display_clear_lcd();
}

void cls(void)
{
    memset(buffer,0x00,4096);  // clear display buffer
    copy_to_lcd();
}

void line(int x0, int y0, int x1, int y1, int color)
{
    int   dx = 0, dy = 0;
    int   dx_sym = 0, dy_sym = 0;
    int   dx_x2 = 0, dy_x2 = 0;
    int   di = 0;

    dx = x1-x0;
    dy = y1-y0;

    if (dx > 0) {
        dx_sym = 1;
    } else {
        dx_sym = -1;
    }

    if (dy > 0) {
        dy_sym = 1;
    } else {
        dy_sym = -1;
    }

    dx = dx_sym*dx;
    dy = dy_sym*dy;

    dx_x2 = dx*2;
    dy_x2 = dy*2;

    if (dx >= dy) {
        di = dy_x2 - dx;
        while (x0 != x1) {

            pixel(x0, y0, color);
            x0 += dx_sym;
            if (di<0) {
                di += dy_x2;
            } else {
                di += dy_x2 - dx_x2;
                y0 += dy_sym;
            }
        }
        pixel(x0, y0, color);
    } else {
        di = dx_x2 - dy;
        while (y0 != y1) {
            pixel(x0, y0, color);
            y0 += dy_sym;
            if (di < 0) {
                di += dx_x2;
            } else {
                di += dx_x2 - dy_x2;
                x0 += dx_sym;
            }
        }
        pixel(x0, y0, color);
    }
    if(auto_up) copy_to_lcd();
}

void rect(int x0, int y0, int x1, int y1, int color)
{
    if (x1 > x0) line(x0,y0,x1,y0,color);
    else  line(x1,y0,x0,y0,color);

    if (y1 > y0) line(x0,y0,x0,y1,color);
    else line(x0,y1,x0,y0,color);

    if (x1 > x0) line(x0,y1,x1,y1,color);
    else  line(x1,y1,x0,y1,color);

    if (y1 > y0) line(x1,y0,x1,y1,color);
    else line(x1,y1,x1,y0,color);

    if(auto_up) copy_to_lcd();
}

void fillrect(int x0, int y0, int x1, int y1, int color)
{
    int l,c,i;
    if(x0 > x1) {
        i = x0;
        x0 = x1;
        x1 = i;
    }

    if(y0 > y1) {
        i = y0;
        y0 = y1;
        y1 = i;
    }

    for(l = x0; l<= x1; l ++) {
        for(c = y0; c<= y1; c++) {
            pixel(l,c,color);
        }
    }
    if(auto_up) copy_to_lcd();
}

void circle(int x0, int y0, int r, int color)
{

    int draw_x0, draw_y0;
    int draw_x1, draw_y1;
    int draw_x2, draw_y2;
    int draw_x3, draw_y3;
    int draw_x4, draw_y4;
    int draw_x5, draw_y5;
    int draw_x6, draw_y6;
    int draw_x7, draw_y7;
    int xx, yy;
    int di;
    //WindowMax();
    if (r == 0) {       /* no radius */
        return;
    }

    draw_x0 = draw_x1 = x0;
    draw_y0 = draw_y1 = y0 + r;
    if (draw_y0 < height()) {
        pixel(draw_x0, draw_y0, color);     /* 90 degree */
    }

    draw_x2 = draw_x3 = x0;
    draw_y2 = draw_y3 = y0 - r;
    if (draw_y2 >= 0) {
        pixel(draw_x2, draw_y2, color);    /* 270 degree */
    }

    draw_x4 = draw_x6 = x0 + r;
    draw_y4 = draw_y6 = y0;
    if (draw_x4 < width()) {
        pixel(draw_x4, draw_y4, color);     /* 0 degree */
    }

    draw_x5 = draw_x7 = x0 - r;
    draw_y5 = draw_y7 = y0;
    if (draw_x5>=0) {
        pixel(draw_x5, draw_y5, color);     /* 180 degree */
    }

    if (r == 1) {
        return;
    }

    di = 3 - 2*r;
    xx = 0;
    yy = r;
    while (xx < yy) {

        if (di < 0) {
            di += 4*xx + 6;
        } else {
            di += 4*(xx - yy) + 10;
            yy--;
            draw_y0--;
            draw_y1--;
            draw_y2++;
            draw_y3++;
            draw_x4--;
            draw_x5++;
            draw_x6--;
            draw_x7++;
        }
        xx++;
        draw_x0++;
        draw_x1--;
        draw_x2++;
        draw_x3--;
        draw_y4++;
        draw_y5++;
        draw_y6--;
        draw_y7--;

        if ( (draw_x0 <= width()) && (draw_y0>=0) ) {
            pixel(draw_x0, draw_y0, color);
        }

        if ( (draw_x1 >= 0) && (draw_y1 >= 0) ) {
            pixel(draw_x1, draw_y1, color);
        }

        if ( (draw_x2 <= width()) && (draw_y2 <= height()) ) {
            pixel(draw_x2, draw_y2, color);
        }

        if ( (draw_x3 >=0 ) && (draw_y3 <= height()) ) {
            pixel(draw_x3, draw_y3, color);
        }

        if ( (draw_x4 <= width()) && (draw_y4 >= 0) ) {
            pixel(draw_x4, draw_y4, color);
        }

        if ( (draw_x5 >= 0) && (draw_y5 >= 0) ) {
            pixel(draw_x5, draw_y5, color);
        }
        if ( (draw_x6 <=width()) && (draw_y6 <= height()) ) {
            pixel(draw_x6, draw_y6, color);
        }
        if ( (draw_x7 >= 0) && (draw_y7 <= height()) ) {
            pixel(draw_x7, draw_y7, color);
        }
    }
    if(auto_up) copy_to_lcd();
}

void fillcircle(int x, int y, int r, int color)
{
    int i,up;
    up = auto_up;
    auto_up = 0;   // off
    for (i = 0; i <= r; i++)
        circle(x,y,i,color);
    auto_up = up;
    if(auto_up) copy_to_lcd();
}

void setmode(int mode)
{
    draw_mode = mode;
}


void set_font(unsigned char* f)
{
    font = f;
}

void set_auto_up(unsigned int up)
{
    if(up ) auto_up = 1;
    else auto_up = 0;
}

unsigned int get_auto_up(void)
{
    return (auto_up);
}

void print_bm(struct Bitmap bm, int x, int y)
{
    int h,v,b;
    char d;

    for(v=0; v < bm.ySize; v++) {   // lines
        for(h=0; h < bm.xSize; h++) { // pixel
            if(h + x > 127) break;
            if(v + y > 31) break;
            d = bm.data[bm.Byte_in_Line * v + ((h & 0xF8) >> 3)];
            b = 0x80 >> (h & 0x07);
            if((d & b) == 0) {
                pixel(x+h,y+v,0);
            } else {
                pixel(x+h,y+v,1);
            }
        }
    }

}

void initTextDisplay(const char *name){
    _file = NULL;

    struct FileHandle fileHandle;
    fileHandle.isatty = false; 

    _file = lcdfdopen(&fileHandle, "w+");
    // fdopen() will make us buffered because Stream::isatty()
    // wrongly returns zero which is not being changed for
    // backward compatibility
    if (_file) {
        mbed_set_unbuffered_stream(_file);
    } 

    _row = 0;
    _column = 0;
    if (name == NULL) {
        _path = NULL;
    } else {
       // _path = new char[strlen(name) + 2];
        _path = (char *)malloc(strlen(name) + 2);
        sprintf(_path, "/%s", name);
    }
}

int _putc(int value) {
    {
        if (value == '\n') {    // new line
            char_x = 0;
            char_y = char_y + font[2];
            if (char_y >= height() - font[2]) {
                char_y = 0;
            }
        } else {
            character(char_x, char_y, value);
            if(auto_up) copy_to_lcd();
        }
        return value;
    }
    
}

void locate(int x, int y)
{
    char_x = x;
    char_y = y;
}

int _getc() {
    return -1;
}

void foreground(uint16_t colour) {
    _foreground = colour;
}

void background(uint16_t colour) {
    _background = colour;
}

bool claim (FILE *stream) {
    if ( _path == NULL) {
        fprintf(stderr, "claim requires a name to be given in the instantioator of the TextDisplay instance!\r\n");
        return false;
    }
    if (freopen(_path, "w", stream) == NULL) {
        // Failed, should not happen
        return false;
    }
    // make sure we use line buffering
    setvbuf(stdout, NULL, _IOLBF, columns());
    return true;
}

int width()
{
    if (orientation == 0 || orientation == 2) return 32;
    else return 128;
}

int height()
{
    if (orientation == 0 || orientation == 2) return 128;
    else return 32;
}

int columns() {
    return width() / 8;
}

int rows() {
    return height() / 8;
}


int lcdputc(int c)
{

    fflush(_file);
    int ret = _putc(c);
    return ret;
}

int lcdPrintf(const char *format, ...)
{
    va_list arg;
    va_start(arg, format);

    char buffer[4096] = { 0 };
    int r = vsprintf(buffer, format, arg);
    for (int ix = 0; ix < r; ix++) {
        _putc(buffer[ix]);
    }
    _flush();

    va_end(arg);
    return r;
}

int glcdPrintChar(const char *format, ...)
{
    memset(buffer16x4, 0x00, 64);
    va_list arg;
    va_start(arg, format);

    char buffer[64] = {};
    int r = vsprintf(buffer, format, arg);
    for (int ix = 0; ix < r; ix++) {
       buffer16x4[ix] = buffer[ix];
    }
    copy_char_to_glcd();

    va_end(arg);
    return r;
}


int lcdPrintChar(const char *format, ...)
{
    memset(buffer20x4, 0x00, 80);
    va_list arg;
    va_start(arg, format);

    char buffer[80] = {};
    int r = vsprintf(buffer, format, arg);
    for (int ix = 0; ix < r; ix++) {
       buffer20x4[ix] = buffer[ix];
    }
    copy_char_to_lcd();

    va_end(arg);
    return r;
}


void _flush(void)
{
    copy_to_lcd();
}

void mbed_set_unbuffered_stream(FILE *_file) {
#if defined (__ICCARM__)
    char buf[2];
    setvbuf(_file,buf,_IONBF,NULL);
#else
    setbuf(_file, NULL);
#endif
}

FILE *lcdfdopen(struct FileHandle *fh, const char *mode){
    // Implementación del método fdopen aquí
    char buf[1 + sizeof(fh)]; /* :(pointer) */
  //  MBED_STATIC_ASSERT(sizeof(buf) == 5, "Pointers should be 4 bytes.");
    buf[0] = ':';
    memcpy(buf + 1, &fh, sizeof(fh));

    FILE *stream = fopen(buf, mode);
    /* newlib-nano doesn't appear to ever call _isatty itself, so
     * happily fully buffers an interactive stream. Deal with that here.
     */
    if (stream && fh->isatty) {
        mbed_set_unbuffered_stream(stream);
    }
    return stream;
}

off_t seek(off_t offset, int whence)
{
    return 0;
}

void character(int x, int y, int c)
{
    unsigned int hor,vert,offset,bpl,j,i,b;
    unsigned char* zeichen;
    unsigned char z,w;

    if ((c < 31) || (c > 127)) return;   // test char range

    // read font parameter from start of array
    offset = font[0];                    // bytes / char
    hor = font[1];                       // get hor size of font
    vert = font[2];                      // get vert size of font
    bpl = font[3];                       // bytes per line

    if (char_x + hor > width()) {
        char_x = 0;
        char_y = char_y + vert;
        if (char_y >= height() - font[2]) {
            char_y = 0;
        }
    }

    zeichen = &font[((c -32) * offset) + 4]; // start of char bitmap
    w = zeichen[0];                          // width of actual char
    // construct the char into the buffer
    for (j=0; j<vert; j++) {  //  vert line
        for (i=0; i<hor; i++) {   //  horz line
            z =  zeichen[bpl * i + ((j & 0xF8) >> 3)+1];
            b = 1 << (j & 0x07);
            if (( z & b ) == 0x00) {
                pixel(x+i,y+j,0);
            } else {
                pixel(x+i,y+j,1);
            }

        }
    }

    char_x += w;
}

void window(int x, int y, int w, int h) {
    // current pixel location
    _x = x;
    _y = y;
    // window settings
    _x1 = x;
    _x2 = x + w - 1;
    _y1 = y;
    _y2 = y + h - 1;
}

void putp(int colour) {
    // put pixel at current pixel location
    pixel(_x, _y, colour);
    // update pixel location based on window settings
    _x++;
    if(_x > _x2) {
        _x = _x1;
        _y++;
        if(_y > _y2) {
            _y = _y1;
        }
    }
}

void pixel(int x, int y, int color)
{
    // first check parameter
    if(x > 128 || y > 32 || x < 0 || y < 0) return;

    if(draw_mode == NORMAL) {
        if(color == 0)
            buffer[x + (y * 128)] = 0;
        else
            buffer[x + (y * 128)] = 1;
    } else { // XOR mode
        if(color == 1)
            buffer[x + (y * 128)] ^= 1;
    }
}