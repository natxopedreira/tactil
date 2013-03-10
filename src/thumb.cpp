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
}

thumb::~thumb(){}
void thumb::ponListeners(){}
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