/*
 *  boton.h
 *  tactil
 *
 *  Created by ignacio garcia on 08/01/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef BOTON
#define BOTON

#include "baseShape.h"

class boton : public baseShape {
public:
    boton();
    
	
    void    drawButton();
    void    drawContxt(ofTrueTypeFont & fuente);
    void    desactivate();
    
    ofColor idiomaActivoColor,idiomaColor;
    bool    botonIdiomaCheck;
    bool    botonClose;
};
#endif