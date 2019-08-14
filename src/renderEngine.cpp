//  renderEngine.cpp
//  Class that processes the rendering of shapes, objects and scenes.
//
//  Copyright (c) 2018 Jamal Rahman
//  Use of this source code is governed by the MIT license that can be
//  found in the LICENSE file.

#include "renderEngine.h"
#include <tuple>

Color red(255,0,0);

RenderEngine::RenderEngine(){

}

RenderEngine::RenderEngine(Bitmap* b){
    bitmap = b;
    cW = bitmap->getWidth();
    cH = bitmap->getHeight();
    vW = 400;
    vH = 400;
    viewportZ = 1;
}

RenderEngine::~RenderEngine(){

}


void RenderEngine::drawPixel(int x, int y, Color color){
    (*bitmap).set(x,y,color);
}

void RenderEngine::drawLine(Point2D v1, Point2D v2){
    if(abs(v1.x-v2.x)>abs(v1.y-v2.y)){
        if(v1.x<v2.x) drawLineX(v1.x,v1.y,v2.x,v2.y);
        else drawLineX(v2.x,v2.y,v1.x,v1.y);
    }
    else{
        if(v1.y<v2.y) drawLineY(v1.x,v1.y,v2.x,v2.y);
        else drawLineY(v2.x,v2.y,v1.x,v1.y);
    }
}

void RenderEngine::drawFace(Face f){
    int vertCount = f.verts.size();
    if(vertCount==0){
        return;
    }
    drawLine(projectVertex(f.verts.at(0)),projectVertex(f.verts.at(vertCount-1)));
    for(int i=0;i<vertCount-1;i++){
        drawLine(projectVertex(f.verts.at(i)),projectVertex(f.verts.at(i+1)));
    }
}

void RenderEngine::drawFilledFace(Face f){
    
}

void RenderEngine::drawObject(Object o){
    
}

void RenderEngine::renderScene(Scene* s){

}

void RenderEngine::drawLineX(float x0, float y0, float x1, float y1){
    int e = 0,
        y = y0,
        iterator=1,
        dx = x1-x0,
        dy=y1-y0;
    if(dy<0){
        dy = -dy;
        iterator = -1;
    }
    for(int x = (int)x0;x<=x1;x++){
        drawPixel(x,y,red);
        e+=dy;
        if((2*(e))>=dx){
            e-=dx;
            y+=iterator;
        }
    }
}

void RenderEngine::drawLineY(float x0, float y0, float x1, float y1){
    int e = 0,
        x = x0,
        iterator=1,
        dx = x1-x0,
        dy=y1-y0;
        if(dx<0){
            dx = -dx;
            iterator = -1;
        }
    for(int y = (int)y0;y<=y1;y++){
        drawPixel(x,y,red);
        e+=dx;
        if((2*(e))>=dy){
            e-=dy;
            x+=iterator;
        }
    }
}

Point2D RenderEngine::projectVertex(Point3D vIn){
    float tempX = vIn.x * viewportZ / vIn.z;
    float tempY = vIn.y * viewportZ / vIn.z;
    auto t = viewportTransform(tempX,tempY);
    return Point2D((float)std::get<0>(t),(float)std::get<1>(t));
}

std::tuple<float,float> RenderEngine::viewportTransform(float x, float y){
    return std::make_tuple(x*cW/vW,y*cH/vH);
}

void RenderEngine::saveImage(const char* filename){
    (*bitmap).writeFile(filename);
}