//
//  mar.h
//  tactil
//
//  Created by ignacio pedreira gonzalez on 25/03/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

// fondo para el tactil de picatxu, es un mesh con un sader para hacer una wave


#ifndef tactil_mar_h
#define tactil_mar_h

#include "ofMain.h"

class mar{
public:
    
    void setup();
    void update();
    void draw();
    
private:
    void creaGrid();
    
    ofShader shaderFondo;
    ofMesh mesh;
    ofEasyCam cam;
    int waveDirection, waveFrequency;
    ofImage fondo;
};

#endif
