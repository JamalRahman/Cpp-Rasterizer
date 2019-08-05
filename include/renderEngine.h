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

    void drawLineX(int x0, int y0, int x1, int y1);
    void drawLineY(int x0, int y0, int x1, int y1);

protected:


public:
    RenderEngine();
    RenderEngine(Bitmap* bitmap);
    ~RenderEngine();

    void drawLine(Point3D v1, Point3D v2);
    void drawPixel(int x, int y, Color color);
    void drawPixel(Point3D v, Color color);
    void drawFace(Face f);
    void drawObject(Object o);
    void renderScene(Scene* s);

    void saveImage(const char* filename);
    int interpolate(int x0, int y0, int x1, int y1);  
};

#endif