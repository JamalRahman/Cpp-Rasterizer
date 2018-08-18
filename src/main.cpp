#include "renderEngine.h"

int main(int argc, char const *argv[]){
    // Create Scene
        // Create Bitmap
            // Does bitmap belong to RenderEngine?
    // Create RenderEngine
    
    // Populate scene
    // Render scene
    
    Bitmap* bitmap = new Bitmap(200,200,24);
    RenderEngine renderEngine(bitmap);

    Point3D v1(100,100,0);
    Point3D v2(17,200,0);
    Point3D v3(200,60,0);

    Object* obj = new Object();
    
    renderEngine.saveImage("output.bmp");

    return 0;
}