#include "bitmap.h"

using std::ifstream, std::cerr, std::endl, std::ofstream;

const int hSize = 14;
const int ihSize = 40;
/**
 * Constructs a Bitmap without parameters.
 * 
 * Image defaults to 1920x1080 px
 * Image defaults to 24 bit RGB encoding
 * @return The Bitmap Object
 */
Bitmap::Bitmap():imageData(NULL){
    memset((void*)&header,0,sizeof(BitmapHeader));
    memset((void*)&ih,0,sizeof(BitmapInfoHeader));
    
}

/**
 * Constructs a Bitmap with parameters
 * 
 * @param w The width of the image
 * @param h The height of the image
 * @param cd The color depth (number of bits per pixel) of the image
 * @return The Bitmap object
 */
Bitmap::Bitmap(int w, int h, int cd) : imageData(NULL){
    unsigned long dataSize = w*h*cd*8;
    imageData = new unsigned char[dataSize];
    
    memset(imageData, 255, dataSize);
    memset((void*)&header,0,sizeof(BitmapHeader));
    memset((void*)&ih,0,sizeof(BitmapInfoHeader));

    header.bitmapType[0] = (unsigned char)'B';
    header.bitmapType[1] = (unsigned char)'M';
    header.fileSize = hSize+ihSize+cd*8*h*w;
    header.offset = hSize+ihSize;

    ih.infoHeaderSize = ihSize;
    ih.width = w;
    ih.height = h;
    ih.colorPlanes = 1;
    ih.colorDepth = cd;
}

Bitmap::~Bitmap(){
    if(imageData) delete[] imageData;
}

/**
 * Gets the number of bytes required to pad the image rows into DWORDS
 * 
 * @return The number of bytes of padding required
 */
int Bitmap::paddingSize(){
    return (4 -(ih.width*ih.colorDepth*8 % 4))%4;
}

/**
 * Reads the contents of a .bmp file into a Bitmap object
 * 
 * @param filename The file to be read
 * @return True on successful read
 */
bool Bitmap::readFile(const char* filename){
    
    unsigned char identifier[2];
    unsigned char buffer[16];
    ifstream imageFile;

    imageFile.open(filename, ifstream::binary);
    
    if(imageFile.fail()){
        std::cerr<<"Failure to open file on 'read' action."<<std::endl;
        imageFile.close();
        return false;
    }

    imageFile.read((char*)buffer,2);
    identifier[0]=buffer[0];
    identifier[1]=buffer[1];
    if(!strcmp((const char*)identifier,"BM")){
        std::cerr<<"Failure to process image format. Unsupported Format."<<std::endl;
        imageFile.close();
        return false;
    }

    buffer[2] = (unsigned char)0;
    buffer[3] = (unsigned char)0;
    imageFile.read(((char*)buffer+4),12);

    memcpy((void*)&header,(unsigned char*)buffer,sizeof(BitmapHeader));

    if(header.offset>=hSize+ihSize){
        unsigned char infoBuffer[40];
        imageFile.read((char*)infoBuffer,40);
        memcpy((void*)&ih,(unsigned char*)infoBuffer,sizeof(BitmapInfoHeader));
        
        int imageDataSize = ih.width*ih.height*ih.colorDepth*8;
        imageData = new unsigned char[imageDataSize];
        memset(imageData,0,imageDataSize);

        imageFile.ignore(header.offset-(hSize+ihSize));
                
        for(int i=0;i<ih.height;i++){
            imageFile.read(((char*)imageData+(i*ih.width*ih.colorDepth*8)),(ih.width*ih.colorDepth*8));
            imageFile.ignore(paddingSize());
        }
    }
    else{
        std::cerr<<"BMP Version unsupported. Please use BMP v3.x+."<<std::endl;
        imageFile.close();
        return false;
    }

    imageFile.close();
    return true;
}

/**
 * Writes a Bitmap object to the system as a .bmp file
 * 
 * @param filename The write location. Must include ".bmp" extension 
 * @return True on successful write
 */
bool Bitmap::writeFile(const char *filename){
    
    // Bitmaps store data in DWORDS
    // If our width is not divisible by 4 we must pad each row with zeroes
    unsigned char* paddingStructure[3] = {0,0,0};

    ofstream imageFile;
    imageFile.open(filename, ifstream::binary);
    
    if(imageFile.fail()){
        std::cerr<<"Failure opening file on 'write' action."<<std::endl;
        return false;
    }

    // The C++ compiler pads the Header struct from 14 bytes to 16 bytes
    // We must write the chars then subsequent ints separately to avoid padding
    imageFile.write((const char*)&header.bitmapType,2);
    imageFile.write((const char*)&header.fileSize,12);

    
    imageFile.write((const char*)&ih,40);

    // Write one row at a time
    for(int i=0; i<ih.height; i++){
        imageFile.write((const char*)imageData+(i*ih.width*ih.colorDepth*8),ih.width*ih.colorDepth*8);
        imageFile.write((const char*)paddingStructure,paddingSize());      
    }

    imageFile.close();
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
    if(!imageData || x<0 || y<0 || x>ih.width || y>ih.height){
        return BitmapColor(0,0,0);
    }
    else{
        int r,g,b,a;
        unsigned char buffer[4];
        memcpy(buffer,imageData+(x+y*ih.width)*ih.colorDepth*8,4);
        
        return BitmapColor((const unsigned char*)buffer,ih.colorDepth*8);

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
    if(!imageData || x<0 || y<0 || x>ih.width || y>ih.height){
        return false;
    }
    memcpy(imageData+(x+y*ih.width)*ih.colorDepth*8, color.array,ih.colorDepth*8);
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
 * Sets every pixel in the image data to white
 */
void Bitmap::clear(){
    memset((void*)imageData,255,ih.width*ih.height*ih.colorDepth*8);
}

/**
 * Gets the pixel width of the image
 * 
 * @return The pixel width
 */
int Bitmap::getWidth(){
    return ih.width;
}

/**
 * Gets the pixel height of the image
 * 
 * @return The height, in pixels
 */
int Bitmap::getHeight(){
    return ih.height;
}

/**
 * Gets the pixel color depth of the image
 * 
 * @return Number of bits per pixel
 */
int Bitmap::getColorDepth(){
    return ih.colorDepth;
}