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

#define USE_TUIO



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
    
#ifdef USE_TUIO
    
#else
    void    mouseDragged(ofMouseEventArgs & args);
    void    mousePressed(ofMouseEventArgs & args);
    void    mouseReleased(ofMouseEventArgs & args);
    void    mouseMoved(ofMouseEventArgs & args);
#endif
    
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
    bool    drag;
    bool    verInfo;
    
    int cont;
    int posxrect;
    int posyrect;
    int poswrect;
    int poshrect;
    
private:
    ofImage imagen;
    ofImage gestos;
    
    bool    imgVisible;
    
    
    ofPoint mousePrev;
    
    string  wrapString(string text, int width, ofTrueTypeFont & _ft);
};
#endif