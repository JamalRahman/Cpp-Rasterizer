#include "bitmapImage.h"
#include <iostream>

int imageHeight, imageWidth;
// Function Definitions -------------------------------

int main(int argc, char const *argv[]){
    
    imageHeight = 1080;
    imageWidth = 1920;

    unsigned char image[imageHeight][imageWidth][3];
    char* imageFileName = "test.bmp";

    int i, j;
    for(i=0; i<imageHeight; i++){
        for(j=0; j<imageWidth; j++){
            image[i][j][2] = (unsigned char)((double)i/imageHeight*255);
            image[i][j][1] = (unsigned char)((double)i/imageHeight*255);
            image[i][j][0] = (unsigned char)((double)i/imageHeight*255);
        }
    }

    saveBitmap((unsigned char *)image, imageHeight, imageWidth, imageFileName);

    return 0;
}