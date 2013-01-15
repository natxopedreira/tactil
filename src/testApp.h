#pragma once

#include "ofMain.h"
#include "fichaInfo.h"
#include "ofxGui.h"

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