//
//  miniaturas.h
//  tactil
//
//  Created by natxo pedreira on 14/01/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef MINIATURAS
#define MINIATURAS
#include "ofMain.h"
#include "thumb.h"

class miniaturas{
public:
    miniaturas();
    ~miniaturas();
    
    void setup(int cuantas, float _px, float _py);
    void update(float _dx, float _dy);
    void drawCircle();
    
    vector<ofPolyline> lineas;
    vector<ofPoint> circlePoints;
    
    int circleResolution;
    float radio;
    
    ofPoint centro;
    vector<thumb *> thumbs;
};

#endif
