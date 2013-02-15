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
#include "miniaturas.h"
#include "ofxXmlSettings.h"
/*
 ANIMACION ES
 
 - BOTON SECCION CLICK
 - CORTINA VISUALIZADOR
 - CARGAS MINIARUAS
 - CORTINAS MINIATURAS
 */


class fichaInfo {
public:
	fichaInfo();
	~fichaInfo();
	//////////////////////////////////////////////////////
    //////////////////////////////////////////////////////
    void setup();
	void update();
	void draw();
    void    cargaXml();
    
	void _mouseDragged(ofMouseEventArgs &e);
	void _mousePressed(ofMouseEventArgs &e);
	void _mouseReleased(ofMouseEventArgs &e);
	
	void _areaGrandeLista(string & s);
	
	void  collideWith( fichaInfo *_body );
    
    
    void    cambiaSeccion(int _cuala);
    void    cargaMinis(int _index);
    void    cargaImagenes();
	//
    // construccion de la figura
	void construFigura();
	void cambiaK(float v);
	void cambiaDamp(float v);
	void cambiaKDiagonal(float v);
	void cambiaKHorizontal(float v);
	void cambiaDampMiniaturas(float v);
    
    
    void onCompleteCambio(float* arg);
    
    //
    // piezas para la figura
	vector<baseShape*> rectangulos; /// el vector es para la colision entre ellos
	vector<Spring*> muelles;
    
	boton btnImagenes;
	boton btnCuadros;
	boton btnPeriodicos;
    //boton btnInfo;
	visualizador areaGrande;

    
    ///
    // offset para el dragging
    ofVec2f offsetDrag;
    
    //
    // variables
	bool dragin, dragingMini;
	int	idLeader;
    float px,py;
	int seccionActiva;
    
    // vars gui
	float	kmuelles, kMuellesDiagonales, kHorizontal;
    float   dampcajas, dampCajasMiniaturas;
    
    // visualizador de miniaturas
    miniaturas minis;
    
    //
    bool    abierta; //// animacion de inicio de ficha
    float   anchoGrande,    altoGrande;
    
    ofxXmlSettings datosXml;
};
#endif