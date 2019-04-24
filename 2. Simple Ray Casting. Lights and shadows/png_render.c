#include <malloc.h>
#include "png_render.h"

static void setRGBFromBuffer(png_byte* ptr, const unsigned char* buffer)
{
    ptr[0] = (png_byte)(buffer[0]);
    ptr[1] = (png_byte)(buffer[1]);
    ptr[2] = (png_byte)(buffer[2]);
}

PNG* createPng(char *filename, int width, int height, char* title)
{
    PNG* png = malloc(sizeof(PNG));
    png->width = width;
    png->height = height;

    // Open file for writing (binary mode)
    png->file = fopen(filename, "wb");
    if (png->file == NULL) {
        fprintf(stderr, "Could not open file %s for writing\n", filename);
        goto error;
    }

    // Initialize write structure
    png->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png->png_ptr == NULL)
    {
        fprintf(stderr, "Could not allocate write struct\n");
        goto error;
    }

    // Initialize info structure
    png->info_ptr = png_create_info_struct(png->png_ptr);
    if (png->info_ptr == NULL)
    {
        fprintf(stderr, "Could not allocate info struct\n");
        goto error;
    }

    // Setup Exception handling
    if (setjmp(png_jmpbuf(png->png_ptr)))
    {
        fprintf(stderr, "Error during png creation\n");
        goto error;
    }

    png_init_io(png->png_ptr, png->file);

    // Write header (8 bit colour depth)
    png_set_IHDR(png->png_ptr, png->info_ptr, width, height,
                 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    // Set title
    if (title != NULL)
    {
        png_text title_text;
        title_text.compression = PNG_TEXT_COMPRESSION_NONE;
        title_text.key = "Title";
        title_text.text = title;
        png_set_text(png->png_ptr, png->info_ptr, &title_text, 1);
    }

    png_write_info(png->png_ptr, png->info_ptr);

    return png;

    error:
    freePng(png);
    return NULL;
}

void freePng(PNG* png)
{
    if (png == NULL)
        return;

    // End write
    png_write_end(png->png_ptr, NULL);

    if (png->file != NULL) fclose(png->file);
    if (png->info_ptr != NULL) png_free_data(png->png_ptr, png->info_ptr, PNG_FREE_ALL, -1);
    if (png->png_ptr != NULL) png_destroy_write_struct(&png->png_ptr, (png_infopp)NULL);

    free(png);
}

void writeRow(PNG* png, unsigned char* buffer)
{
    // Allocate memory for one row (3 bytes per pixel - RGB)
    png_bytep row = (png_bytep) malloc(3 * png->width * sizeof(png_byte));

    // Write image data
    for (int x = 0 ; x < png->width; x++)
    {
        setRGBFromBuffer(&(row[x*3]), &(buffer[x*3]));
    }
    png_write_row(png->png_ptr, row);

    free(row);
}

