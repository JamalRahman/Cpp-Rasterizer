//  primitives.h
//
//  Copyright (c) 2018 Jamal Rahman
//  Use of this source code is governed by the MIT license that can be
//  found in the LICENSE file.

#ifndef PRIMITVES
#define PRIMITVES

#include <vector>

using std::vector;

struct Point3D{
    float x,y,z;
    Point3D(float X, float Y, float Z) : x(X), y(Y), z(Z){};
    Point3D():x(0),y(0),z(0){};
};

struct Point2D{
    float x,y;
    Point2D(float X, float Y): x(X), y(Y){};
};

struct Edge{
    Point3D v1, v2;
    Edge(Point3D V1, Point3D V2) : v1(V1), v2(V2){};
};

struct Face{
    vector<Point3D> verts;
    vector<Point2D> vertTexs;
    Point3D norm;
    Face(const vector<Point3D> &v):verts(v){};
    Face(vector<Point3D> v, vector<Point2D> vt, Point3D n):verts(v),vertTexs(vt),norm(n){};
    Face(vector<Point3D> v, vector<Point2D> vt):verts(v),vertTexs(vt){};
    Face(vector<Point3D> v, Point3D n):verts(v),norm(n){};
};

class Camera{
private:
    Point3D loc;
    Point3D dir;
    float focalLength;
    int vh, vw;


protected:
    

public:


};

#endif