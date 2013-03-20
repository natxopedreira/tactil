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
    
    botonClose = false;
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
       
        ofSetColor(0, 0, 0, 190);
        roundedRect(this->x+2, this->y+2, this->width, this->height,6);
        
        ofSetColor(idiomaActivoColor.r, idiomaActivoColor.g, idiomaActivoColor.b, idiomaActivoColor.a);
        roundedRect(this->x, this->y, this->width, this->height,6);
    }else{
        ofSetColor(idiomaColor.r, idiomaColor.g, idiomaColor.b, idiomaColor.a);
       
        if(nombre != "ESP" && nombre != "FR"){
            ofRect(this->x, this->y, this->width, this->height);
        }else{
            roundedRect(this->x, this->y, this->width, this->height,6);
        }
        // roundedRect(this->x, this->y, this->width, this->height,6);
    }
    
    
    //
    //drawRound();
    
    ofPushStyle();
    if(botonIdiomaCheck){
        ofSetColor(255);
    }else{
        ofSetColor(20);
    }
            
    if(botonIdiomaCheck){
        if(nombre != "FR" ){
            fuente.drawString(nombre, this->x + 8, this->y + 15);
        }else{
            fuente.drawString(nombre, this->x + 12, this->y + 15);
        }
        
    }else if(nombre == "FR"){
        fuente.drawString(nombre, this->x + 12, this->y + 15);
    }else {
        fuente.drawString(nombre, this->x + 5, this->y + 15);
    }
   ofPopStyle();
}
