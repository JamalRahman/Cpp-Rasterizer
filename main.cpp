#include "bitmap.h"

int main(int argc, char const *argv[]){
    Bitmap bitmap;
    bitmap.readFile("flag.bmp");
    bitmap.writeFile("testOutput.bmp");
    return 0;
}