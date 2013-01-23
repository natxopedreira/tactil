/*
 *  fichaInfo.cpp
 *  tactil
 *
 *  Created by ignacio garcia on 08/01/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "fichaInfo.h"
fichaInfo::fichaInfo(){
	// el leader es el que estas drageando
	idLeader = -1;
    dampcajas = 0.15;
    kmuelles = 0.01;
	
	dragin = false;
	px = .0;
	py = .0;
    
    offsetDrag.set(0, 0);
    

}
fichaInfo::~fichaInfo(){

	ofRemoveListener(ofEvents().mousePressed, this, &fichaInfo::_mouseDragged);
	ofRemoveListener(ofEvents().mousePressed, this, &fichaInfo::_mousePressed);
	ofRemoveListener(ofEvents().mouseReleased, this, &fichaInfo::_mouseReleased);
	
	
	for(int i = 0; i < muelles.size(); i++){
		delete muelles[i]; //porque no puedo borrar los muelles !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	}
	muelles.clear();	
	
	for(int i = 0; i < rectangulos.size(); i++){
		delete rectangulos[i];
	}
	rectangulos.clear();

	
    
}
//--------------------------------------------------------------
void fichaInfo::setup(){
	construFigura();
	
	ofAddListener(ofEvents().mouseDragged, this, &fichaInfo::_mouseDragged);
	ofAddListener(ofEvents().mousePressed, this, &fichaInfo::_mousePressed);
	ofAddListener(ofEvents().mouseReleased, this, &fichaInfo::_mouseReleased);
	
    
    ///iniciamos las miniaturas
    //minis.setup(8 , areaGrande.puntos[2].x, areaGrande.puntos[2].y);
    minis.setup(8 , areaGrande.x + areaGrande.width, areaGrande.y + areaGrande.height);
    
    //cout << "medida " << areaGrande.x + areaGrande.width  << " // " << areaGrande.y + areaGrande.height << endl;
    Tweenzor::init();
}

//--------------------------------------------------------------
void fichaInfo::update(){
	Tweenzor::update( ofGetElapsedTimeMillis() );
    
    
	for(int i = 0; i < muelles.size(); i++){
		muelles.at(i)->update();
	}
	/// todos se repelen entre si
	for(int i = 0; i < rectangulos.size(); i++){
		int index = i;
		for(int j = 0; j < rectangulos.size(); j++){
			if(i != j) rectangulos.at(j)->addRepulsionForce(rectangulos.at(i)->getCenter(),70,90);
		}
        
        rectangulos.at(i)->bounceOffWalls();
		rectangulos.at(i)->update();
	}
   
    //
    //movemos las miniaturas
   
    float dx = ( areaGrande.x + areaGrande.width + 100 ) - minis.centro.x;
    float dy = ( areaGrande.y + areaGrande.height + 100 ) - minis.centro.y;
    //
    
    minis.update(dx,dy);
}

//--------------------------------------------------------------
void fichaInfo::draw(){
	
	
	ofSetColor(255, 100, 100);
    
    /// muelles
	for(int j = 0; j < muelles.size(); j++){
		muelles.at(j)->draw();
	}
	
    /// PINTA LOS BOTONES y EL AREA
    btnImagenes.drawButton();
	btnCuadros.drawButton();
	btnPeriodicos.drawButton();
	areaGrande.drawRound();
    
    
    // PINTA EL AREA
    areaGrande.drawVisualizador();
    
    
    minis.drawCircle();
}

//--------------------------------------------------------------
void fichaInfo::collideWith( fichaInfo *_body ){
    for (int i = 0; i < rectangulos.size(); i++){
        for (int j = 0; j < _body->rectangulos.size(); j++ ){

            rectangulos[i]->addRepulsionForce( (_body)->rectangulos[j] , (_body)->rectangulos[j]->width, 590);
        }
    }
}

// crea la forma
//--------------------------------------------------------------
void fichaInfo::construFigura(){

	areaGrande.x = ofRandom(1024);
	areaGrande.y = ofRandom(768);
	areaGrande.width = 488;
	areaGrande.height = 350;
	areaGrande.color.set(221,245,86);
	areaGrande.principal = true;
	
	btnPeriodicos.x = areaGrande.x - 86 ;
	btnPeriodicos.y = areaGrande.y;
	btnPeriodicos.width = 60;
	btnPeriodicos.height = 60;
	btnPeriodicos.color.set(171,209,217);
	btnPeriodicos.mass = 0.6;
    btnPeriodicos.nombre = "periodicos";
	
	btnImagenes.x = btnPeriodicos.x;
	btnImagenes.y = btnPeriodicos.y -81;
	btnImagenes.width = 60;
	btnImagenes.height = 60;
	btnImagenes.color.set(171,209,217);
	btnImagenes.mass = 0.6;
    btnImagenes.nombre = "imagenes";
	
	btnCuadros.x = btnImagenes.x + 81;
	btnCuadros.y = btnImagenes.y;
	btnCuadros.width = 60;
	btnCuadros.height = 60;
	btnCuadros.color.set(171,209,217);
	btnCuadros.mass = 0.6;
    btnCuadros.nombre = "cuadros";
    
    
	rectangulos.push_back(&areaGrande);
	rectangulos.push_back(&btnPeriodicos);
	rectangulos.push_back(&btnImagenes);
	rectangulos.push_back(&btnCuadros);
	
	
	
	// muelles
	// a cada muelle se le puede definir el anclaje
	Spring * muPeriodico = new Spring();
	Spring * muPeriodicoImagenes = new Spring();
	Spring * muPeriodicoImagenes2 = new Spring();
	Spring * muPeriodicoImagenes3 = new Spring();
	Spring * muPeriodicoImagenes4 = new Spring();
	Spring * muImageCuadros = new Spring();
	Spring * muImageCuadros2 = new Spring();
	Spring * muImageCuadros3 = new Spring();
	Spring * muImageCuadros4 = new Spring();
	Spring * muImageCuadros5 = new Spring();
	Spring * aux = new Spring();
	Spring * aux2 = new Spring();
	Spring * aux3 = new Spring();
	Spring * aux4 = new Spring();
    Spring * aux5 = new Spring();
	
	
	//////////////////////////
	muPeriodico->k = kmuelles;
	muPeriodico->rectA = &btnPeriodicos;
	muPeriodico->rectB = &areaGrande;
	muPeriodico->indiceA = 1;
	muPeriodico->indiceB = 0;
	muPeriodico->dist = 28;
	muPeriodico->visible = true;
	//////////////////////////
	muPeriodicoImagenes->k = kmuelles;
	muPeriodicoImagenes->rectA = &btnPeriodicos;
	muPeriodicoImagenes->rectB = &btnImagenes;
	muPeriodicoImagenes->indiceA = 0;
	muPeriodicoImagenes->indiceB = 3;
	muPeriodicoImagenes->dist = 28;
	muPeriodicoImagenes->visible = true;
	//////////////////////////
	muPeriodicoImagenes2->k = kmuelles;
	muPeriodicoImagenes2->rectA = &btnPeriodicos;
	muPeriodicoImagenes2->rectB = &btnImagenes;
	muPeriodicoImagenes2->indiceA = 1;
	muPeriodicoImagenes2->indiceB = 2;
	muPeriodicoImagenes2->dist = 28;
	muPeriodicoImagenes2->visible = true;
	//////////////////////////
	muPeriodicoImagenes3->k = kmuelles;
	muPeriodicoImagenes3->rectA = &btnPeriodicos;
	muPeriodicoImagenes3->rectB = &btnImagenes;
	muPeriodicoImagenes3->indiceA = 1;
	muPeriodicoImagenes3->indiceB = 3;
	muPeriodicoImagenes3->dist = 66;
	muPeriodicoImagenes3->visible = true;
	//////////////////////////
	muPeriodicoImagenes4->k = kmuelles;
	muPeriodicoImagenes4->rectA = &btnPeriodicos;
	muPeriodicoImagenes4->rectB = &areaGrande;
	muPeriodicoImagenes4->indiceA = 2;
	muPeriodicoImagenes4->indiceB = 0;
	muPeriodicoImagenes4->dist = 66;
	muPeriodicoImagenes4->visible = true;
	//////////////////////////
	muImageCuadros->k = kmuelles;
	muImageCuadros->rectA = &btnImagenes;
	muImageCuadros->rectB = &btnCuadros;
	muImageCuadros->indiceA = 1;
	muImageCuadros->indiceB = 0;
	muImageCuadros->dist = 28;
	muImageCuadros->visible = true;
	//////////////////////////
	muImageCuadros2->k = kmuelles;
	muImageCuadros2->rectA = &btnImagenes;
	muImageCuadros2->rectB = &btnCuadros;
	muImageCuadros2->indiceA = 2;
	muImageCuadros2->indiceB = 3;
	muImageCuadros2->dist = 28;
	muImageCuadros2->visible = true;
	//////////////////////////
	muImageCuadros3->k = kmuelles;
	muImageCuadros3->rectA = &btnCuadros;
	muImageCuadros3->rectB = &areaGrande;
	muImageCuadros3->indiceA = 3;
	muImageCuadros3->indiceB = 0;
	muImageCuadros3->dist = 28;
	muImageCuadros3->visible = true;
	//////////////////////////
	muImageCuadros4->k = kmuelles;
	muImageCuadros4->rectA = &btnImagenes;
	muImageCuadros4->rectB = &btnCuadros;
	muImageCuadros4->indiceA = 2;
	muImageCuadros4->indiceB = 0;
	muImageCuadros4->dist = 66;
	muImageCuadros4->visible = true;
	//////////////////////////
	muImageCuadros5->k = kmuelles;
	muImageCuadros5->rectA = &areaGrande;
	muImageCuadros5->rectB = &btnCuadros;
	muImageCuadros5->indiceA = 0;
	muImageCuadros5->indiceB = 2;
	muImageCuadros5->dist = 66;
	muImageCuadros5->visible = true;
	//////////////////////////
	aux->k = kmuelles;
	aux->rectA = &btnPeriodicos;
	aux->rectB = &areaGrande;
	aux->indiceA = 2;
	aux->indiceB = 2;
	aux->dist = 590;
	aux->visible = true;
	//////////////////////////
	aux2->k = kmuelles;
	aux2->rectA = &btnImagenes;
	aux2->rectB = &btnCuadros;
	aux2->indiceA = 1;
	aux2->indiceB = 3;
	aux2->dist = 66;
	aux2->visible = true;
	//////////////////////////
	aux3->k = kmuelles;
	aux3->rectA = &btnImagenes;
	aux3->rectB = &btnPeriodicos;
	aux3->indiceA = 2;
	aux3->indiceB = 0;
	aux3->dist = 66;
	aux3->visible = true;
	//////////////////////////
	aux4->k = kmuelles;
	aux4->rectA = &btnImagenes;
	aux4->rectB = &areaGrande;
	aux4->indiceA = 2;
	aux4->indiceB = 0;
	aux4->dist = 39;
	aux4->visible = true;
    
	//////////////////////////
	muelles.push_back(muPeriodico);
	muelles.push_back(muPeriodicoImagenes);
	muelles.push_back(muPeriodicoImagenes2);
	muelles.push_back(muPeriodicoImagenes3);
	muelles.push_back(muPeriodicoImagenes4);
	muelles.push_back(muImageCuadros);
	muelles.push_back(muImageCuadros2);
	muelles.push_back(muImageCuadros3);
	muelles.push_back(muImageCuadros4);
	muelles.push_back(muImageCuadros5);
	muelles.push_back(aux2);
	muelles.push_back(aux3);
	muelles.push_back(aux4);
    
    
   
}
//
// MODIFICA VALORES DE LA ELASTICIDAD

//--------------------------------------------------------------
void fichaInfo::cambiaK(float & v){
    /// seteamos un nuevo valor k para los muelles
    for(int i = 0; i < muelles.size(); i++){
        muelles.at(i)->k = v;
    }
}

//--------------------------------------------------------------
void fichaInfo::cambiaDamp(float & v){
    /// seteamos un nuevo valor k para los muelles
    for(int i = 0; i < rectangulos.size(); i++){
        rectangulos.at(i)->damping = v;
    }
}
//
// MODIFICA VALORES DE LA ELASTICIDAD

//--------------------------------------------------------------
void fichaInfo::_mouseDragged(ofMouseEventArgs &e){
	
	if(!dragin) return;
	///distancia desde el drag al cuadrado
	ofPoint p = rectangulos.at(idLeader)->getCenter();
	ofPoint diff	= ofPoint(e.x, e.y) - p;
	float length	= diff.length()/(ofGetWidth()/2);
	
	//// los lideres atraen
	ofPoint destino = ofPoint(e.x, e.y) - diff/2;
	//rectangulos.at(idLeader)->addAttractionForce(destino, diff, 500, length*50);
    
	rectangulos.at(idLeader)->moveTo(diff.x+offsetDrag.x,diff.y+offsetDrag.y);
}
//--------------------------------------------------------------
void fichaInfo::_mousePressed(ofMouseEventArgs &e){
	for(int i = 0; i < rectangulos.size(); i++){
        /// compruebas si estas drageando una caja
		if(rectangulos.at(i)->inside(ofPoint(e.x, e.y))){
			rectangulos.at(i)->leader = true;
			dragin = true;
			idLeader = i;
			px = e.x;
			py = e.y;
            
            // offset para el drag, la distancia desde el click del mouse al centro
            
            offsetDrag.set(rectangulos.at(idLeader)->getCenter().x-e.x,rectangulos.at(idLeader)->getCenter().y-e.y);
			return;
		}
	}
    
    /// comprueba si esta presionando una miniatura
    for(int i = 0; i < minis.thumbs.size(); i++){
        if( minis.thumbs[i]->inside(e.x, e.y)){
            cargaMinis(i);
            return;
        }
    }
}
//--------------------------------------------------------------
void fichaInfo::cargaMinis(int _index){
    for(int i = 0; i < minis.thumbs.size(); i++){
        if(i==_index){
            minis.thumbs[i]->activalo();
        }else{
            minis.thumbs[i]->desactivalo();
        }
    }
}

//--------------------------------------------------------------
void fichaInfo::cambiaSeccion(){}


//--------------------------------------------------------------
void fichaInfo::_mouseReleased(ofMouseEventArgs &e){
	if(!dragin) return;
	for(int i = 0; i < rectangulos.size(); i++){
		rectangulos.at(i)->leader = false;
	}
	idLeader = -1;
	dragin = false;
    offsetDrag.set(0, 0);
}