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
    drawRound();
    ofDrawBitmapString(nombre, ofPoint(this->x + 5, this->y + 15));
}

void thumb::activalo(){
    activo = true;
    escala = 2.0;
}

void thumb::desactivalo(){
    activo = false;
    escala = 1.0;
}