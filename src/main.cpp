#include "renderEngine.h"
#include "scene.h"


int main(int argc, char const *argv[]){
    Bitmap bitmap(200,200,24);
    bitmap.set(100,100,BitmapColor(255,0,0));
    bitmap.writeFile("output.bmp");
    
    return 0;
}