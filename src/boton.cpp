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
    botonVideo = false;
}



void boton::drawButton(){

    drawRound();
	
    if(activo)   ofDrawBitmapString(nombre, ofPoint(this->x + 5, this->y + 15));
}
void boton::drawButtonImgPlano(ofImage & img){
    //drawRound();
    //ofRect(this->x, this->y, this->width, this->height);
    ofPushStyle();
    ofSetColor(255, 255, 255, 255);
    img.draw(this->x,this->y);
    
    ofPopStyle();
}

void boton::drawButtonImg(ofImage & img){
    //drawRound();
    //ofRect(this->x, this->y, this->width, this->height);
    ofPushStyle();
    
    ofSetColor(0,0,0,150);
    ofRect(this->x+3, this->y+3, this->width * escala, this->height * escala);
    
    ofSetColor(color.r,color.g,color.b,255);
    ofRect(this->x, this->y, this->width * escala, this->height * escala);
    
	if(cambiandose){
		/// dibujamos la cortina
		ofSetColor(colorCambio);
		//ofRectRounded(this->x, this->y, this->width * escala, (this->height-cambioY) * escala ,16);
        ofRect(this->x, this->y, this->width * escala, (this->height-cambioY) * escala);
	}
    
    ofPopStyle();
    
    
    
    if(desactivado){
       
    }else{
        ofPushStyle();
        if(activo){
            ofSetColor(255, 255, 255, 255);
        }else {
            ofSetColor(255, 255, 255, 80);
        }
        img.draw(this->x,this->y);
        
        ofPopStyle();
    }
}

void boton::desactivate(){
    // no quieres ver el boton
    color.set(0,0,0);
    desactivado = true;
}

void boton::drawSintxt(){
    if(botonIdiomaCheck){
        ofSetColor(0, 0, 0, 190);
        //ofRectRounded(this->x+2, this->y+2, this->width, this->height,6);
        ofRect(this->x+2, this->y+2, this->width, this->height);
        
        ofSetColor(idiomaActivoColor.r, idiomaActivoColor.g, idiomaActivoColor.b, idiomaActivoColor.a);
        //ofRectRounded(this->x, this->y, this->width, this->height,6);
        ofRect(this->x, this->y, this->width, this->height);
    }else{
        
        ofSetColor(idiomaColor.r, idiomaColor.g, idiomaColor.b, idiomaColor.a);
        
        if(nombre != "ESP" && nombre != "FR"){
            ofRect(this->x, this->y, this->width, this->height);
        }else{
            if(nombre == "ESP"){
                ofRect(this->x, this->y, this->width, this->height);
            }else{
                ofRect(this->x, this->y, this->width, this->height);
            }
            
        }
    }
}

void boton::drawContxt(ofTrueTypeFont & fuente){
    ofPushStyle();
    
    if(botonIdiomaCheck){
       
        ofSetColor(0, 0, 0, 190);
        ofRectRounded(this->x+2, this->y+2, this->width, this->height,6);
        //ofRect(this->x+2, this->y+2, this->width, this->height);
        
        ofSetColor(idiomaActivoColor.r, idiomaActivoColor.g, idiomaActivoColor.b, idiomaActivoColor.a);
        ofRectRounded(this->x, this->y, this->width, this->height,6);
        //ofRect(this->x, this->y, this->width, this->height);
        
        
        ofSetColor(255);
        if(nombre != "FR" ){
            fuente.drawString(nombre, this->x + 10, this->y + 15);
        }else{
            fuente.drawString(nombre, this->x + 13, this->y + 15);
        }
        
    }else{
        ofSetColor(idiomaColor.r, idiomaColor.g, idiomaColor.b, idiomaColor.a);
       
        if(nombre != "ESP" && nombre != "FR"){
            ofRect(this->x, this->y, this->width, this->height);
        }else{
            if(nombre == "ESP"){
                ofRect(this->x, this->y, this->width, this->height);
                //ofRectRounded(this->x, this->y, this->width+4, this->height,6);
            }else{
                ofRect(this->x, this->y, this->width, this->height);
                //ofRectRounded(this->x, this->y, this->width, this->height,6);
            }
            
        }
        
        ofSetColor(20);
        if(nombre != "FR" ){
            fuente.drawString(nombre, this->x + 10, this->y + 15);
        }else{
            fuente.drawString(nombre, this->x + 13, this->y + 15);
        }
    }
    
   ofPopStyle();
}
