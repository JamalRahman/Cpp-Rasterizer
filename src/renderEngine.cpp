#include "renderEngine.h"

Bitmap bitmap(200,200,24);
BitmapColor red(255,0,0);

void drawLineX(int x0, int y0, int x1, int y1){
    int e = 0,
        y = y0,
        iterator=1,
        dx = x1-x0,
        dy=y1-y0;
        if(dy<0){
            dy = -dy;
            iterator = -1;
        }
    for(int x = x0;x<=x1;x++){
        plotPoint(x,y);
        e+=dy;
        if((2*(e))>=dx){
            e-=dx;
            y+=iterator;
        }
    }
}
void drawLineY(int x0, int y0, int x1, int y1){
    int e = 0,
        x = x0,
        iterator=1,
        dx = x1-x0,
        dy=y1-y0;
        if(dx<0){
            dx = -dx;
            iterator = -1;
        }
    for(int y = y0;y<=y1;y++){
        plotPoint(x,y);
        e+=dx;
        if((2*(e))>=dy){
            e-=dy;
            x+=iterator;
        }
    }
}

void drawLine(int x0, int y0, int x1, int y1){
    if(abs(x0-x1)>abs(y0-y1)){
        if(x0<x1) drawLineX(x0,y0,x1,y1);
        else drawLineX(x1,y1,x0,y0);
    }
    else{
        if(y0<y1) drawLineY(x0,y0,x1,y1);
        else drawLineY(x1,y1,x0,y0);
    }
}
void plotPoint(int x,int y){
    bitmap.set(x,y,red);
}

void saveImage(){
    bitmap.writeFile("testBOI.bmp");
}