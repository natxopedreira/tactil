/*
 *  boton.cpp
 *  tactil
 *
 *  Created by ignacio garcia on 08/01/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "boton.h"

boton::boton(){
    nombre = "";
	activo = false;
    
    idiomaColor.set(200,200,200);
    idiomaActivoColor.set(200,200,200);
    botonIdiomaCheck = false;
}

boton::~boton(){

}


void boton::drawButton(){

    drawRound();
	
    if(activo)   ofDrawBitmapString(nombre, ofPoint(this->x + 5, this->y + 15));
}

void boton::desactivate(){
    // no quieres ver el boton
    color.set(0,0,0);
    desactivado = true;
}

void boton::drawContxt(ofTrueTypeFont & fuente){
    if(botonIdiomaCheck){
        ofSetColor(idiomaActivoColor.r, idiomaActivoColor.g, idiomaActivoColor.b);
    }else{
        ofSetColor(idiomaColor.r, idiomaColor.g, idiomaColor.b, 200);
    }
    
    roundedRect(this->x, this->y, this->width, this->height,5);
    //drawRound();
    
    ofPushStyle();
        ofSetColor(20);
        fuente.drawString(nombre, this->x + 5, this->y + 15);
    ofPopStyle();
}
