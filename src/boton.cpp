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
}

boton::~boton(){}

void boton::drawButton(){
   drawRound();
   ofDrawBitmapString(nombre, ofPoint(this->x + 5, this->y + 15));
}