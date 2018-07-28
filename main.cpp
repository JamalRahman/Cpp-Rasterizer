#include "bitmap.h"

int main(int argc, char const *argv[]){
    
    Bitmap bitmap;

    // for(int i=0;i<700;i++){
    //     bitmap.set(i,i,BitmapColor(0,((double)i/700*255),255-((double)i/700*255)));
    // }

    // bitmap.writeFile("test.bmp");

    bitmap.readFile("image.bmp");
    bitmap.writeFile("output2.bmp");
    
    return 0;
}