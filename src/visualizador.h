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
#include "boton.h"

#include "SimplePanZoom.h"

class visualizador : public baseShape {
public:
	visualizador();
	~visualizador();

    void    setup();
    void    update();
    void    drawVisualizador();
    void    drawVisualizadorSombra();
    
    void    cargaImagen(string _url);
    void    ponTexto(string _titularPie,string _pie, string _informacion);
    
    void    mouseDragged(ofMouseEventArgs & args);
    void    mousePressed(ofMouseEventArgs & args);
    void    mouseReleased(ofMouseEventArgs & args);
    void    mouseMoved(ofMouseEventArgs & args);

    boton   btnInfo;
    ofImage imagenBtnInfo;
    SimplePanZoom visorZoom;
    ofImage imagenZoom;
    
    ofRectangle areaPieTitular;
    ofTrueTypeFont  fuente,fuenteCuerpo, fuenteInfo;
    ofVec2f offsetDrag;
    
    string  titularPie, pie, informacion;
    
    float   altoTexto,altoTextoInfo;
    float   desfaseAltoTextoInfo;
    
    bool    verPie;
    
    int cont;
    int posxrect;
    int posyrect;
    int poswrect;
    int poshrect;
    
private:
    ofImage imagen;
    
    bool    imgVisible;
    bool    drag;
    bool    verInfo;
    ofPoint mousePrev;
    
    string  wrapString(string text, int width, ofTrueTypeFont & _ft);
};
#endif