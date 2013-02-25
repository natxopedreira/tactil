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
#include "ofxTextSuite.h"

class visualizador : public baseShape {
public:
	visualizador();
	~visualizador();
    
    void    cargaImagen(string _url);
    void drawVisualizador();
    
    void ponTexto(string _cualo);
    
    ofxTextBlock cajaTexto;
    
private:
    ofImage     imagen;
    bool        imgVisible;
};
#endif