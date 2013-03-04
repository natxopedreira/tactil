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
   // cajaTexto.loadFont("Trebuchet_MS.ttf", 10,90);
    fuente.loadFont("SegoeSb.ttf", 12,90, true);
    fuenteCuerpo.loadFont("SegoeL.ttf", 12,90, true);
    ofRegisterMouseEvents(this);
    
    verPie = false;
}
visualizador::~visualizador(){
    ofUnregisterMouseEvents(this);
}

void visualizador::drawVisualizador(){
     drawRound(); // la base
    
    int posxrect = this->x + 10;
    int posyrect = this->y + 10;
    int poswrect = this->width - 20 * this->escala;
    int poshrect = this->height-50 * this->escala;
    ofRectangle rect = fuente.getStringBoundingBox(titularPie, 0, 0);
    ofRectangle rectPie = fuenteCuerpo.getStringBoundingBox(pie, 0, 0);
    
    ofSetColor(color);
    if(verPie){
        ofRect(posxrect + poswrect, 
               posyrect + poshrect - rectPie.height, 
               rectPie.width + 40, 
               rectPie.height + 40);
    }
    
    ofSetColor(255, 255, 255);
    
    ofPushStyle();
    ofRect(posxrect, posyrect, poswrect, poshrect);
    
    if(imgVisible) imagen.draw(posxrect,posyrect);
    
    ofSetColor(0, 0, 0);
    
    
    fuente.drawString(titularPie, this->x + this->width - 20 - rect.width, this->y + this->height - 15);
    areaPieTitular.set(this->x + this->width - 20 - rect.width - 10, this->y + this->height - 15 - 10, rect.width + 20, rect.height + 20);
    
    
    if(verPie){
        fuenteCuerpo.drawString(pie, posxrect + this->width, posyrect + poshrect + 50 - rectPie.height - 10 );
    }
    
    

    
    ofPopStyle();
}

void visualizador::cargaImagen(string _url){
    imagen.loadImage("grande/" + _url);
    imgVisible = true;
}

void visualizador::ponTexto(string _titularPie,string _pie){
    pie = _pie;
    titularPie = _titularPie;
}

void visualizador::mouseMoved(ofMouseEventArgs & args){}
void visualizador::mouseDragged(ofMouseEventArgs & args){}
void visualizador::mousePressed(ofMouseEventArgs & args){}

void visualizador::mouseReleased(ofMouseEventArgs & args){
    if(areaPieTitular.inside(args.x, args.y)){
        cout << "ver mas " << endl;
        verPie = !verPie;
    }
}