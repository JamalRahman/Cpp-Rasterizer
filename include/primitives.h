//  primitives.h
//
//  Copyright (c) 2018 Jamal Rahman
//  Use of this source code is governed by the MIT license that can be
//  found in the LICENSE file.

#ifndef PRIMITVES
#define PRIMITVES

struct Point3D{
    int x,y,z;
    Point3D(int X, int Y, int Z) : x(X), y(Y), z(Z){};
};

struct Point2D{
    int x,y;
    Point2D(int X, int Y): x(X), y(Y){};
};

struct Edge{
    Point3D v1, v2;
    Edge(Point3D V1, Point3D V2) : v1(V1), v2(V2){};
};

struct Face{
    //Point3D[] Vertices
    //Point2D[] Texture Vertices
    //Point3D[] Normals

};

class Camera{
private:
    Point3D v;
    float focalLength;


protected:
    

public:


};

#endif