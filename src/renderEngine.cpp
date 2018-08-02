//  renderEngine.cpp
//  Class that processes the rendering of shapes, objects and scenes.
//
//  Copyright (c) 2018 Jamal Rahman
//  Use of this source code is governed by the MIT license that can be
//  found in the LICENSE file.

#include "renderEngine.h"

BitmapColor red(255,0,0);

RenderEngine::RenderEngine(){

}

RenderEngine::RenderEngine(Bitmap* b){
    bitmap = b;
}

RenderEngine::~RenderEngine(){

}


void RenderEngine::drawLine(Vertex v1, Vertex v2){
    if(abs(v1.x-v2.x)>abs(v1.y-v2.y)){
        if(v1.x<v2.x) drawLineX(v1.x,v1.y,v2.x,v2.y);
        else drawLineX(v2.x,v2.y,v1.x,v1.y);
    }
    else{
        if(v1.y<v2.y) drawLineY(v1.x,v1.y,v2.x,v2.y);
        else drawLineY(v2.x,v2.y,v1.x,v1.y);
    }
}

void RenderEngine::drawPixel(int x, int y, BitmapColor color){
    (*bitmap).set(x,y,color);
}
void RenderEngine::drawPixel(Vertex v, BitmapColor color){
    (*bitmap).set(v.x,v.y,color);
}

void RenderEngine::drawPolygon(Vertex v1, Vertex v2, Vertex v3){
    // Use iterator (for each pair of the args)
    drawLine(v1,v2);
    drawLine(v1,v3);
    drawLine(v2,v3);
}

void RenderEngine::drawObject(){

}

void RenderEngine::renderScene(){

}

void RenderEngine::setScene(Scene* s){
    scene = s;
}

void RenderEngine::drawLineX(int x0, int y0, int x1, int y1){
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
        drawPixel(x,y,red);
        e+=dy;
        if((2*(e))>=dx){
            e-=dx;
            y+=iterator;
        }
    }
}

void RenderEngine::drawLineY(int x0, int y0, int x1, int y1){
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
        drawPixel(x,y,red);
        e+=dx;
        if((2*(e))>=dy){
            e-=dy;
            x+=iterator;
        }
    }
}

void RenderEngine::saveImage(const char* filename){
    (*bitmap).writeFile(filename);
}

