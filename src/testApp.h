#pragma once

#include "ofMain.h"
#include "fichaInfo.h"
#include "ofxGui.h"
#include "ofxTweenzor.h"
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
		void setup();
		void update();
		void draw();
		
		void btnCambiaK(float & v);
		void btnCambiaDamp(float & v);
	
		void btnCambiaKHorizontal(float & v);
		void btnCambiaKDiagonal(float & v);
		void btnCambiaDampMiniaturas(float & v);
        void keyPressed(int key);
    
		// parte del gui
		ofxPanel gui;
		ofxFloatSlider kMuelles;
		ofxFloatSlider kMuellesDiagonales;
		ofxFloatSlider kMuellesHorizontales;
		ofxFloatSlider dampCajas;
		ofxFloatSlider dampCajasMiniaturas;
	
		float	kmuelles, kmuellesDiagonales, kmuellesHorizontales;
		float   dampcajas, dampcajasMiniaturas;
    
    ofImage plano;
    ofFbo   veloBlur;

	vector<fichaInfo *> fichas;
};