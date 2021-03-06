#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    //ofSetDataPathRoot("../Resources/data/");
    
	//ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
	ofBackground(0,0,0);
    
    Tweenzor::init();
    
    
    ultimoLanzamiento.set(0,0);
    
#ifdef USE_TUIO
    tuioClient.start(3333);
#endif
    
    
    //----- parches para los videos
    
    ///capilla de san andres
    parcheVideo p19;
    p19.ID = 19;
    p19.urlCastellano = "videos/castrense_cast.mov";
    p19.urlGallego = "videos/castrense_gal.mov";
    p19.urlIngles = "videos/castrense_eng.mov";
    p19.urlFrances = "videos/castrense_fr.mov";
    
    ///instituto eusebio da guarda
    parcheVideo p2;
    p2.ID = 2;
    p2.urlCastellano = "videos/eusebio_da_guarda_cast.mov";
    p2.urlGallego = "videos/eusebio_da_guarda_gal.mov";
    p2.urlIngles = "videos/eusebio_da_guarda_eng.mov";
    p2.urlFrances = "videos/eusebio_da_guarda_fr.mov";
    
    ///cementerio de san amaro
    parcheVideo p13;
    p13.ID = 13;
    p13.urlCastellano = "videos/san_amaro_cast.mov";
    p13.urlGallego = "videos/san_amaro_gal.mov";
    p13.urlIngles = "videos/san_amaro_eng.mov";
    p13.urlFrances = "videos/san_amaro_fr.mov";    
    
    
    parches.push_back(p19);
    parches.push_back(p2);
    parches.push_back(p13);
    
    
    
    
    
	dampcajas = 0.3;
	dampcajasMiniaturas = 0.3;
	
    kmuelles = 0.0325;
	kmuellesDiagonales = 0.0325;
	kmuellesHorizontales = 0.0325;

    leyenda.loadImage("leyenda2.png");
    ciudad.loadImage("ciudad2.jpg");
    ciudadMask.loadImage("mascara_ciudad.jpg");
    
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
    gui.add(puntosDebug.setup("editar puntos", false));
    gui.add(guardarPosicionesPuntos.setup("guardar puntos", false));
    gui.add(fps.setup("fps", ""));
	gui.loadFromFile("settings.xml");
	
    kMuelles.addListener(this, &testApp::btnCambiaK);
	kMuellesHorizontales.addListener(this, &testApp::btnCambiaKHorizontal);
	kMuellesDiagonales.addListener(this, &testApp::btnCambiaKDiagonal);
    dampCajasMiniaturas.addListener(this, &testApp::btnCambiaDampMiniaturas);
	dampCajas.addListener(this, &testApp::btnCambiaDamp);
	
    puntosDebug.addListener(this,&testApp::editarPuntos);
    guardarPosicionesPuntos.addListener(this,&testApp::guardarPuntos);
    
    
    ofAddListener(puntosMapa.verFicha,this, &testApp::verFicha);
}

//--------------------------------------------------------------
void testApp::update(){
    Tweenzor::update( ofGetElapsedTimeMillis() );
    
#ifdef USE_TUIO
    tuioClient.getMessage();
#endif
    
    

    
    
    fps = ofToString(ofGetFrameRate());
    
    for (int i = fichas.size()-1; i >= 0 ; i--){
        fichas[i]->update();
        if (!fichas[i]->debesMorir ){
            for (int j = i; j >= 0; j--){
                if (j != i)
                    if((fichas[i]->rectanguloArea.intersects(fichas[j]->rectanguloArea)) && (fichas[j]->areaGrande.leader)){
                        //fichas[j]->areaGrande.addRepulsionForce( &fichas[i]->areaGrande, 100, 100);
                        //return;
                    }
                   /* if ((fichas[i]->areaGrande.intersects( fichas[j]->areaGrande )) && (fichas[j]->areaGrande.leader)){
                        fichas[j]->areaGrande.addRepulsionForce( &fichas[i]->areaGrande, 800, 100);
                    }*/
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
    leyenda.draw(975, 320);
    
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
        //cout << (*itFichas)->areaGrande.x << endl;
    }


    if(verGui){
        gui.draw();
    }
    
    
    /// cursor tuio
    
    
#ifdef USE_TUIO
    //ofSetColor(30, 255, 255);
    tuioClient.drawCursors();
#endif
    
    
    ///////////////looop test
   /* for (int i = fichas.size()-1; i >= 0 ; i--){
        ofPushStyle();
        ofSetColor(255, 0, 0);
        ofCircle(fichas[i]->ptoInicio.x, fichas[i]->ptoInicio.y, 6);
        ofSetColor(255, 100, 0);
        ofCircle(fichas[i]->areaGrande.pos.x, fichas[i]->areaGrande.pos.y, 3);
        ofPopStyle();
    }
    */
    
    
}


//--------------------------------------------------------------
void testApp::verFicha(customDataEvent & info){
    //if(fichas.size()>0) return;
    
    
    bool usado = false;
    
    for (int i = 0; i<fichas.size(); i++) {
        usado = fichas.at(i)->isInside(info.pto);
    }
    
    if(usado)  return;
    
    
    
    
    
    
    fichaInfo * ficha = new fichaInfo();
    //buscamos un sitio
    bool encontrado = false;
    
    ultimoLanzamiento.set(ofRandom(200,1400),ofRandom(200,600));
    
    if(fichas.size()>0){
        for (int i = 0; i<fichas.size(); i++) {
            if(ultimoLanzamiento.distance(ofVec2f(fichas.at(i)->px,fichas.at(i)->py))>800){
                encontrado = true;
                ///cout << ultimoLanzamiento.distance(ofVec2f(fichas.at(i)->px,fichas.at(i)->py)) << endl;
            }
        }
        if(!encontrado) verFicha(info);
    }
    
    
    ///--- compruebas su id para ver si tiene un video
    for (int i = 0; i<parches.size(); i++) {
        if(parches.at(i).ID == info.valor){
            ///// hay un video
            ficha->hayVideo = true;
            ficha->linksVideos.cast = parches.at(i).urlCastellano;
            ficha->linksVideos.gal = parches.at(i).urlGallego;
            ficha->linksVideos.eng = parches.at(i).urlIngles;
            ficha->linksVideos.fr = parches.at(i).urlFrances;
        }
    }
    
    
    ficha->setup(info.nombre, info.valor, ultimoLanzamiento);
    
    
    
#ifdef USE_TUIO
    ficha->setTuioClient(&tuioClient);
#endif
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
void testApp::guardarPuntos(bool & r){
    if (r) {
        puntosMapa.savePositions();
        guardarPosicionesPuntos.value = false;
    }
}

//--------------------------------------------------------------
void testApp::editarPuntos(bool & r){
    if(r){
        puntosMapa.debugOn();
    }else {
        puntosMapa.debugOff();
    }
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
           // lanzaFicha();
            break;
            
        case 'g':
            verGui = !verGui; 
            break; 
    }
}

