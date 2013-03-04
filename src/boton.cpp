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
}

boton::~boton(){
}

void boton::drawButton(){
   drawRound();
	if(activo)   ofDrawBitmapString(nombre, ofPoint(this->x + 5, this->y + 15));
}

void boton::desactivate(){
    // no quieres ver el boton
    color.set(0,0,0);
    desactivado = true;
}