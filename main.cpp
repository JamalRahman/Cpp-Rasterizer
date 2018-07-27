#include "bitmap.h"

int main(int argc, char const *argv[]){
    
    Bitmap bitmap(1920,1080,3);

    for(int i=0;i<700;i++){
        bitmap.set(i,i,BitmapColor(0,((double)i/700*255),255-((double)i/700*255)));
    }

    bitmap.writeFile("test.bmp");

    return 0;
}