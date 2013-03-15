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
    void    setup();
	void    update();
	void    draw();
    void    cargaXml();
    
	void    _mouseDragged(ofMouseEventArgs &e);
	void    _mousePressed(ofMouseEventArgs &e);
	void    _mouseReleased(ofMouseEventArgs &e);

	void    _areaGrandeLista(string & s);
	void    collideWith( fichaInfo *_body );
    
    void    cambiaSeccion(int _cuala);
    void    cargaMinis(int _index);
    void    cargaImagenes();
    void    onCompleteCambio(float* arg);
	//
    // construccion de la figura
	void    construFigura();
	void    cambiaK(float v);
	void    cambiaDamp(float v);
	void    cambiaKDiagonal(float v);
	void    cambiaKHorizontal(float v);
	void    cambiaDampMiniaturas(float v);
    
    //
    // piezas para la figura
	vector<baseShape*>  rectangulos; /// el vector es para la colision entre ellos
	vector<Spring*> muelles;
    
	boton   btnImagenes;
	boton   btnCuadros;
	boton   btnPeriodicos;
    boton   castellano, gallego, ingles, frances;
    boton   cerrar;
    
    miniaturas  minis;
	visualizador    areaGrande;

    int totalFichas;
    int totalImagenes;
    int totalCuadros;
    int totalperiodicos;
    int	idLeader;
    int visualizadorWidth;
    int visualizadorheight;
    int seccionActiva;

    bool    abierta;
    bool    verIdiomas;
    bool    debesMorir;

    float   kmuelles, kMuellesDiagonales, kHorizontal;
    float   dampcajas, dampCajasMiniaturas;
    float   anchoGrande,    altoGrande;
    float px,py;
    
    ofTrueTypeFont  fuenteBotones;
    ofxXmlSettings  datosXml;
};
#endif