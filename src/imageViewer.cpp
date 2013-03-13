//
//  imageViewer.cpp
//  tactil
//
//  Created by ignacio pedreira gonzalez on 10/03/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "imageViewer.h"

imageViewer::imageViewer(){}
imageViewer::~imageViewer(){}

void imageViewer::setup(float _anchoMax, float _altoMax){
    anchoMax = _anchoMax;
    altoMax = _altoMax;
    fbo.allocate(_anchoMax, _altoMax, GL_RGB);
   // 
    fbo.begin();
    ofClear(255);
    fbo.end();
    
    escalaX = 1;
    escalaY = 1;
}
void imageViewer::cambiaTamano(float _nuevoAlto){
    
    if(altoMax != _nuevoAlto){
        altoMax = _nuevoAlto;
        fbo.allocate(anchoMax, altoMax);
    }
}

void imageViewer::update(){
    fbo.begin();
    ofPushMatrix();
        ofClear(255);
        ofSetColor(255);
        ofScale(escalaX, escalaY);
            if(imagen.isAllocated()){
                imagen.draw(0,0, imagen.width, imagen.height);
            }
    ofPopMatrix();
    fbo.end();
}

void imageViewer::draw(float _px, float _py){
    if(imagen.isAllocated()) fbo.draw(_px, _py);
}

void imageViewer::cargaImagen(string _url){
    imagen.loadImage(_url);
    float ratio = imagen.getWidth()/imagen.getHeight();
    
    escalaX = anchoMax / imagen.getWidth();
    escalaY = altoMax / imagen.getWidth()*ratio;
}