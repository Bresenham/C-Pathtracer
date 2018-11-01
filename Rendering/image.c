//
// Created by Standardbenutzer on 31.03.2018.
//
#include <stdio.h>
#include <mem.h>
#include "image.h"
#include "stdint.h"

void save_bitmap(const char *file_name, const unsigned int width, const unsigned int height, const unsigned int dpi, const int *buffer,
                 int samples) {
// create a file object that we will use to write our image
    FILE *image;
// we want to know how many pixels to reserve
    unsigned int image_size = width * height;
// a byte is 4 bits but we are creating a 24 bit image so we can represent a pixel with 3
// our final file size of our image is the width * height * 4 + size of bitmap header
    unsigned int file_size = 54 + 4 * image_size;

    struct bitmap_file_header {
        uint8_t         bitmap_type[2];     // 2 bytes
        uint32_t        file_size;          // 4 bytes
        uint16_t        reserved1;          // 2 bytes
        uint16_t        reserved2;          // 2 bytes
        uint32_t        offset_bits;        // 4 bytes
    } bfh;

// bitmap image header (40 bytes)
    struct bitmap_image_header {
        unsigned int    size_header;        // 4 bytes
        unsigned int    width;              // 4 bytes
        unsigned int    height;             // 4 bytes
        short int       planes;             // 2 bytes
        short int       bit_count;          // 2 bytes
        unsigned int    compression;        // 4 bytes
        unsigned int    image_size;         // 4 bytes
        unsigned int    ppm_x;              // 4 bytes
        unsigned int    ppm_y;              // 4 bytes
        unsigned int    clr_used;           // 4 bytes
        unsigned int    clr_important;      // 4 bytes
    } bih;

// if you are on Windows you can include <windows.h>
// and make use of the BITMAPFILEHEADER and BITMAPINFOHEADER structs

    memcpy(&bfh.bitmap_type, "BM", 2);
    bfh.file_size       = file_size;
    bfh.reserved1       = 0;
    bfh.reserved2       = 0;
    bfh.offset_bits     = 0;

    bih.size_header     = sizeof(bih);
    bih.width           = width;
    bih.height          = height;
    bih.planes          = 1;
    bih.bit_count       = 24;
    bih.compression     = 0;
    bih.image_size      = file_size;
    bih.ppm_x           = 0;
    bih.ppm_y           = 0;
    bih.clr_used        = 0;
    bih.clr_important   = 0;

    image = fopen(file_name, "wb");

// compiler woes so we will just use the constant 14 we know we have
    fwrite(&bfh, 1, 14, image);
    fwrite(&bih, 1, sizeof(bih), image);

// write out pixel data, one last important this to know is the ordering is backwards
// we have to go BGR as opposed to RGB
    int i = 0;
    for(unsigned y = 0; y < height; y++) {
        for (unsigned x = 0; x < width; x++) {
            uint8_t r = (uint8_t) (buffer[i * 3 + 0] / samples);
            uint8_t g = (uint8_t) (buffer[i * 3 + 1] / samples);
            uint8_t b = (uint8_t) (buffer[i * 3 + 2] / samples);

            uint8_t color[] = {b, g, r};

            fwrite(color, 1, sizeof(color), image);
            i++;
        }
    }
    fclose(image);
}

void drawbmp (char * filename, int WIDTH, int HEIGHT, int *buffer, int samples) {

    unsigned int headers[13];
    FILE * outfile;
    int extrabytes;
    int paddedsize;
    int x; int y; int n;

    extrabytes = 4 - ((WIDTH * 3) % 4);                 // How many bytes of padding to add to each
    // horizontal line - the size of which must
    // be a multiple of 4 bytes.
    if (extrabytes == 4)
        extrabytes = 0;

    paddedsize = ((WIDTH * 3) + extrabytes) * HEIGHT;

// Headers...
// Note that the "BM" identifier in bytes 0 and 1 is NOT included in these "headers".

    headers[0]  = paddedsize + 54;      // bfSize (whole file size)
    headers[1]  = 0;                    // bfReserved (both)
    headers[2]  = 54;                   // bfOffbits
    headers[3]  = 40;                   // biSize
    headers[4]  = WIDTH;  // biWidth
    headers[5]  = HEIGHT; // biHeight

// Would have biPlanes and biBitCount in position 6, but they're shorts.
// It's easier to write them out separately (see below) than pretend
// they're a single int, especially with endian issues...

    headers[7]  = 0;                    // biCompression
    headers[8]  = paddedsize;           // biSizeImage
    headers[9]  = 0;                    // biXPelsPerMeter
    headers[10] = 0;                    // biYPelsPerMeter
    headers[11] = 0;                    // biClrUsed
    headers[12] = 0;                    // biClrImportant

    outfile = fopen(filename, "wb");

//
// Headers begin...
// When printing ints and shorts, we write out 1 character at a time to avoid endian issues.
//

    fprintf(outfile, "BM");

    for (n = 0; n <= 5; n++)
    {
        fprintf(outfile, "%c", headers[n] & 0x000000FF);
        fprintf(outfile, "%c", (headers[n] & 0x0000FF00) >> 8);
        fprintf(outfile, "%c", (headers[n] & 0x00FF0000) >> 16);
        fprintf(outfile, "%c", (headers[n] & (unsigned int) 0xFF000000) >> 24);
    }

// These next 4 characters are for the biPlanes and biBitCount fields.

    fprintf(outfile, "%c", 1);
    fprintf(outfile, "%c", 0);
    fprintf(outfile, "%c", 24);
    fprintf(outfile, "%c", 0);

    for (n = 7; n <= 12; n++)
    {
        fprintf(outfile, "%c", headers[n] & 0x000000FF);
        fprintf(outfile, "%c", (headers[n] & 0x0000FF00) >> 8);
        fprintf(outfile, "%c", (headers[n] & 0x00FF0000) >> 16);
        fprintf(outfile, "%c", (headers[n] & (unsigned int) 0xFF000000) >> 24);
    }

//
// Headers done, now write the data...
//

    int i = 0;
    for (y = 0; y <HEIGHT; y++)     // BMP image format is written from bottom to top...
    {
        for (x = 0; x <= WIDTH - 1; x++)
        {

            int r = buffer[i * 3 + 0] / samples;
            int g = buffer[i * 3 + 1] / samples;
            int b = buffer[i * 3 + 2] / samples;

            fprintf(outfile, "%c", b);
            fprintf(outfile, "%c", g);
            fprintf(outfile, "%c", r);
            i++;
        }
        if (extrabytes)      // See above - BMP lines must be of lengths divisible by 4.
        {
            for (n = 1; n <= extrabytes; n++)
            {
                fprintf(outfile, "%c", 0);
            }
        }
    }

    fclose(outfile);
    return;
}