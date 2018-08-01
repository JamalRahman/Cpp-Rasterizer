#include "renderEngine.h"
#include "scene.h"


int main(int argc, char const *argv[]){
    drawLine(100,100,140,120);
    drawLine(100,100,120,140);
    drawLine(100,100,60,120);
    drawLine(100,100,80,140);
    
    drawLine(100,100,140,80);
    drawLine(100,100,120,60);
    drawLine(100,100,60,80);
    drawLine(100,100,80,60);

    saveImage();
    
    return 0;
}