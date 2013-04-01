#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    
	ofBackground(0,0,0);
    
    Tweenzor::init();
    
	dampcajas = 0.3;
	dampcajasMiniaturas = 0.3;
	
    kmuelles = 0.0325;
	kmuellesDiagonales = 0.0325;
	kmuellesHorizontales = 0.0325;

    leyenda.loadImage("leyenda.png");
    ciudad.loadImage("ciudad.jpg");
    ciudadMask.loadImage("ciudad_mask.jpg");
    
    tuioClient.start(3333);
    
    
    // ----- mar de fondo
    animacionFondo.setup();

    
    // ----- shader con la mascara
    mascara.load("composite");
    mascara.begin();
	mascara.setUniformTexture("Tex0", ciudad.getTextureReference(), 0);
	mascara.setUniformTexture("Tex1", ciudadMask.getTextureReference(), 1);
	mascara.end();
    
    
    // ----- hotspots del mapa
    puntosMapa.setup();
    
    
    verGui = false;
    
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
	
    
    
    
    /////////////////////
    /////////////////////
	//fichaInfo * ficha = new fichaInfo();
	//ficha->setup("interactivo.xml");
    //ficha->setTuioClient(&tuioClient);
    
	//fichas.push_back(ficha);

}

//--------------------------------------------------------------
void testApp::update(){
    Tweenzor::update( ofGetElapsedTimeMillis() );
    tuioClient.getMessage();
    
    
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
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(255, 255,255);
    // animacion mar
    animacionFondo.draw();
    
    
    ///////////////////////////////////
    ///////////////////////////////////
    // shader mascara para la ciudad
	mascara.begin();
    
	glActiveTexture(GL_TEXTURE0_ARB);
	ciudad.getTextureReference().bind();
	glActiveTexture(GL_TEXTURE1_ARB);
	ciudadMask.getTextureReference().bind();
    
	//draw a quad the size of the frame
	glBegin(GL_QUADS);
    
	//move the mask around with the mouse by modifying the texture coordinates

        glMultiTexCoord2d(GL_TEXTURE0_ARB, 0, 0);
        glMultiTexCoord2d(GL_TEXTURE1_ARB, 0, 0);		
        glVertex2f( 0, 0);
    
        glMultiTexCoord2d(GL_TEXTURE0_ARB, 1920, 0);
        glMultiTexCoord2d(GL_TEXTURE1_ARB, 1920, 0);		
        glVertex2f( 1920, 0);
    
        glMultiTexCoord2d(GL_TEXTURE0_ARB, 1920, 1080);
        glMultiTexCoord2d(GL_TEXTURE1_ARB, 1920, 1080);
        glVertex2f( 1920, 1080);
    
        glMultiTexCoord2d(GL_TEXTURE0_ARB, 0, 1080);
        glMultiTexCoord2d(GL_TEXTURE1_ARB, 0, 1080);		
        glVertex2f( 0,1080 );
    
	glEnd();
    
	//deactive and clean up
	glActiveTexture(GL_TEXTURE1_ARB);
	ciudadMask.getTextureReference().unbind();
	glActiveTexture(GL_TEXTURE0_ARB);
	ciudad.getTextureReference().unbind();
    
	mascara.end();
    
    
    // ----- leyenda del tactil
    leyenda.draw(805, 426);
    
    // ----- hotspots del mapa
    puntosMapa.draw();
    
    
    
    // velo negro
    if(fichas.size()>0){
        ofPushStyle();
        ofSetColor(0, 0, 0, 180);
        ofRect(0, 0, 1920, 1080);
        ofPopStyle();
    }
    

    
    
    
    
    // ----- fichas
    for (vector<fichaInfo*>::iterator itFichas = fichas.begin(); itFichas!=fichas.end(); ++itFichas) {
        (*itFichas)->draw();
    }

    
    
    
    stringstream str;
    
    str << "[e] ver/ocultar el mensaje" << endl
    << "" << endl
    << "[d] SI mover puntos" <<  endl
    << "[o] NO mover puntos" <<   endl
    << "" << endl
    << "[s] para guardar los puntos" <<  endl
    << "" << endl
    << "[g] para ver/ocultar GUI" <<  endl
    << "" << endl
    << "fps: " <<  ofToString(ofGetFrameRate()) << endl
    << "" << endl;
    
    ofDrawBitmapString(str.str(),10,10);
    
    if(verGui){
        gui.draw();
    }
    
    
    /// cursor tuio
    ofSetColor(30, 255, 255);
    
    tuioClient.drawCursors();
}

//--------------------------------------------------------------
void testApp::lanzaFicha(){
      fichaInfo * ficha = new fichaInfo();
      ficha->setup("interactivo.xml");
      ficha->setTuioClient(&tuioClient);
    
      fichas.push_back(ficha);

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
    switch (key) {
        case 'f':
            lanzaFicha();
            break;
            
        case 's':
            puntosMapa.savePositions(); 
            break; 
            
        case 'd':
            puntosMapa.debugOn(); 
            break; 
            
        case 'o':
            puntosMapa.debugOff(); 
            break;
            
        case 'g':
            verGui = !verGui; 
            break; 
    }
    

}

