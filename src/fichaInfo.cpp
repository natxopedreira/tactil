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
    
    kmuelles = 0.115;
	kHorizontal = 0.205;
	kMuellesDiagonales = 0.245;
	
	dampCajasMiniaturas = 0.35;
	dampcajas = 0.55;
	
	dragin = false;
    dragingMini = false;
	px = .0;
	py = .0;
    
    offsetDrag.set(0, 0);
	
	seccionActiva = 1; // cual es la seccion de inicio
    
    abierta = false;
    
    anchoGrande = 60;
    altoGrande = 60;

}
fichaInfo::~fichaInfo(){

	ofRemoveListener(ofEvents().mousePressed, this, &fichaInfo::_mouseDragged);
	ofRemoveListener(ofEvents().mousePressed, this, &fichaInfo::_mousePressed);
	ofRemoveListener(ofEvents().mouseReleased, this, &fichaInfo::_mouseReleased);
	ofRemoveListener(areaGrande.meCambie, this, &fichaInfo::_areaGrandeLista);
	
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
	
    
   
    
    
	
	//inicias la miniatura
    /// le indicamos las anclas al area grande (para enganchar las minis)
    minis.setAncla(&areaGrande);
	
	minis._kMuellesDiagonales = kMuellesDiagonales;
	minis._kHorizontal = kHorizontal;
	minis._kmuelles = kmuelles;
	minis._dampCajasMiniaturas = dampCajasMiniaturas;
	
	//
	ofAddListener(areaGrande.meCambie, this, &fichaInfo::_areaGrandeLista);
    abierta = true;

    
    Tweenzor::add(&anchoGrande, anchoGrande, 488, .6, 1.f, EASE_IN_OUT_CUBIC);
    Tweenzor::add(&altoGrande, altoGrande, 350, .3, 1.f, EASE_IN_OUT_CUBIC);
	Tweenzor::addCompleteListener( Tweenzor::getTween(&anchoGrande), this, &fichaInfo::onCompleteCambio);
}
//--------------------------------------------------------------
void fichaInfo::onCompleteCambio(float* arg){
    cambiaSeccion(2); /// en cuanto se termina la animacion inicial, cambias la seccion
}

//--------------------------------------------------------------
void fichaInfo::update(){
    //=cout << escalaGrande << endl;
    areaGrande.width = anchoGrande;
    areaGrande.height = altoGrande;
    //areaGrande.scaleFromCenter(escalaGrande);

	/// todos se repelen entre si
	for(int i = 0; i < rectangulos.size(); i++){
		int index = i;
		/*
		repulsion para los botones
		 */
		for(int j = 0; j < rectangulos.size(); j++){
			if(i != j) rectangulos.at(j)->addRepulsionForce(rectangulos.at(i),80,100);
		}
        
       // rectangulos.at(i)->bounceOffWalls();
		rectangulos.at(i)->update();
	}
   
    //
    // movemos las miniaturas
    minis.update();
	
	
	for(int i = 0; i < muelles.size(); i++){
		muelles.at(i)->update();
	}
}

//--------------------------------------------------------------
void fichaInfo::draw(){
	
	
	ofSetColor(255, 255, 255,255);
    
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
	/// colisionan las minis con el grande
    for (int i = 0; i < rectangulos.size(); i++){
        for (int j = 0; j < _body->rectangulos.size(); j++ ){

            if(i=!j)rectangulos[i]->addRepulsionForce( (_body)->rectangulos[j] , (_body)->rectangulos[j]->width, 590);
        }
    }
}

