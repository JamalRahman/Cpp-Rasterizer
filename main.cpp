#include "bitmap.h"

int main(int argc, char const *argv[]){
    
    // Bitmap bitmap(22,10,3);
    Bitmap bitmap2;

    // for(int i=0;i<10;i++){
    //     bitmap.set(i,i,BitmapColor(0,((double)i/10*255),255-((double)i/10*255)));
    // }

    // bitmap.writeFile("test.bmp");

    bitmap2.readFile("test2.bmp");
    bitmap2.writeFile("testOutput.bmp");
    
    return 0;
}