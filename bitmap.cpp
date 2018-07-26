#include "bitmap.h"
#include <stdio.h>

// Functions    ----------------------------------------------------------------------

void saveBitmap(unsigned char *imageData, int height, int width, char *imageName){

    unsigned char* imageHeader = generateBitmapHeader(height, width);

    // Due to bitmap's image data requiring all rows explained in multiples of 4 byte DWORDS, we determine how many bytes short our rows are of completing a DWORD, and will later pad them
    unsigned char* paddingStructure[3] = {0,0,0};
    int paddingSize = (4 -(width*defaultBytesPerPixel % 4))%4;

    // We open the file
    FILE* imageFile = fopen(imageName, "wb");

    // Write header to file
    fwrite(imageHeader,1,defaultHeaderSize,imageFile);

    // Iterate over rows, writing each time
    int index;
    for(index=0; index<height; index++){
        fwrite(imageData+(index*width*defaultBytesPerPixel),1,width*defaultBytesPerPixel,imageFile);
        fwrite(paddingStructure,1,paddingSize,imageFile);
    }

    fclose(imageFile);

}

unsigned char* generateBitmapHeader(int height, int width){
    
    // Size of file = bytes in header + bytes in image data
    int fileSize = defaultHeaderSize +defaultBytesPerPixel*height*width;

    // Declaring 54 char long header data. See BMP specification
    static unsigned char header[] = {      
        0,0,        // BM
        0,0,0,0,    // Size of the entire file
        0,0,0,0,    // Reserved - Unused
        0,0,0,0,    // File offset index
        0,0,0,0,    // Info header size ( 4o bytes)
        0,0,0,0,    // Width (signed int)
        0,0,0,0,    // Height (signed int)
        0,0,        // Number of Colour planes
        0,0,        // Num bits per pixel (colour depth)
        0,0,0,0,    // Compression level
        0,0,0,0,    // Image size
        0,0,0,0,    // Horiz resolution
        0,0,0,0,    // Vert res
        0,0,0,0,    // Colour number
        0,0,0,0,    // Number of important colours
    };

    // Filling in header data

    header[0] = (unsigned char)'B';
    header[1] = (unsigned char)'M';

    header[2] = (unsigned char)(fileSize);
    header[3] = (unsigned char)(fileSize>>8);
    header[4] = (unsigned char)(fileSize>>16);
    header[5] = (unsigned char)(fileSize>>24);

    header[10] = (unsigned char)(defaultHeaderSize);
    header[14] = (unsigned char)(40);

    header[18] = (unsigned char)(width);
    header[19] = (unsigned char)(width>>8);
    header[20] = (unsigned char)(width>>16);
    header[21] = (unsigned char)(width>>24);

    header[22] = (unsigned char)(height);
    header[23] = (unsigned char)(height>>8);
    header[24] = (unsigned char)(height>>16);
    header[25] = (unsigned char)(height>>24);

    header[26] = (unsigned char)(1);
    header[28] = (unsigned char)(defaultBytesPerPixel*8);

    return header;
}

unsigned char* readBitmap(FILE* imageFile){
    
}