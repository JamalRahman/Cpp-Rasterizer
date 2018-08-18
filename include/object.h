//  object.h
//
//  Copyright (c) 2018 Jamal Rahman
//  Use of this source code is governed by the MIT license that can be
//  found in the LICENSE file.

#ifndef OBJECT_H
#define OBJECT_H

#include "primitives.h"

// A Object object stores full 3D data for an object in a scene.
class Object{
protected:
    // Vertex list
    // Vertex Texture List
    // Normals list
    // Face list

    // Material Data Structure

    // Visibility Flag
    // Smooth Shading Bit
    // Scene Space Origin

    bool rendered;
    int smooth;
    Point3D sceneSpaceOrigin;
};

#endif