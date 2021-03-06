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
    
    posicion.set(ofPoint(_pos.x-ancho/2, _pos.y-alto/2));
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
        
        ofSetColor(255,255,255, 255);
    
        string nome = ofToString(numeroXml);
        int largo = nome.length();
        int desfase = 11;
        if(largo>1) desfase = 7;
        ofDrawBitmapString(nome, ofPoint(posicion.x + desfase,posicion.y + 20));
    

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