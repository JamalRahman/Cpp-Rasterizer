//  renderEngine.h
//
//  Copyright (c) 2018 Jamal Rahman
//  Use of this source code is governed by the MIT license that can be
//  found in the LICENSE file.

#ifndef RENDERENGINE
#define RENDERENGINE

#include "bitmap.h"
#include "scene.h"
#include "primitives.h"

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

    void drawLine(Vertex v1, Vertex v2);
    void drawPixel(int x, int y, Color color);
    void drawPixel(Vertex v, Color color);
    void drawFace(Vertex v1, Vertex v2, Vertex v3);
    void drawObject();
    void renderScene(Scene* s);

    void saveImage(const char* filename);  
};

#endif