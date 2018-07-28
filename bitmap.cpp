#include "bitmap.h"
#include <iostream>
#include <stdio.h>
#include <string.h>

const int bmfhSize = 14;
const int bmihSize = 40;
/**
 * Constructs a Bitmap without parameters.
 * 
 * Image defaults to 1920x1080 px
 * Image defaults to 24 bit RGB encoding
 * @return The Bitmap Object
 */
Bitmap::Bitmap():imageData(NULL),width(0),height(0),bytesPerPixel(0){

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

bool Bitmap::readFile(const char* filename){
    
    unsigned char identifier[2];
    unsigned char buffer[16];
    BitmapHeader header;

    FILE* imageFile = fopen(filename,"rb");
    if(imageFile<0){
        std::cerr<<"Failure to open file on 'read' action."<<std::endl;
        return false;
    }

    fread(buffer,1,2,imageFile);
    identifier[0]=buffer[0];
    identifier[1]=buffer[1];
    if(!strcmp((const char*)identifier,"BM")){
        std::cerr<<"Failure to process image format. Unsupported Format."<<std::endl;
        fclose(imageFile);
        return false;
    }

    buffer[2] = (unsigned char)0;
    buffer[3] = (unsigned char)0;
    fread(buffer+4,1,12,imageFile);

    memcpy((void*)&header,buffer,sizeof(BitmapHeader));
    std::cout<<header.offset<<std::endl;
    if(header.offset>=54){
        BitmapInfoHeader infoHeader;
        unsigned char infoBuffer[40];

        fread(infoBuffer,1,40,imageFile);
        memcpy((void*)&infoHeader,infoBuffer,sizeof(BitmapInfoHeader));
        
        width = infoHeader.width;
        height = infoHeader.height;
        bytesPerPixel = infoHeader.colorDepth/8;

        int imageDataSize = infoHeader.width*infoHeader.height*infoHeader.colorDepth;
        imageData = new unsigned char[imageDataSize];
        memset(imageData,0,imageDataSize);

        unsigned char paddingStructure[3];
        int paddingSize = (4 -(width*bytesPerPixel % 4))%4;

        // fread(imageData,1,imageDataSize,imageFile);
        // PADDING
        // for(int i=0;i<height;i++){
        //     fread(imageData,1,width*bytesPerPixel,imageFile);
        //     fread(paddingStructure,paddingSize,1,imageFile);
        // }
    }
    else{
        std::cerr<<"BMP Version unsupported. Please use BMP v3.x"<<std::endl;
        return false;
    }

    fclose(imageFile);
    
    return true;
}

/**
 * Writes a Bitmap object to the system as a .bmp file
 * 
 * @param filename The write location. Must include ".bmp" extension 
 * @return True on success
 */
bool Bitmap::writeFile(const char *filename){
    
    BitmapHeader header;
    BitmapInfoHeader infoHeader;

    // Zeroes the headers in memory
    memset((void*)&header,0,sizeof(BitmapHeader));
    memset((void*)&infoHeader,0,sizeof(BitmapInfoHeader));

    // Assign values to the headers, all other members are kept zeroed.
    header.bitmapType[0] = (unsigned char)'B';
    header.bitmapType[1] = (unsigned char)'M';
    header.fileSize = bmfhSize+bmihSize+bytesPerPixel*height*width;
    header.offset = bmfhSize+bmihSize;

    infoHeader.infoHeaderSize = bmihSize;
    infoHeader.width = width;
    infoHeader.height = height;
    infoHeader.colorPlanes = 1;
    infoHeader.colorDepth = bytesPerPixel*8;

    // Bitmaps write the image data in 4 byte DWORDS
    // If our width is not divisible by 4 we must pad each row with zeroes
    // to complete the DWORD
    unsigned char* paddingStructure[3] = {0,0,0};
    int paddingSize = (4 -(width*bytesPerPixel % 4))%4;

    FILE* imageFile = fopen(filename,"wb");
    
    if(imageFile<0){
        std::cerr<<"Failure opening file on 'write' action."<<std::endl;
        return false;
    }

    // The C++ compiler turns the Header struct from 14 bytes to 16 bytes
    // It adds padding after the 2 byte char array.
    // We must write the chars then subsequent ints manually
    // Else we will write the padding
    fwrite((unsigned char*)&header.bitmapType,1,2,imageFile);
    fwrite((unsigned char*)&header.fileSize,1,4,imageFile);
    fwrite((unsigned char*)&header.reserved,1,4,imageFile);
    fwrite((unsigned char*)&header.offset,1,4,imageFile);

    fwrite((unsigned char*)&infoHeader,1,40,imageFile);

    // Write one row at a time
    for(int i=0; i<height; i++){
        fwrite((unsigned char*)imageData+(i*width*bytesPerPixel),1,width*bytesPerPixel,imageFile);
        fwrite(paddingStructure,1,paddingSize,imageFile);
    }

    fclose(imageFile);
    return true;
}

/**
 * Gets the color of the Bitmap at the given coordinates
 * 
 * @param x The x coordinate
 * @param y The y coordinate
 * @return An object which represents the Bitmap's image data at (x,y)
 */
BitmapColor Bitmap::get(int x, int y){
    if(!imageData || x<0 || y<0 || x>width || y>height){
        return BitmapColor(0,0,0);
    }
    else{
        int r,g,b,a;
        unsigned char buffer[4];
        memcpy(buffer,imageData+(x+y*width)*bytesPerPixel,4);
        
        return BitmapColor((const unsigned char*)buffer,bytesPerPixel);

    }
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