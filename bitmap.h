#ifndef BITMAP_H
#define BITMAP_H

#include <iostream>
#include <stdio.h>
#include <string.h>


// Stores Bitmap File Header. 14 bytes.
// See Wikipedia for information about the Bitmap File Format
struct BitmapHeader{
    unsigned char bitmapType[2];    // "BM" always
    int fileSize;                   // Total bytes in the file 
    int reserved;                   // Unused Data
    int offset;                     // Address at which the actual image data begins
};

// Stores Bitmap Info Header. 40 bytes.
struct BitmapInfoHeader{
    int infoHeaderSize;             // Size of this info header (40 bytes)
    int width;                      // Image width in px
    int height;                     // Image height in px
    short colorPlanes;              // Set to 0
    short colorDepth;               // Bits per pixel
    int compression;                // Compression method (usually 0)
    int imageSize;                  // Can be set to zero if no compression is used
    int horizRes;                   // pxm^-1 : usually set to 0
    int vertRes;                    // pxm^-1 : usually set to 0
    int colNum;                     // Number of colours, if set to 0 then colorDepth is used to calculate it
    int importantColNum;            // Number of "important Colours". 0=every colour.
};

// Structure to handle pixel values. A BitmapColor can have RGBA values.
// BitmapColor is most frequently used with only RGB, and A is ignored, this is when
// only 3 bytes per pixel are used.
// The structure also allows for 1 byte per pixel. A simple grayscale value.
struct BitmapColor{

    // Data can be addressed as individual members or as an array of values
    union{
        struct{
            unsigned char r,g,b,a;
        };
        unsigned char array[4];
    };
    int bytesPerPixel;

    // Instantiate using rgba in the constructor
    BitmapColor(unsigned char R, unsigned char G, unsigned char B, unsigned char A) : r(R), g(G), b(B), a(A), bytesPerPixel(4){
    
    };
    // Instantiate using rgb in the constructor
    BitmapColor(unsigned char R, unsigned char G, unsigned char B) : r(R), g(G), b(B), a(255), bytesPerPixel(3){
    
    };
    // Instantiate using an array in the constructor
    BitmapColor(const unsigned char *p, int bpp) : bytesPerPixel(bpp){
        for(int i=0;i<bpp;i++){
            array[i] = p[i];
        }
    };

};

// A Bitmap object stores image data
// The object can be altered, written to a file or recieve data from a file.
class Bitmap{
protected:
    unsigned char* imageData;
    int width;
    int height;
    int bytesPerPixel;

public:
    Bitmap();
    Bitmap(int w, int h, int bpp);

    ~Bitmap();

    bool readFile(const char *filename);
    bool writeFile(const char *filename);
    
    BitmapColor get(int x, int y);
    bool set(int x, int y, BitmapColor);

    unsigned char* getData();
    void clear();

    int getWidth();
    int getHeight();
    int getBytesPerPixel();
};

#endif