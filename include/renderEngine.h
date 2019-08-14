//  renderEngine.h
//
//  Copyright (c) 2018 Jamal Rahman
//  Use of this source code is governed by the MIT license that can be
//  found in the LICENSE file.

#ifndef RENDERENGINE
#define RENDERENGINE

#include "bitmap.h"
#include "scene.h"
#include "object.h"

void drawLine(int x0, int y0, int x1, int y1);
void plotPoint(int x, int y);
void saveImage();

class RenderEngine{
private:
    Bitmap* bitmap;
    float viewportZ;
    int cW, cH, vW, vH;
    void drawLineX(float x0, float y0, float x1, float y1);
    void drawLineY(float x0, float y0, float x1, float y1);

protected:


public:
    RenderEngine();
    RenderEngine(Bitmap* bitmap);
    ~RenderEngine();

    void drawLine(Point2D v1, Point2D v2);
    void drawPixel(int x, int y, Color color);
    void drawFace(Face f);
    void drawFilledFace(Face f);
    void drawObject(Object o);
    void renderScene(Scene* s);

    Point2D projectVertex(Point3D v);
    std::tuple<float,float> viewportTransform(float x, float y);

    void saveImage(const char* filename);
    int interpolate(int x0, int y0, int x1, int y1);  
};

#endif