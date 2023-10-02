#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H

#include "sapi.h"  
#include "Small_7.h"
#include "lcd_api.h"

/*==================[c]====================================================*/
#ifdef __cplusplus
extern "C" {
#endif

   enum {NORMAL,XOR};

    struct Bitmap{
        int xSize;
        int ySize;
        int Byte_in_Line;
        char* data;
    };

    unsigned int char_x;
    unsigned int char_y;
    unsigned int contrast;
    unsigned int auto_up;
    unsigned char* font;
    unsigned char buffer[32 * 128];

    struct FileHandle {
      int isatty;  
    };

    unsigned int orientation;
    uint16_t _column;
    uint16_t _row;
    uint16_t _foreground;
    uint16_t _background;
    char *_path;
    FILE *_file;

    // pixel location
    short _x;
    short _y;

    // window location
    short _x1;
    short _x2;
    short _y1;
    short _y2;
    unsigned int draw_mode;
    
    void initGraphicsDisplay(const char* name);

    void fill(int x, int y, int w, int h, int colour);

    void invert(unsigned int o);
    void set_contrast(unsigned int o);
    unsigned int get_contrast(void);
    void wr_cmd(unsigned char cmd);
    void wr_dat(unsigned char dat);
    void lcd_reset();
    void copy_to_lcd(void);
    void cls(void);
    void line(int x0, int y0, int x1, int y1, int color);
    void rect(int x0, int y0, int x1, int y1, int color);
    void fillrect(int x0, int y0, int x1, int y1, int color);
    void circle(int x0, int y0, int r, int color);
    void fillcircle(int x, int y, int r, int color);
    void setmode(int mode);
    void set_font(unsigned char* f);
    void set_auto_up(unsigned int up);
    unsigned int get_auto_up(void);
    void print_bm(struct Bitmap bm, int x, int y);

    void initTextDisplay(const char *name);
    void character(int x, int y, int c) ;
    void locate(int x, int y);
    void foreground(uint16_t colour);
    void background(uint16_t colour);

    int _putc(int c);
    int _getc();
    void _flush();

    FILE *lcdfdopen(struct FileHandle *fh, const char *mode);
    void mbed_set_unbuffered_stream(FILE *_file);

    bool claim (FILE *stream);
    int width();
    int height();
    int columns();
    int rows();
    int lcdputc(int c);
    int lcdPrintf(const char *format, ...);
    void mbed_set_unbuffered_stream(FILE *_file);

    off_t seek(off_t offset, int whence);
    void window(int x, int y, int w, int h);
    void putp(int colour);
    void pixel(int x, int y, int color);

#ifdef __cplusplus
}
#endif


#endif