/*
 *  visualizador.h
 *  tactil
 *
 *  Created by ignacio garcia on 08/01/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef VISUALIZADOR
#define VISUALIZADOR

#include "baseShape.h"

class visualizador : public baseShape {
public:
	visualizador();
	~visualizador();
    
    void drawVisualizador();
};
#endif