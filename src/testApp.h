#pragma once

#include "ofMain.h"
#include "fichaInfo.h"
#include "ofxGui.h"

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

		// parte del gui
		ofxPanel gui;
		ofxFloatSlider kMuelles;
		ofxFloatSlider dampCajas;
	
		float	kmuelles;
		float   dampcajas;
		
	vector<fichaInfo *> fichas;
	
};