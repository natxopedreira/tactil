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
    
    void    cargaImagen(string _url);
    void drawVisualizador();
    void ponListeners();
    
    void ponTexto(string _titularPie,string _pie);
    
    ofTrueTypeFont fuente,fuenteCuerpo;
    string titularPie, pie;
    
    void mouseMoved(ofMouseEventArgs & args);
    void mouseDragged(ofMouseEventArgs & args);
    void mousePressed(ofMouseEventArgs & args);
    void mouseReleased(ofMouseEventArgs & args);
    
    ofRectangle areaPieTitular;
    bool        verPie;
    int     cont;
    float   altoTexto;
    
    // offset para el dragging
    ofVec2f offsetDrag;
    
private:
    ofImage     imagen;
    bool        imgVisible;
    bool drag;
    
    string wrapString(string text, int width);
};
#endif