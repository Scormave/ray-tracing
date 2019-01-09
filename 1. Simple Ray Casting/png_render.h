#ifndef CG_RAYTRACER_PNG_RENDER_H
#define CG_RAYTRACER_PNG_RENDER_H

#include <png.h>

typedef struct SPNG
{
    FILE* file;
    png_structp png_ptr;
    png_infop info_ptr;

    int width;
    int height;
} PNG;

PNG* createPng(char *filename, int width, int height, char* title);
void writeRow(PNG* png, unsigned  char* buffer);
void freePng(PNG* png);

#endif //CG_RAYTRACER_PNG_RENDER_H
