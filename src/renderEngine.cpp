#include "renderEngine.h"

Bitmap bitmap(200,200,24);
BitmapColor red(255,0,0);

void drawLine(int x0, int y0, int x1, int y1){
    int e = 0,
        y = y0,
        dx = x1-x0,
        dy=y1-y0;
    for(int x = x0;x<=x1;x++){
        plotPoint(x,y);
        e+=dy;
        if((2*(e))>=dx){
            e-=dx;
            y++;
        }
    }
}

void plotPoint(int x,int y){
    bitmap.set(x,y,red);
}

void saveImage(){
    bitmap.writeFile("testBOI.bmp");
}