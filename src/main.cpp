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
    Point3D v2(50,50,0);
    Point3D v3(100,50,0);
    std::vector<Point3D> vect{v1,v2,v3};
    Face f(vect);
    renderEngine.drawFace(f);
    renderEngine.saveImage("output.bmp");

    return 0;
}