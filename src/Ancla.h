//
//  Ancla.h
//  tactil
//
//  Created by natxo pedreira on 01/02/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//


//  NOTA NOTA NOTA
//  variante de un spring pero rigido
//  es para conectar las minis al visualizador

#ifndef ANCLA
#define ANCLA

#include "ofMain.h"
#include "baseShape.h"
#include "visualizador.h"
#include "thumb.h"

class Ancla {
public:
    Ancla();
	~Ancla();
	
    void update();
    void draw();
    
    baseShape * rectA; // esto es el visualizador
    baseShape * rectB; // esto es un thumb
	
    float dist;
    float k;	 // this is the k, Springiness constant
	bool	visible;
	
	int	indiceA;	//es el indice  del rectA para saber cual de los puntos que forman en rectangle es el ancla
	int	indiceB;	//es el indice  del rectB para saber cual de los puntos que forman en rectangle es el ancla
    
};
#endif
