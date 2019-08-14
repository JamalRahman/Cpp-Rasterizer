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

    Point3D v1(50,50,0.35);
    Point3D v2(50,100,0.35);
    Point3D v3(100,100,0.35);
    Point3D v4(100,50,0.35);

    Point3D v1b(50,50,0.4);
    Point3D v2b(50,100,0.4);
    Point3D v3b(100,100,0.4);
    Point3D v4b(100,50,0.4);


    std::vector<Point3D> vectb{v1b,v2b,v3b,v4b};
    std::vector<Point3D> vectb1{v2,v3,v3b,v2b};
    Face f1(vectb);
    Face fb1(vectb1);

    Face anonFace({v1,v2,v3,v4});
    
    renderEngine.drawFace(anonFace);
    renderEngine.drawFace(f1);
    renderEngine.drawFace(fb1);
    renderEngine.saveImage("output.bmp");

    return 0;
}