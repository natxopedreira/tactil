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

#ifdef USE_TUIO
#include "ofxTuio.h"
#endif

struct tCursor {
	int	idN;
	ofVec2f loc;
};

class visualizador : public baseShape {
public:
	visualizador();
	~visualizador();

    void    setup();
    void    update();
    void    drawVisualizador();
    void    drawVisualizadorSombra();
    
    void    cargaImagen(string _url);
    void    cargaVideo(string _url);
    
    void    ponTexto(string _titularPie,string _pie, string _informacion);
    
    

#ifdef USE_TUIO
    /// tuio
    void tuioAdded(ofxTuioCursor & tuioCursor);
    void tuioRemoved(ofxTuioCursor & tuioCursor);
    void tuioUpdated(ofxTuioCursor & tuioCursor);
#else
    void mouseDragged(ofMouseEventArgs & arg);
    void mousePressed(ofMouseEventArgs & arg);
    void mouseReleased(ofMouseEventArgs & arg);
#endif

    
    boton   btnInfo;
    ofImage imagenBtnInfo;
    SimplePanZoom visorZoom;
    ofImage imagenZoom;
    ofFbo   fboImageZoom;
    
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
    //int posxrect;
    //int posyrect;
    int poswrect;
    int poshrect;
    bool    tieneVideo;
    bool    verVidrio;
    
    ofVec2f         pos,vel,acc;
    
    ofVideoPlayer   videoplayer;
private:
    ofImage imagen;
    ofImage gestos;
    
    bool    imgVisible;
    ofPoint mousePrev;
    
    /// para tuio
    vector<tCursor>	cursorsOnBorder;
	ofVec2f         oldLoc[3];
    
    
    string  wrapString(string text, int width, ofTrueTypeFont & _ft);
};
#endif