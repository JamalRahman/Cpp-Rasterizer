#include <iostream>
#include <stdio.h>
#include <string.h>
#include "bitmap.h"


Bitmap::Bitmap(){

}

Bitmap::Bitmap(int w, int h, int bpp) : imageData(NULL), width(w), height(h), bytesPerPixel(bpp){
    unsigned long dataSize = width*height*bytesPerPixel;
    imageData = new unsigned char[dataSize];
    memset(imageData, 0, dataSize);
}

Bitmap::~Bitmap(){
    if(imageData) delete[] imageData;
}

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

BitmapColor Bitmap::get(int x, int y){

}

bool Bitmap::set(int x, int y, BitmapColor color){
    if(!imageData || x<0 || y<0 || x>width || y>height){
        return false;
    }
    memcpy(imageData+(x+y*width)*bytesPerPixel, color.array,bytesPerPixel);
}

int Bitmap::getWidth(){

}

int Bitmap::getHeight(){

}

int Bitmap::getBytesPerPixel(){

}

unsigned char* Bitmap::getData(){

}

void Bitmap::clear(){

}




int main(int argc, char const *argv[])
{
    Bitmap bitmap(50,50,3);

    for(int i=20;i<31;i++){
        bitmap.set(i,i,BitmapColor(0,0,255));
    }

    bitmap.writeFile("test.bmp");
    return 0;
}
