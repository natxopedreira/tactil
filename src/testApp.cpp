#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
	ofEnableSmoothing();
	ofBackground(84,78,110);
	dampcajas = 0.3;
    kmuelles = 0.0025;
	/// gui para el modo debug
    gui.setup("ajustes");
    gui.add(kMuelles.setup("k muelles", kmuelles, .0, .5));
    gui.add(dampCajas.setup("damp cajas", dampcajas, .0, .5));
    
    kMuelles.addListener(this, &testApp::btnCambiaK);
    dampCajas.addListener(this, &testApp::btnCambiaDamp);
	
	fichaInfo * ficha = new fichaInfo();
	ficha->setup();
	
	fichaInfo * ficha2 = new fichaInfo();
	ficha2->setup();

	fichas.push_back(ficha);
   // fichas.push_back(ficha2);
        
}
//--------------------------------------------------------------
void testApp::btnCambiaK(float & v){
    /// seteamos un nuevo valor k para los muelles
	for(int i = 0; i < fichas.size(); i++){
		fichas[i]->cambiaK(v);
		
	}

}
//--------------------------------------------------------------
void testApp::btnCambiaDamp(float & v){
    /// seteamos un nuevo valor k para los muelles
	for(int i = 0; i < fichas.size(); i++){
		fichas[i]->cambiaDamp(v);
	}
}



//--------------------------------------------------------------
void testApp::update(){
	for(int i = 0; i < fichas.size(); i++){
		fichas[i]->update();
        for(int j = 0; j < fichas.size(); j++){
         if(i != j )fichas[i]->collideWith(fichas[j]);
        }
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	for(int i = 0; i < fichas.size(); i++){
		fichas[i]->draw();
	}

    ofDrawBitmapString(ofToString(ofGetFrameRate()), 50, 50);
    gui.draw();
}