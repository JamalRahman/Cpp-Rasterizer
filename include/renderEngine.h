//  renderEngine.h
//
//  Copyright (c) 2018 Jamal Rahman
//  Use of this source code is governed by the MIT license that can be
//  found in the LICENSE file.

#ifndef RENDERENGINE
#define RENDERENGINE

#include "bitmap.h"
#include "scene.h"

void drawLine(int x0, int y0, int x1, int y1);
void plotPoint(int x, int y);
void saveImage();

class RenderEngine{
private:
    Scene* scene;
    Bitmap* bitmap;

    void drawLineX(int x0, int y0, int x1, int y1);
    void drawLineY(int x0, int y0, int x1, int y1);

protected:


public:
    RenderEngine();
    RenderEngine(Bitmap* bitmap);
    ~RenderEngine();

    void drawLine(int x0, int y0, int x1, int y1);
    void drawPixel(int x, int y);
    void drawPolygon();
    void drawObject();
    void renderScene();

    void setScene(Scene* s);
    Scene* getScene();

    void saveImage(const char* filename);  
};

#endif