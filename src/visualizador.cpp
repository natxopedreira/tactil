/*
 *  visualizador.cpp
 *  tactil
 *
 *  Created by ignacio garcia on 08/01/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "visualizador.h"

visualizador::visualizador(){}
visualizador::~visualizador(){}

void visualizador::drawVisualizador(){
     drawRound(); // la base
     ofRect(this->x + 10,this->y + 10,this->width - 20,this->height-50);
}