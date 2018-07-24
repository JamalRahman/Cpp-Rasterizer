#include <iostream>
#include "bitmap.h"


// Struct Definitions -------------------------------------------------------

struct Vertex{
    float x,y,z;
    Vertex(float X, float Y, float Z){
        x = X;
        y = Y;
        z = Z;
    }
};

struct Vector{
    float x,y,z;
    Vector(float X, float Y, float Z){
        x = X;
        y = Y;
        z = Z;
    }
};

struct Triangle{
    Vertex *v1;
    Vertex *v2;
    Vertex *v3;
    Triangle(Vertex* V1, Vertex* V2, Vertex* V3){
        v1 = V1;
        v2 = V2;
        v3 = V3;
    }
};

struct Edge{
    Vertex *v1;
    Vertex *v2;
    Edge(Vertex* V1, Vertex* V2){

    }
};

struct Camera{
    Vertex *pos;
    Vector *direction;
    Camera(Vertex* POS, Vector* DIRECTION){
        pos = POS;
        direction = DIRECTION;
    }
};

// Function Definitions -------------------------------

int main(int argc, char const *argv[]){
    Vertex *v1 = new Vertex(0,0,0);
    Vertex *v2 = new Vertex(1,1,0);
    Vertex *v3 = new Vertex(1,0,0);
    Vertex *cameraPos = new Vertex(0,0,0);
    Vector *cameraDirection = new Vector(0,0,1);

    Camera cam = new Camera(cameraPos,cameraDirection);
    Triangle *t1 = new Triangle(v1,v2,v3);
    Edge *e1 = new Edge(v1,v2);


    return 0;
}