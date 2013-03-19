//
//  imageViewer.cpp
//  tactil
//
//  Created by ignacio pedreira gonzalez on 10/03/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "imageViewer.h"

imageViewer::imageViewer(){
    esVideo = false;
}

// ---------------------------------------
imageViewer::~imageViewer(){}

// ---------------------------------------
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

// ---------------------------------------
float imageViewer::getAltoMax(){
    return altoMax;
}

// ---------------------------------------
float imageViewer::getAnchoMax(){
    return anchoMax;
}


// ---------------------------------------
void imageViewer::update(){
    if(esVideo) vidrio.update();
    
    fbo.begin();
    ofPushMatrix();
    ofClear(255);
    ofSetColor(255);
    ofScale(escalaX, escalaY);
    if(imagen.isAllocated() && !esVideo){
        imagen.draw(0,0, imagen.width, imagen.height);
        
    }else if(esVideo){
        vidrio.draw(0,0, 320,240);
    }
    ofPopMatrix();
    fbo.end();
}

// ---------------------------------------
void imageViewer::draw(float _px, float _py){
    if(imagen.isAllocated() && !esVideo) fbo.draw(_px, _py);
}

// ---------------------------------------
void imageViewer::cambiaTamano(float _nuevoAlto){
    
    if(altoMax != _nuevoAlto){
        altoMax = _nuevoAlto;
        fbo.allocate(anchoMax, altoMax);
    }
}

// ---------------------------------------
void imageViewer::cargaImagen(string _url){
    string extensionArchivo = _url.substr(_url.find("."),_url.length());
    
    if(extensionArchivo != ".mov"){
    
        imagen.loadImage(_url);
        float ratio = imagen.getWidth()/imagen.getHeight();
    
        escalaX = anchoMax / imagen.getWidth();
        escalaY = altoMax / imagen.getWidth()*ratio;
    }else{
        // eres un vidrio
        esVideo = true;
        vidrio.loadMovie(_url);
        
        float ratio = vidrio.getWidth()/vidrio.getHeight();
        escalaX = anchoMax / vidrio.getWidth();
        escalaY = altoMax / vidrio.getWidth()*ratio;
    }

}