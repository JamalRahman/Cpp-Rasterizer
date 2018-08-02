#include "renderEngine.h"

int main(int argc, char const *argv[]){
    // Create Scene
        // Create Bitmap
            // Does bitmap belong to RenderEngine?
    // Create RenderEngine
    
    // Populate scene
    // Render scene
    Bitmap* bitmap = new Bitmap(512,512,24);
    RenderEngine renderEngine(bitmap);

    Vertex v1(100,100,0);
    Vertex v2(250,200,0);
    Vertex v3(200,150,0);

    renderEngine.drawPolygon(v1,v2,v3);

    renderEngine.saveImage("myboi.bmp");

    return 0;
}