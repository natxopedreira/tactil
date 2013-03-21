#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
    ofSetCircleResolution(50);
	ofBackground(255,0,0);
    
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
	ficha->setup("interactivo.xml");

	fichas.push_back(ficha);
    
    veloBlur.allocate(1920, 1080);
    
    veloBlur.begin();
    ofClear(0);
    veloBlur.end();
    
    //blur.setup(1920, 1080, 4, .1, 4);
}

//--------------------------------------------------------------
void testApp::update(){
    Tweenzor::update( ofGetElapsedTimeMillis() );
    
    for (int i = fichas.size()-1; i >= 0 ; i--){
        fichas[i]->update();
        if (!fichas[i]->debesMorir ){
            for (int j = i; j >= 0; j--){
                if (j != i)
                    if ((fichas[i]->areaGrande.intersects( fichas[j]->areaGrande )) && (fichas[j]->areaGrande.leader)){
                        fichas[j]->areaGrande.addRepulsionForce( &fichas[i]->areaGrande, 800, 100);
                    }
            }
        } else {
            delete fichas[i];
            fichas.erase(fichas.begin()+i);
        }
    }
    /*
    veloBlur.begin();
    ofClear(0);
    ofSetColor(0,0,0,180);
    ofRect(0,0,1920,1080);
    ofTranslate(3, 3);
    
    for (vector<fichaInfo*>::iterator itFichas = fichas.begin(); itFichas!=fichas.end(); ++itFichas) {
        (*itFichas)->drawSombra();
    }
    veloBlur.end();
   */
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(255, 255,255,255);
    plano.draw(0, 0);
    
    ofSetColor(0,0,0,180);
    ofRect(0,0,1920,1080);
  //  veloBlur.draw(0, 0);
    
    ofSetColor(255, 255,255,255);
    for (vector<fichaInfo*>::iterator itFichas = fichas.begin(); itFichas!=fichas.end(); ++itFichas) {
        (*itFichas)->draw();
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
	ficha->setup("interactivo.xml");
    
	fichas.push_back(ficha);
}

