//  primitives.h
//
//  Copyright (c) 2018 Jamal Rahman
//  Use of this source code is governed by the MIT license that can be
//  found in the LICENSE file.

#ifndef PRIMITVES
#define PRIMITVES

struct Vertex{
    int x,y,z;
    Vertex(int X, int Y, int Z) : x(X), y(Y), z(Z){};
};

struct Edge{
    Vertex v1, v2;
    Edge(Vertex V1, Vertex V2) : v1(V1), v2(V2){};
};


class Camera{
private:
    Vertex v;
    float focalLength;


protected:
    

public:


};

#endif