//  color.h
//
//  Copyright (c) 2018 Jamal Rahman
//  Use of this source code is governed by the MIT license that can be
//  found in the LICENSE file.

#ifndef COLOR_H
#define COLOR_H

struct Color{
    union{
        struct{
            int r,g,b;
        };
        int array[3];
    };

    Color(int R, int G, int B) : r(R), g(G), b(B){

    };

    Color(int* p){
        for(int i=0;i<3;i++){
            array[i] = p[i];
        }
    };

};

#endif