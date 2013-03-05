//
//  thumb.cpp
//  tactil
//
//  Created by natxo pedreira on 15/01/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "thumb.h"

thumb::thumb(){
    nombre = "";
    activo = false;
    escala = 1.0;
    offsetDragThumb.set(0,0);
}

thumb::~thumb(){
    ofUnregisterMouseEvents(this);
}
void thumb::ponListeners(){
    ofRegisterMouseEvents(this);
}
void thumb::urdate(){
    update();
}

void thumb::drawThumb(){
    //drawRound();
	ofPushStyle();
	ofSetColor(color);
	roundedRect(x-((width-cambioY)/2) + width/2, y-((height-cambioY)/2) + height/2, (width-cambioY) * escala, (height-cambioY) * escala, 5);
    
	ofPopStyle();
    if(img.getWidth()>0 && cambioY<.1) img.draw(x + 5, y + 5, 35, 35);
    
    
    if (activo) {
        /// si la mini esta pulsada le ponemos un border
        ofPushStyle();
        ofSetColor(255);
        ofNoFill();
        ofSetLineWidth(2);
        roundedRect(x-((width-cambioY)/2) + width/2, y-((height-cambioY)/2) + height/2, (width-cambioY) * escala, (height-cambioY) * escala, 5);
        
        ofPopStyle();
    }
}

void thumb::activala(){
    activo = true;
}

void thumb::desactivala(){
    activo = false;
}
void thumb::mouseDragged(ofMouseEventArgs & args){
    /// estas drageando un boton o el visualizador
    if(dragBoton){
        ofPoint p = getCenter();
        ofPoint diff	= ofPoint(args.x, args.y) - p;
        ofPoint destino = ofPoint(args.x, args.y) - diff/2;
        cout << diff.x << "," << diff.y << endl;
        // moveTo(diff.x+offsetDragThumb.x,diff.y+offsetDragThumb.y);
    }
}

void thumb::mousePressed(ofMouseEventArgs & args){
    if(inside(args.x, args.y)){
        offsetDragThumb.set(0, 0);
        dragBoton = true;
    }
}

void thumb::mouseReleased(ofMouseEventArgs & args){
    if(dragBoton){
        dragBoton = false;
        offsetDragThumb.set(0, 0);
    }
}

void thumb::mouseMoved(ofMouseEventArgs & args){}