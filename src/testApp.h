#pragma once

#include "ofMain.h"
#include "ofxTuio.h"
#include "ofxGui.h"
#include "ofxTweenzor.h"

/// clases perso
#include "fichaInfo.h"
#include "mar.h"
#include "controllerHotSpot.h"
/*
 quiero crear una clase fichaInfo para mostrar todos
 los contenidos de un punto en el mapa
 
 la idea es tener luego un xml donde aparezca
 toda la info de cada uno de los puntos, con esa info
 se asignaran los contenidos a cada instancia
 de fichaInfo
 */

class testApp : public ofBaseApp{

	public:
		void    setup();
		void    update();
		void    draw();
		
		void    btnCambiaK(float & v);
		void    btnCambiaDamp(float & v);
	
		void    btnCambiaKHorizontal(float & v);
		void    btnCambiaKDiagonal(float & v);
		void    btnCambiaDampMiniaturas(float & v);
        void    editarPuntos(bool & r);
        void    guardarPuntos(bool & r);
        void    keyPressed(int key);
    
        void    verFicha(customDataEvent & info);
    
        void    lanzaFicha();
		// ---------------------- parte del gui
		ofxPanel gui;
		ofxFloatSlider kMuelles;
		ofxFloatSlider kMuellesDiagonales;
		ofxFloatSlider kMuellesHorizontales;
		ofxFloatSlider dampCajas;
		ofxFloatSlider dampCajasMiniaturas;
        ofxToggle   puntosDebug;
        ofxToggle   guardarPosicionesPuntos;
        ofxLabel    fps;
	
		float	kmuelles, kmuellesDiagonales, kmuellesHorizontales;
		float   dampcajas, dampcajasMiniaturas;
        bool    verGui;
    
		// ---------------------- 
        ofImage ciudad, ciudadMask, leyenda;
        ofShader mascara;
        ofxTuioClient   tuioClient;
        vector<fichaInfo *> fichas;
        mar animacionFondo;
        controllerHotSpot puntosMapa;
};