//  object.h
//
//  Copyright (c) 2018 Jamal Rahman
//  Use of this source code is governed by the MIT license that can be
//  found in the LICENSE file.

#ifndef OBJECT_H
#define OBJECT_H

#include "primitives.h"
#include "material.h"

// A Object object stores full 3D data for an object in a scene.
class Object{
private:
    bool loadObj(const char* filename);

protected:
    vector<Point3D> verts;
    vector<Point2D> vertTexs;
    vector<Point3D> norms;
    vector<Face> faces;
    
    Material* material;          // Material Data Structure
    bool rendered;              // Visibility Flag
    bool smooth;                // Smooth shading bit
    Point3D sceneSpaceOrigin;   // Scene space representation of object's origin

public:
    Object();
    Object(const char *filename);

    ~Object();

    vector<Face> getFaces();
    void setRendered(bool r);
    void setSmooth(int s);
    Point3D *getOrigin();
};

#endif