#ifndef BITMAP_H
#define BITMAP_H

#include <iostream>
#include <stdio.h>
#include <string.h>

struct BitmapHeader{
    unsigned char bitmapType[2];
    int fileSize;
    int reserved;
    int offset;
};

struct BitmapInfoHeader{
    int infoHeaderSize;
    int width;
    int height;
    short colorPlanes;
    short colorDepth;
    int compression;
    int imageSize;
    int horizRes;
    int vertRes;
    int colNum;
    int importantColNum;
};

struct BitmapColor{
    union{
        struct{
            unsigned char r,b,g,a;
        };
        unsigned char array[4];
    };
    int bytesPerPixel;
    
    BitmapColor(unsigned char R, unsigned char G, unsigned char B, unsigned char A) : r(R), g(G), b(B), a(A), bytesPerPixel(4){
    
    };
    
    BitmapColor(unsigned char R, unsigned char G, unsigned char B) : r(R), g(G), b(B), a(255), bytesPerPixel(3){
    
    };

    BitmapColor(const unsigned char *p, int bpp) : bytesPerPixel(bpp){
        for(int i=0;i<bpp;i++){
            array[i] = p[i];
        }
    };

};

class Bitmap{
protected:
    unsigned char* imageData;
    int width;
    int height;
    int bytesPerPixel;

public:
    Bitmap();
    Bitmap(int w, int h, int bpp);

    bool readFile(const char *filename);
    bool writeFile(const char *filename);

    BitmapColor get(int x, int y);
    bool set(int x, int y, BitmapColor);
    ~Bitmap();

    int getWidth();
    int getHeight();
    int getBytesPerPixel();

    unsigned char* getData();
    void clear();
};

#endif