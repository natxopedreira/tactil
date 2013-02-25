/*
 *  visualizador.cpp
 *  tactil
 *
 *  Created by ignacio garcia on 08/01/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "visualizador.h"

visualizador::visualizador(){
    imgVisible = false;
    cajaTexto.loadFont("Trebuchet_MS.ttf", 10,90);

}
visualizador::~visualizador(){
    
}

void visualizador::drawVisualizador(){
     drawRound(); // la base
    ofPushStyle();
     ofRect(this->x + 10,this->y + 10,this->width - 20 * this->escala,this->height-50 * this->escala);
    
     if(imgVisible) imagen.draw(this->x + 10,this->y + 10);
    
    ofSetColor(0, 0, 0);
    
    cajaTexto.draw(this->x + 20,this->y + 20,this->width - 40 * this->escala,this->height-50 * this->escala);
    
    ofPopStyle();
}

void visualizador::cargaImagen(string _url){
    imagen.loadImage("grande/" + _url);
    imgVisible = true;
}

void visualizador::ponTexto(string _cualo){
    cajaTexto.setText(_cualo);
}