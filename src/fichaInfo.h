/*
 *  fichaInfo.h
 *  tactil
 *
 *  Created by ignacio garcia on 08/01/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef FICHA_INFO
#define FICHA_INFO

#include "boton.h"
#include "visualizador.h"
#include "Spring.h"
#include "ofxGui.h"
#include "miniaturas.h"


class fichaInfo {
public:
	fichaInfo();
	~fichaInfo();
	//////////////////////////////////////////////////////
    //////////////////////////////////////////////////////
    void setup();
	void update();
	void draw();
    
	void _mouseDragged(ofMouseEventArgs &e);
	void _mousePressed(ofMouseEventArgs &e);
	void _mouseReleased(ofMouseEventArgs &e);
	
	void    collideWith( fichaInfo *_body );
    
    
    void cambiaSeccion();
    void cargaMinis(int _index);
	//
    // construccion de la figura
	void construFigura();
	void cambiaK(float & v);
	void cambiaDamp(float & v);
    
    //
    // piezas para la figura
	vector<baseShape*> rectangulos; /// el vector es para la colision entre ellos
	vector<Spring*> muelles;
    
	boton btnImagenes;
	boton btnCuadros;
	boton btnPeriodicos;
    //boton btnInfo;
	visualizador areaGrande;
	
    //
    // parte del gui
    ofxPanel gui;
    ofxFloatSlider kMuelles;
    ofxFloatSlider dampCajas;
    
    ///
    // offset para el dragging
    ofVec2f offsetDrag;
    
    //
    // variables
	bool dragin;
	int	idLeader;
    float px,py;
    
    // vars gui
	float	kmuelles;
    float   dampcajas;
    
    // visualizador de miniaturas
    miniaturas minis;
};
#endif