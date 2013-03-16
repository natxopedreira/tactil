#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
	ofBackground(40,40,40);
    
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
}


//--------------------------------------------------------------
void testApp::update(){
    Tweenzor::update( ofGetElapsedTimeMillis() );

    
    for (vector<fichaInfo*>::reverse_iterator itFicha = fichas.rbegin(); itFicha!=fichas.rend();) {
        
            (*itFicha)->update();
            if(!(*itFicha)->debesMorir){
                for (vector<fichaInfo*>::reverse_iterator itFicha2 = itFicha; itFicha2!=fichas.rend(); ++itFicha2) {
                    if(((*itFicha)!=(*itFicha2)) && (*itFicha)->areaGrande.intersects((*itFicha2)->areaGrande) && (*itFicha2)->areaGrande.leader){
                        (*itFicha2)->areaGrande.addRepulsionForce(&(*itFicha)->areaGrande, 800, 100);
                    }
                }
                ++itFicha;
            }else{
                delete *itFicha;  
                fichas.erase(fichas.begin(),fichas.end()); 
            }
    }
    
}

//--------------------------------------------------------------
void testApp::draw(){
    //plano.draw(0, 0);
    
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

