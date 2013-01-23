//
//  miniaturas.cpp
//  tactil
//
//  Created by natxo pedreira on 14/01/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "miniaturas.h"

miniaturas::miniaturas(){
    circleResolution = 0;
    centro.set(0, 0);
}

miniaturas::~miniaturas(){
    for (int i = 0; i < thumbs.size(); i++) {
        delete thumbs[i];
    }
    
    thumbs.clear();
    circlePoints.clear();
}

void miniaturas::setup(int cuantas, float _px, float _py){
    ofPolyline circlePolyline;
    
    circleResolution = cuantas;
    centro.set(_px, _py);
    
    radio = cuantas * 13;
    
    circlePolyline.arc(centro,radio,radio,0,360,cuantas);
    circlePoints.resize(circlePolyline.size());
    
    for (int i = 0; i < circlePolyline.size(); i++) {
        
        thumb * b = new thumb();
        b->set(circlePolyline[i].x-30, circlePolyline[i].y-30, 45, 45);
        b->color.set(171,209,217);
        b->nombre = "mini";
        thumbs.push_back(b);
        
        
        circlePoints.push_back(circlePolyline[i]);
        
    }
}

void miniaturas::update(float _dx, float _dy){
    /// hay que actualizar el vector con las lineas
    centro.x += _dx * .075;
    centro.y += _dy * .075;
    
    lineas.clear();
    
    for (int i = 0; i < thumbs.size(); i++) {
        
        thumbs[i]->x += _dx * .075;
        thumbs[i]->y += _dy * .075;
        
        thumbs[i]->urdate();
    }
}

void miniaturas::drawCircle(){
    ofPushMatrix();
    
    
    for (int i = 0; i < thumbs.size(); i++) {
        thumbs[i]->drawThumb();
    }
    ofPopMatrix(); 
    
    
}