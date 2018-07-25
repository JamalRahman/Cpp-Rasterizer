#ifndef BITMAP_H
#define BITMAP_H


const int defaultHeaderSize = 54;       // Header default uses the "BITMAPINFOHEADER" format, being 14 + 40 bytes long
const int defaultBytesPerPixel = 3;     // Default colour depth is 24 bits per pixel. 24/8 = 3 bytes per pixel (rgb each 3 char digits long, 0-255))

void saveBitmap(unsigned char *imageData, int height, int width, char *imageName);
unsigned char* generateBitmapHeader(int height, int width);

#include <stdio.h>

#endif