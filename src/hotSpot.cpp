//
//  hotSpot.cpp
//  tactil
//
//  Created by ignacio pedreira gonzalez on 01/04/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "hotSpot.h"


hotSpot::hotSpot(){
    
    posicion.set(0, 0);
    editable = false;
}

// ------------------------------
void hotSpot::setup(int _numXml){
    ancho = 30;
    alto = 30;
    
    numeroXml = _numXml;
}

// ------------------------------
void hotSpot::setPosition(ofPoint _pos){
    posicion.set(_pos);
}

// ------------------------------
void hotSpot::udpate(){

}

// ------------------------------
void hotSpot::draw(){
    
    ofPushStyle();
        ofSetColor(0, 0, 0, 150);
        //ofRect(posicion.x + 2,posicion.y + 2, ancho,alto);
        ofRectRounded(posicion.x + 2,posicion.y + 2, ancho,alto, 8);
    
        ofSetColor(199, 81, 35, 255);
        ofRectRounded(posicion.x,posicion.y, ancho,alto, 8);
        
        ofSetColor(0, 0, 0, 255);
        ofDrawBitmapString(ofToString(numeroXml), ofPoint(posicion.x + 10,posicion.y + 20));
    

    ofPopStyle();
}

// ------------------------------
ofPoint hotSpot::damePos(){
    return posicion;
}

// ------------------------------
int hotSpot::dameIndex(){
    return numeroXml;
}