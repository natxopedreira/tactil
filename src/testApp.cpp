#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
	ofEnableSmoothing();
	ofBackground(40,40,40);
	//ofSetLogLevel(OF_LOG_VERBOSE);
    
    Tweenzor::init();
    
	dampcajas = 0.3;
	dampcajasMiniaturas = 0.3;
	
    kmuelles = 0.0325;
	kmuellesDiagonales = 0.0325;
	kmuellesHorizontales = 0.0325;
	
	/// gui para el modo debug
    gui.setup("ajustes");
    gui.add(kMuelles.setup("k muelles", kmuelles, .0, 1));
	gui.add(kMuellesHorizontales.setup("k horiz", kmuellesHorizontales, .0, 1));
	gui.add(kMuellesDiagonales.setup("k diag", kmuellesDiagonales, .0, 1));
    gui.add(dampCajasMiniaturas.setup("damp miniaturas", dampcajasMiniaturas, .0, 5));
    gui.add(dampCajas.setup("damp cajas", dampcajas, .0, 5));
    
	gui.loadFromFile("settings.xml");
	
    kMuelles.addListener(this, &testApp::btnCambiaK);
	kMuellesHorizontales.addListener(this, &testApp::btnCambiaKHorizontal);
	kMuellesDiagonales.addListener(this, &testApp::btnCambiaKDiagonal);
    dampCajasMiniaturas.addListener(this, &testApp::btnCambiaDampMiniaturas);
	dampCajas.addListener(this, &testApp::btnCambiaDamp);
	
    plano.loadImage("plano.jpg");
    
    /////////////////////
    /////////////////////
	fichaInfo * ficha = new fichaInfo();
	ficha->setup();

	fichas.push_back(ficha);
}


//--------------------------------------------------------------
void testApp::update(){
    Tweenzor::update( ofGetElapsedTimeMillis() );
    
	for(int i = 0; i < fichas.size(); i++){
        for (int j = 0; j < fichas.size(); j++) {
            
            if(j!=i){
                if(fichas.at(i)->areaGrande.intersects(fichas.at(j)->areaGrande)){
                    if(fichas.at(j)->areaGrande.leader) fichas.at(j)->areaGrande.addRepulsionForce(&fichas.at(i)->areaGrande, 800, 100);
                }
            }
        }
		fichas[i]->update();
	}
}

//--------------------------------------------------------------
void testApp::draw(){
    plano.draw(0, 0);
    
	for(int i = 0; i < fichas.size(); i++){
		fichas[i]->draw();
	}
    
    ofDrawBitmapString(ofToString(ofGetFrameRate()), 50, 50);
    gui.draw();
}


/*
 //////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////
 /////////////////////////////////////////////// ZONA GUI /////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////
 */



//--------------------------------------------------------------
void testApp::btnCambiaK(float & v){
    /// seteamos un nuevo valor k para los muelles
	for(int i = 0; i < fichas.size(); i++){
		fichas[i]->cambiaK(v);
	}
}
//--------------------------------------------------------------
void testApp::btnCambiaDamp(float & v){
    /// seteamos un nuevo valor damp para los rectangles
	for(int i = 0; i < fichas.size(); i++){
		fichas[i]->cambiaDamp(v);
	}
}
//--------------------------------------------------------------
void testApp::btnCambiaKDiagonal(float & v){
    /// seteamos un nuevo valor k para los muelles
	for(int i = 0; i < fichas.size(); i++){
		fichas[i]->cambiaKDiagonal(v);
	}
}
//--------------------------------------------------------------
void testApp::btnCambiaKHorizontal(float & v){
    /// seteamos un nuevo valor k para los muelles
	for(int i = 0; i < fichas.size(); i++){
		fichas[i]->cambiaKHorizontal(v);
	}
}
//--------------------------------------------------------------
void testApp::btnCambiaDampMiniaturas(float & v){
    /// seteamos un nuevo valor damp para las miniaturas
	for(int i = 0; i < fichas.size(); i++){
		fichas[i]->cambiaDampMiniaturas(v);
	}
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    fichaInfo * ficha = new fichaInfo();
	ficha->setup();
    
	fichas.push_back(ficha);
}