// crea la forma
//--------------------------------------------------------------
void fichaInfo::construFigura(){

	areaGrande.x = 800;
	areaGrande.y = 300;
/*
    areaGrande.width = 488;
	areaGrande.height = 350;
 */
    areaGrande.width = 60;
	areaGrande.height = 60;
    
	areaGrande.color.set(10, 10, 10);
	areaGrande.principal = true;
	areaGrande.damping = dampcajas;
   // areaGrande.escala = 0;
    
	
	btnPeriodicos.x = areaGrande.x - 86 ;
	btnPeriodicos.y = areaGrande.y;
	btnPeriodicos.width = 60;
	btnPeriodicos.height = 60;
	btnPeriodicos.color.set(109, 4, 56);
	btnPeriodicos.mass = 0.6;
    btnPeriodicos.nombre = "P";
	btnPeriodicos.useBtn = true;
	btnPeriodicos.damping = dampcajas;
	
	btnImagenes.x = btnPeriodicos.x;
	btnImagenes.y = btnPeriodicos.y -81;
	btnImagenes.width = 60;
	btnImagenes.height = 60;
	btnImagenes.color.set(237, 157, 0);
	btnImagenes.mass = 0.6;
    btnImagenes.nombre = "I";
	btnImagenes.useBtn = true;
	btnImagenes.damping = dampcajas;
	
	btnCuadros.x = btnImagenes.x + 81;
	btnCuadros.y = btnImagenes.y;
	btnCuadros.width = 60;
	btnCuadros.height = 60;
	btnCuadros.color.set(88, 132, 0);
	btnCuadros.mass = 0.6;
    btnCuadros.nombre = "C";
	btnCuadros.useBtn = true;
    btnCuadros.damping = dampcajas;
    
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
	muPeriodico->visible = false;
	//////////////////////////
	muPeriodicoImagenes->k = kmuelles;
	muPeriodicoImagenes->rectA = &btnPeriodicos;
	muPeriodicoImagenes->rectB = &btnImagenes;
	muPeriodicoImagenes->indiceA = 0;
	muPeriodicoImagenes->indiceB = 3;
	muPeriodicoImagenes->dist = 28;
	muPeriodicoImagenes->visible = false;
	//////////////////////////
	muPeriodicoImagenes2->k = kmuelles;
	muPeriodicoImagenes2->rectA = &btnPeriodicos;
	muPeriodicoImagenes2->rectB = &btnImagenes;
	muPeriodicoImagenes2->indiceA = 1;
	muPeriodicoImagenes2->indiceB = 2;
	muPeriodicoImagenes2->dist = 28;
	muPeriodicoImagenes2->visible = false;
	//////////////////////////
	muPeriodicoImagenes3->k = kmuelles;
	muPeriodicoImagenes3->rectA = &btnPeriodicos;
	muPeriodicoImagenes3->rectB = &btnImagenes;
	muPeriodicoImagenes3->indiceA = 1;
	muPeriodicoImagenes3->indiceB = 3;
	muPeriodicoImagenes3->dist = 66;
	muPeriodicoImagenes3->visible = false;
	//////////////////////////
	muPeriodicoImagenes4->k = kmuelles;
	muPeriodicoImagenes4->rectA = &btnPeriodicos;
	muPeriodicoImagenes4->rectB = &areaGrande;
	muPeriodicoImagenes4->indiceA = 2;
	muPeriodicoImagenes4->indiceB = 0;
	muPeriodicoImagenes4->dist = 66;
	muPeriodicoImagenes4->visible = false;
	//////////////////////////
	muImageCuadros->k = kmuelles;
	muImageCuadros->rectA = &btnImagenes;
	muImageCuadros->rectB = &btnCuadros;
	muImageCuadros->indiceA = 1;
	muImageCuadros->indiceB = 0;
	muImageCuadros->dist = 28;
	muImageCuadros->visible = false;
	//////////////////////////
	muImageCuadros2->k = kmuelles;
	muImageCuadros2->rectA = &btnImagenes;
	muImageCuadros2->rectB = &btnCuadros;
	muImageCuadros2->indiceA = 2;
	muImageCuadros2->indiceB = 3;
	muImageCuadros2->dist = 28;
	muImageCuadros2->visible = false;
	//////////////////////////
	muImageCuadros3->k = kmuelles;
	muImageCuadros3->rectA = &btnCuadros;
	muImageCuadros3->rectB = &areaGrande;
	muImageCuadros3->indiceA = 3;
	muImageCuadros3->indiceB = 0;
	muImageCuadros3->dist = 28;
	muImageCuadros3->visible = false;
	//////////////////////////
	muImageCuadros4->k = kmuelles;
	muImageCuadros4->rectA = &btnImagenes;
	muImageCuadros4->rectB = &btnCuadros;
	muImageCuadros4->indiceA = 2;
	muImageCuadros4->indiceB = 0;
	muImageCuadros4->dist = 66;
	muImageCuadros4->visible = false;
	//////////////////////////
	muImageCuadros5->k = kmuelles;
	muImageCuadros5->rectA = &areaGrande;
	muImageCuadros5->rectB = &btnCuadros;
	muImageCuadros5->indiceA = 0;
	muImageCuadros5->indiceB = 2;
	muImageCuadros5->dist = 66;
	muImageCuadros5->visible = false;
	//////////////////////////
	aux->k = kmuelles;
	aux->rectA = &btnPeriodicos;
	aux->rectB = &areaGrande;
	aux->indiceA = 2;
	aux->indiceB = 2;
	aux->dist = 590;
	aux->visible = false;
	//////////////////////////
	aux2->k = kmuelles;
	aux2->rectA = &btnImagenes;
	aux2->rectB = &btnCuadros;
	aux2->indiceA = 1;
	aux2->indiceB = 3;
	aux2->dist = 66;
	aux2->visible = false;
	//////////////////////////
	aux3->k = kmuelles;
	aux3->rectA = &btnImagenes;
	aux3->rectB = &btnPeriodicos;
	aux3->indiceA = 2;
	aux3->indiceB = 0;
	aux3->dist = 66;
	aux3->visible = false;
	//////////////////////////
	aux4->k = kmuelles;
	aux4->rectA = &btnImagenes;
	aux4->rectB = &areaGrande;
	aux4->indiceA = 2;
	aux4->indiceB = 0;
	aux4->dist = 39;
	aux4->visible = false;
    
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
void fichaInfo::cambiaKDiagonal(float  v){
	/// seteamos un nuevo valor k para los muelles daigonales
    for(int i = 0; i < muelles.size(); i++){
        if(muelles.at(i)->diagonal) muelles.at(i)->k = v;
    }

	minis.cambiaKDiagonal(v);
}
//--------------------------------------------------------------
void fichaInfo::cambiaKHorizontal(float v){
	minis.cambiaKHorizontal(v);
}

//--------------------------------------------------------------
void fichaInfo::cambiaK(float  v){
    /// seteamos un nuevo valor k para los muelles
    for(int i = 0; i < muelles.size(); i++){
        muelles.at(i)->k = v;
    }
	minis.cambiaK(v);
}

void fichaInfo::cambiaDampMiniaturas(float  v){
	minis.cambiaDampMiniaturas(v);
}
//--------------------------------------------------------------
void fichaInfo::cambiaDamp(float  v){
    /// seteamos un nuevo valor k para los muelles
    for(int i = 0; i < rectangulos.size(); i++){
        rectangulos.at(i)->damping = v;
    }
}
//
// MODIFICA VALORES DE LA ELASTICIDAD

//--------------------------------------------------------------
void fichaInfo::_mouseDragged(ofMouseEventArgs &e){
	
	if(!dragin && !dragingMini) return;   /// si no estas drageando nada get out of here
    
    if(dragin){
        /// estas drageando un boton o el visualizador
        ofPoint p = rectangulos.at(idLeader)->getCenter();
        ofPoint diff	= ofPoint(e.x, e.y) - p;
        ofPoint destino = ofPoint(e.x, e.y) - diff/2;
        rectangulos.at(idLeader)->moveTo(diff.x+offsetDrag.x,diff.y+offsetDrag.y);
    }
    
    if(dragingMini){
        /// estas drageando una miniatura
        ofPoint p = minis.thumbs[idLeader]->getCenter();
        ofPoint diff	= ofPoint(e.x, e.y) - p;
        ofPoint destino = ofPoint(e.x, e.y) - diff/2;
        minis.thumbs[idLeader]->moveTo(diff.x+offsetDrag.x,diff.y+offsetDrag.y);
    }
}
//--------------------------------------------------------------
void fichaInfo::_mousePressed(ofMouseEventArgs &e){
	for(int i = 0; i < rectangulos.size(); i++){
        /// compruebas si estas drageando una caja
		if(rectangulos.at(i)->inside(ofPoint(e.x, e.y))){
			rectangulos.at(i)->leader = true;
			dragin = true;
            dragingMini = false;
			idLeader = i;
			px = e.x;
			py = e.y;
            
			
            // offset para el drag, la distancia desde el click del mouse al centro
            offsetDrag.set(rectangulos.at(idLeader)->getCenter().x-e.x,rectangulos.at(idLeader)->getCenter().y-e.y);
			
			// mira si es un boton
			if(rectangulos.at(i)->useBtn){
				
				
				cambiaSeccion(i);
			}
			
			return;
		}
	}
    
    /// comprueba si esta presionando una miniatura 
    /// desabilitado el drag en las minis
    
    for(int i = 0; i < minis.thumbs.size(); i++){
        if( minis.thumbs[i]->inside(e.x, e.y)){
            //cargaMinis(i);
            dragin = false;
            dragingMini = true;
            idLeader = i;
			px = e.x;
			py = e.y;
            
            // offset para el drag, la distancia desde el click del mouse al centro
            
            offsetDrag.set(minis.thumbs[idLeader]->getCenter().x-e.x,minis.thumbs[idLeader]->getCenter().y-e.y);
            
            return;
        }
    }
    
}
//--------------------------------------------------------------
void fichaInfo::cargaMinis(int _index){
    
	///cargamos las miniaturas
    minis.setup(8 , areaGrande.x, areaGrande.y + areaGrande.getHeight() + 120, rectangulos.at(seccionActiva)->color);
}

//--------------------------------------------------------------
void fichaInfo::cambiaSeccion(int _cuala){
	seccionActiva = _cuala;
	
	for(int i = 1; i < rectangulos.size(); i++){
		if(rectangulos.at(i)->useBtn){
			/// eres un boton
			
			if(i==seccionActiva){
				rectangulos.at(i)->activo = true;
				areaGrande.cambiate(rectangulos.at(i)->color.r,rectangulos.at(i)->color.g,rectangulos.at(i)->color.b, 0);
				//minis.limpiaMinis();
			}else {
				rectangulos.at(i)->activo = false;
			}

		}
	}

	
}


//--------------------------------------------------------------
void fichaInfo::_mouseReleased(ofMouseEventArgs &e){
	if(dragin){
        // tas arrastrando un boton el visualizador
        idLeader = -1;
        dragin = false;
        offsetDrag.set(0, 0);
        for(int i = 0; i < rectangulos.size(); i++){
            rectangulos.at(i)->leader = false;
        }
    }
    if(dragingMini){
        // tas arrastrando una mini
        idLeader = -1;
        dragingMini = false;
        offsetDrag.set(0, 0);
        for(int i = 0; i < minis.thumbs.size(); i++){
            minis.thumbs[i]->leader = false;
        }
    }

}



//--------------------------------------------------------------
void fichaInfo::_areaGrandeLista(string & s){
	cout << "gorda lista " << endl;
	cargaMinis(seccionActiva);
}