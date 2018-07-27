#include <iostream>
#include <stdio.h>
#include <string.h>
#include "bitmap.h"

/**
 * Constructs a Bitmap without parameters.
 * 
 * Image defaults to 1920x1080 px
 * Image defaults to 24 bit RGB encoding
 * @return The Bitmap Object
 */
Bitmap::Bitmap():imageData(NULL),width(1920),height(1080),bytesPerPixel(3){
    unsigned long dataSize = width*height*bytesPerPixel;
    imageData = new unsigned char[dataSize];
    memset(imageData,0,dataSize);
}

/**
 * Constructs a Bitmap with parameters
 * 
 * @param w The width of the image
 * @param h The height of the image
 * @param bpp The color depth (number of bytes per pixel) of the image
 * @return The Bitmap object
 */
Bitmap::Bitmap(int w, int h, int bpp) : imageData(NULL), width(w), height(h), bytesPerPixel(bpp){
    unsigned long dataSize = width*height*bytesPerPixel;
    imageData = new unsigned char[dataSize];
    memset(imageData, 0, dataSize);
}

Bitmap::~Bitmap(){
    if(imageData) delete[] imageData;
}

/**
 * Writes a Bitmap object to the system as a .bmp file
 * 
 * @param filename The write location. Must include ".bmp" extension 
 * @return True on success
 */
bool Bitmap::writeFile(const char *filename){
    
    BitmapHeader header;
    memset((void*)&header,0,sizeof(BitmapHeader));
    BitmapInfoHeader infoHeader;
    memset((void*)&infoHeader,0,sizeof(BitmapInfoHeader));

    header.bitmapType[0] = (unsigned char)'B';
    header.bitmapType[1] = (unsigned char)'M';
    header.fileSize = 14+40+bytesPerPixel*height*width;
    header.offset = 14+40;
    infoHeader.infoHeaderSize = 40;
    infoHeader.width = width;
    infoHeader.height = height;
    infoHeader.colorPlanes = 1;
    infoHeader.colorDepth = bytesPerPixel*8;

    unsigned char* paddingStructure[3] = {0,0,0};
    int paddingSize = (4 -(width*bytesPerPixel % 4))%4;

    FILE* imageFile = fopen(filename,"wb");
    
    fwrite((unsigned char*)&header.bitmapType,1,2,imageFile);
    fwrite((unsigned char*)&header.fileSize,1,4,imageFile);
    fwrite((unsigned char*)&header.reserved,1,4,imageFile);
    fwrite((unsigned char*)&header.offset,1,4,imageFile);

    fwrite((unsigned char*)&infoHeader,1,40,imageFile);

    for(int i=0; i<height; i++){
        fwrite((unsigned char*)imageData+(i*width*bytesPerPixel),1,width*bytesPerPixel,imageFile);
        fwrite(paddingStructure,1,paddingSize,imageFile);
    }

    fclose(imageFile);
    

}

/**
 * Gets the color of the Bitmap at the given coordinates
 * 
 * @param x The x coordinate
 * @param y The y coordinate
 * @return An object which represents the Bitmap's image data at (x,y)
 */
BitmapColor Bitmap::get(int x, int y){

}

/**
 * Sets the color of the Bitmap at the given coordinates
 * 
 * @param x The x coordinate
 * @param y The y coordinate
 * @param BitmapColor The color object which represents how to color the Bitmap pixel
 */
bool Bitmap::set(int x, int y, BitmapColor color){
    if(!imageData || x<0 || y<0 || x>width || y>height){
        return false;
    }
    memcpy(imageData+(x+y*width)*bytesPerPixel, color.array,bytesPerPixel);
}

/**
 * Gets the pixel width of the image
 * 
 * @return The pixel width
 */
int Bitmap::getWidth(){
    return width;
}

/**
 * Gets the pixel width of the image
 * 
 * @return The width, in pixels
 */
int Bitmap::getHeight(){
    return height;
}

/**
 * Gets the pixel height of the image
 * 
 * @return The height, in pixels
 */
int Bitmap::getBytesPerPixel(){
    return bytesPerPixel;
}

/**
 * Gets the image data raw byte array
 * 
 * @return The array of bytes which stores the raw image data 
 */
unsigned char* Bitmap::getData(){
    return imageData;
}

/**
 * Sets every pixel in the image data to black
 */
void Bitmap::clear(){
    memset((void*)imageData,0,width*height*bytesPerPixel);
}