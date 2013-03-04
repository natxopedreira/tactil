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

thumb::~thumb(){

}

void thumb::urdate(){
    update();
}

void thumb::drawThumb(){
    //drawRound();
	ofPushStyle();
	ofSetColor(color);
	roundedRect(this->x-((this->width-cambioY)/2) + this->width/2, this->y-((this->height-cambioY)/2) + this->height/2, (this->width-cambioY) * escala, (this->height-cambioY) * escala, 5);
    
	ofPopStyle();
    if(img.getWidth()>0 && cambioY<.1) img.draw(this->x + 5, this->y + 5, 35, 35);
    
    
    if (activo) {
        /// si la mini esta pulsada le ponemos un border
        ofPushStyle();
        ofSetColor(255);
        ofNoFill();
        ofSetLineWidth(2);
        roundedRect(this->x-((this->width-cambioY)/2) + this->width/2, this->y-((this->height-cambioY)/2) + this->height/2, (this->width-cambioY) * escala, (this->height-cambioY) * escala, 5);
        
        ofPopStyle();
    }
}

void thumb::activala(){
    activo = true;
}

void thumb::desactivala(){
    
    activo = false;
}
