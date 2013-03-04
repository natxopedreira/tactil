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

    fuente.loadFont("SegoeSbI.ttf", 13,90, true);
    fuenteCuerpo.loadFont("SegoeL.ttf", 12,90, true);
    fuenteCuerpo.setLineHeight(20);
    
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
        if(cont < posxrect + poswrect){
            cont += 15;
            ofRect(cont, 
                   posyrect + poshrect - rectPie.height, 
                   rectPie.width + 40, 
                   rectPie.height + 40);
        }else{
            ofRect(posxrect + poswrect, 
                   posyrect + poshrect - rectPie.height, 
                   rectPie.width + 40, 
                   rectPie.height + 40);
        }
    }
    
    ofSetColor(255, 255, 255);
    
    ofPushStyle();
    ofRect(posxrect, posyrect, poswrect, poshrect);
    
    if(imgVisible) imagen.draw(posxrect,posyrect);
    
    ofSetColor(0, 0, 0);
    
    
    fuente.drawString(titularPie, this->x + this->width - 20 - rect.width, this->y + this->height - 15);
    areaPieTitular.set(this->x + this->width - 20 - rect.width - 10, this->y + this->height - 15 - 10, rect.width + 20, rect.height + 20);
    
    
    if(verPie && (cont >= posxrect + poswrect)){
        fuenteCuerpo.drawString(pie, posxrect + this->width, posyrect + poshrect + 50 - rectPie.height - 10 );
    }
    
    //ofRect(areaPieTitular.x, areaPieTitular.y, areaPieTitular.width, areaPieTitular.height);
    //ofRect(this->x, this->y, this->width, this->height);
    
    ofPopStyle();
}

void visualizador::cargaImagen(string _url){
    imagen.loadImage("grande/" + _url);
    imgVisible = true;
}

void visualizador::ponTexto(string _titularPie,string _pie){
    pie = _pie;
    titularPie = _titularPie;
    cont = this->x + 200;
}

void visualizador::mouseDragged(ofMouseEventArgs & args){
        /// estas drageando un boton o el visualizador
    if(drag){
        ofPoint p = this->getCenter();
        ofPoint diff	= ofPoint(args.x, args.y) - p;
        ofPoint destino = ofPoint(args.x, args.y) - diff/2;
        moveTo(diff.x+offsetDrag.x,diff.y+offsetDrag.y);
    }
}

void visualizador::mousePressed(ofMouseEventArgs & args){
    ofRectangle rt;
    rt.set(this->x, this->y, this->width, this->height);
    cout << "presss" << endl;
    if(rt.inside(args.x, args.y)){
        offsetDrag.set(this->getCenter().x-args.x,this->getCenter().y-args.y);
        drag = true;
    }
}

void visualizador::mouseReleased(ofMouseEventArgs & args){
    if(areaPieTitular.inside(args.x, args.y)){
        verPie = !verPie;
    }
    if(this->inside(args.x, args.y)){
        drag = false;
        offsetDrag.set(0, 0);
    }
}

void visualizador::mouseMoved(ofMouseEventArgs & args){}