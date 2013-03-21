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

	idLeader = 0;
    
    kmuelles = 0.30;
	kHorizontal = 0.305;
	kMuellesDiagonales = 0.325;
	
	dampCajasMiniaturas = 0.35;
	dampcajas = 0.55;
	
	px = .0;
	py = .0;
    
	seccionActiva = 0; // cual es la seccion de inicio
    
    abierta = false;
    
    anchoGrande = 60;
    altoGrande = 60;
    
    visualizadorWidth = 497;
    visualizadorheight = 400;

    totalFichas = 0;
    totalImagenes = 0;
    totalCuadros = 0;
    totalperiodicos = 0;
    
    verIdiomas = false;
    debesMorir = false;
}

fichaInfo::~fichaInfo(){
    
	ofRemoveListener(ofEvents().mousePressed, this, &fichaInfo::_mouseDragged);
	ofRemoveListener(ofEvents().mousePressed, this, &fichaInfo::_mousePressed);
	ofRemoveListener(ofEvents().mouseReleased, this, &fichaInfo::_mouseReleased);
	ofRemoveListener(areaGrande.meCambie, this, &fichaInfo::_areaGrandeLista);
    
	for(int i = 0; i < muelles.size(); i++){
        if ( muelles[i] != NULL){
            delete muelles[i];
            muelles[i] = NULL;
        }
	}
	muelles.clear();	
	rectangulos.clear();
     
}


//--------------------------------------------------------------
void fichaInfo::setup(string _ulrXml){
    
    fuenteBotones.loadFont("SegoeRg.ttf", 9 ,90, true);
    fuenteBotones.setLineHeight(18);
    
	construFigura();
    /////
    areaGrande.setup();
    
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


    Tweenzor::add(&anchoGrande, anchoGrande, visualizadorWidth, .3, 1.f, EASE_IN_OUT_CUBIC);
    Tweenzor::add(&altoGrande, altoGrande, visualizadorheight, .1, 1.f, EASE_IN_OUT_CUBIC);
	Tweenzor::addCompleteListener( Tweenzor::getTween(&anchoGrande), this, &fichaInfo::onCompleteCambio);
    
    
    //cargamos datos
    cargaXml(_ulrXml);
}

//--------------------------------------------------------------
void fichaInfo::update(){

    areaGrande.width = anchoGrande;
    areaGrande.height = altoGrande;
    
    
    // update rectangulos
    for (vector<baseShape*>::iterator itRect = rectangulos.begin(); itRect!=rectangulos.end(); ++itRect) {
        
        for (vector<baseShape*>::iterator itRectR = itRect; itRectR!=rectangulos.end(); ++itRectR) {
            
            if((*itRect) != (*itRectR) && !(*itRect)->useBtnIdioma && !(*itRectR)->useBtnIdioma && !(*itRectR)->principal){
                (*itRectR)->addRepulsionForce((*itRect), 80, 80);
            }
        }
        
        (*itRect)->update();
    }

    // update muelles
    for (vector<Spring*>::iterator itMuelle = muelles.begin(); itMuelle!=muelles.end(); ++itMuelle) {
        (*itMuelle)->update();
    }

    
    // movemos las miniaturas
    
	areaGrande.update();
    minis.update();
    
    
    /// algo de elasticidad para los botones de los idiomas
    float dFrx = (areaGrande.x + areaGrande.width - frances.width)-(frances.x);
    float dEngx = (frances.x - ingles.width + 4)-(ingles.x);
    float dCastx = (gallego.x - castellano.width + 4)-(castellano.x);
    float dGalx = (ingles.x - gallego.width + 4)-(gallego.x);
    float dClosex = (areaGrande.x)-(cerrar.x);
    
    float dFry = (areaGrande.y - 15)-(frances.y);
    float dCasty = (areaGrande.y - 15)-(castellano.y);
    float dGly = (areaGrande.y - 15)-(gallego.y);
    float Engy = (areaGrande.y - 15)-(ingles.y);
    
    float dClosey = (areaGrande.y + areaGrande.height+10)-(cerrar.y);

    
    frances.x += dFrx * .5;
    ingles.x += dEngx * .6;
    castellano.x += dCastx * .7;
    gallego.x += dGalx * .75;
    cerrar.x += dClosex * .75;
    
    
    frances.y += dFry * .4;
    ingles.y += Engy * .5;
    gallego.y += dGly * .6;
    castellano.y += dCasty * .5;
    cerrar.y += dClosey * .5;
    
}

//--------------------------------------------------------------
void fichaInfo::draw(){
    
    //ofPushStyle();
    
	ofSetColor(255, 255, 255,255);
    
    /// muelles
	/*for(int j = 0; j < muelles.size(); j++){
		muelles.at(j)->draw();
	}*/
	
    /// PINTA LOS BOTONES y EL AREA
    btnImagenes.drawButton();
	btnCuadros.drawButton();
	btnPeriodicos.drawButton();
	areaGrande.drawRound();
    

    // PINTA EL AREA
    areaGrande.drawVisualizador();
    minis.drawCircle();
    
    
    /// botones de idioma
    if(verIdiomas){
       if(!frances.botonIdiomaCheck) frances.drawContxt(fuenteBotones);
       if(!ingles.botonIdiomaCheck)  ingles.drawContxt(fuenteBotones);
       if(!gallego.botonIdiomaCheck)  gallego.drawContxt(fuenteBotones);
       if(!castellano.botonIdiomaCheck)  castellano.drawContxt(fuenteBotones);
        
        
        if(frances.botonIdiomaCheck) frances.drawContxt(fuenteBotones);
        if(ingles.botonIdiomaCheck)  ingles.drawContxt(fuenteBotones);
        if(gallego.botonIdiomaCheck)  gallego.drawContxt(fuenteBotones);
        if(castellano.botonIdiomaCheck)  castellano.drawContxt(fuenteBotones);
        cerrar.drawContxt(fuenteBotones);
    }
    

}
//--------------------------------------------------------------
void fichaInfo::drawSombra(){
    
    //ofPushStyle();
    
	ofSetColor(255, 255, 255,255);
    
    /// muelles
	/*for(int j = 0; j < muelles.size(); j++){
		muelles.at(j)->draw();
	}*/
	
    /// PINTA LOS BOTONES y EL AREA
    btnImagenes.drawButton();
	btnCuadros.drawButton();
	btnPeriodicos.drawButton();
	areaGrande.drawRound();
    
    
    // PINTA EL AREA
    areaGrande.drawVisualizador();
    minis.drawCircle();
}
//  callback animacion del inicio
//--------------------------------------------------------------
void fichaInfo::onCompleteCambio(float* arg){
   // cout << "onCompleteCambio" << endl;
    cambiaSeccion(2); /// en cuanto se termina la animacion inicial, cambias la seccion
}


//  collision entre el visualizador y las minis
//--------------------------------------------------------------
void fichaInfo::collideWith( fichaInfo *_body ){

    for (int i = 0; i < rectangulos.size(); i++){
        for (int j = 0; j < _body->rectangulos.size(); j++ ){

            if((i =! j)){rectangulos[i]->addRepulsionForce( (_body)->rectangulos[j] , (_body)->rectangulos[j]->width, 590);
            }
        }
    }
}


// asigna el contenido al visualizador
//--------------------------------------------------------------
void fichaInfo::cargaImagenes(){
    /// cada vez que click una mini
    /// cargas el contenido en el area de visualizacion
    
    
    switch (minis.lenguaje) {
        case IDIOMA_CAST:
            if(idLeader < minis.titular_cast_mini.size() && idLeader < minis.pies_cast_cuerpo_mini.size() && idLeader < minis.txt_cast_mini.size()){
                areaGrande.ponTexto(minis.titular_cast_mini.at(idLeader), minis.pies_cast_cuerpo_mini.at(idLeader), minis.txt_cast_mini.at(idLeader));   
            }
            break;
            
        case IDIOMA_GAL:
            if(idLeader < minis.titular_gal_mini.size() && idLeader < minis.pies_gal_cuerpo_mini.size() && idLeader < minis.txt_gal_mini.size()){
                areaGrande.ponTexto(minis.titular_gal_mini.at(idLeader), minis.pies_gal_cuerpo_mini.at(idLeader), minis.txt_gal_mini.at(idLeader));
            }
            break;
            
        case IDIOMA_ENG:
            if(idLeader < minis.titular_eng_mini.size() && idLeader < minis.pies_eng_cuerpo_mini.size() && idLeader < minis.txt_eng_mini.size()){
                areaGrande.ponTexto(minis.titular_eng_mini.at(idLeader), minis.pies_eng_cuerpo_mini.at(idLeader), minis.txt_eng_mini.at(idLeader));
            }
            break;
            
        case IDIOMA_FR:
            if(idLeader < minis.titular_fr_mini.size() && idLeader < minis.pies_fr_cuerpo_mini.size() && idLeader < minis.txt_fr_mini.size()){
                areaGrande.ponTexto(minis.titular_fr_mini.at(idLeader), minis.pies_fr_cuerpo_mini.at(idLeader), minis.txt_fr_mini.at(idLeader));
            }
            break;
            
        default:
            break;
    }
    if(idLeader < minis.urls_mini.size()) areaGrande.cargaImagen(minis.urls_mini.at(idLeader));
}


//--------------------------------------------------------------
void fichaInfo::cambiaSeccion(int _cuala){
	seccionActiva = _cuala;
	
	for(int i = 1; i < rectangulos.size(); i++){
		if(rectangulos.at(i)->useBtn){
			/// eres un boton
			
			if(i==seccionActiva){
				rectangulos.at(i)->activo = true;
                areaGrande.desfaseAltoTextoInfo = 0;
                areaGrande.altoTexto = 0;
                
				areaGrande.cambiate(rectangulos.at(i)->color.r,rectangulos.at(i)->color.g,rectangulos.at(i)->color.b, 0);
                areaGrande.verPie = false;
			}else {
				rectangulos.at(i)->activo = false;
			}
		}
	}
}



//--------------------------------------------------------------
void fichaInfo::_areaGrandeLista(string & s){
	cargaMinis(seccionActiva);
    verIdiomas = true;
}



// crea los thumbs de las secciones
//--------------------------------------------------------------
void fichaInfo::cargaMinis(int _index){
    
	///cargamos las miniaturas
    
    int px = areaGrande.x;
    int py = areaGrande.posyrect + areaGrande.poshrect + 180;
    
    minis.limpiaMinis(); // borras las que hay
    
    for (int i = 0; i<rectangulos.at(seccionActiva)->urls.size(); i++) {
        
        minis.urls_mini.push_back(rectangulos.at(seccionActiva)->urls.at(i));
        
        minis.txt_cast_mini.push_back(rectangulos.at(seccionActiva)->txt_cast.at(i));
        minis.txt_eng_mini.push_back(rectangulos.at(seccionActiva)->txt_eng.at(i));
        minis.txt_fr_mini.push_back(rectangulos.at(seccionActiva)->txt_fr.at(i));
        minis.txt_gal_mini.push_back(rectangulos.at(seccionActiva)->txt_gal.at(i));
        
        minis.pies_cast_titular_mini.push_back(rectangulos.at(seccionActiva)->pies_cast_titular.at(i));
        minis.pies_cast_cuerpo_mini.push_back(rectangulos.at(seccionActiva)->pies_cast_cuerpo.at(i));
        
        minis.pies_gal_titular_mini.push_back(rectangulos.at(seccionActiva)->pies_gal_titular.at(i));
        minis.pies_gal_cuerpo_mini.push_back(rectangulos.at(seccionActiva)->pies_gal_cuerpo.at(i));
        
        minis.pies_eng_titular_mini.push_back(rectangulos.at(seccionActiva)->pies_eng_titular.at(i));
        minis.pies_eng_cuerpo_mini.push_back(rectangulos.at(seccionActiva)->pies_eng_cuerpo.at(i));
        
        minis.pies_fr_titular_mini.push_back(rectangulos.at(seccionActiva)->pies_fr_titular.at(i));
        minis.pies_fr_cuerpo_mini.push_back(rectangulos.at(seccionActiva)->pies_fr_cuerpo.at(i));
        
        minis.titular_cast_mini.push_back(rectangulos.at(seccionActiva)->titular_cast.at(i));
        minis.titular_gal_mini.push_back(rectangulos.at(seccionActiva)->titular_gal.at(i));
        minis.titular_eng_mini.push_back(rectangulos.at(seccionActiva)->titular_eng.at(i));
        minis.titular_fr_mini.push_back(rectangulos.at(seccionActiva)->titular_fr.at(i));
    }
    
    //cout << minis.pies_gal_titular_mini.size() << endl;
    minis.setup(px, py, rectangulos.at(seccionActiva)->color);
}


// crea la forma
//--------------------------------------------------------------
void fichaInfo::construFigura(){
    
	areaGrande.x = 800;
	areaGrande.y = 300;
    
    areaGrande.width = 60;
	areaGrande.height = 60;
    
	areaGrande.color.set(10, 10, 10);
	areaGrande.principal = true;
	areaGrande.damping = dampcajas;
	
	btnPeriodicos.x = areaGrande.x - 86 ;
	btnPeriodicos.y = areaGrande.y;
	btnPeriodicos.width = 60;
	btnPeriodicos.height = 60;
	btnPeriodicos.color.set(233, 186, 118);
	btnPeriodicos.mass = 0.6;
    btnPeriodicos.nombre = "P";
	btnPeriodicos.useBtn = true;
	btnPeriodicos.damping = dampcajas;
	
	btnImagenes.x = btnPeriodicos.x;
	btnImagenes.y = btnPeriodicos.y -81;
	btnImagenes.width = 60;
	btnImagenes.height = 60;
	btnImagenes.color.set(154, 189, 195);
	btnImagenes.mass = 0.6;
    btnImagenes.nombre = "I";
	btnImagenes.useBtn = true;
	btnImagenes.damping = dampcajas;
	
	btnCuadros.x = btnImagenes.x + 81;
	btnCuadros.y = btnImagenes.y;
	btnCuadros.width = 60;
	btnCuadros.height = 60;
	btnCuadros.color.set(236, 232, 220);
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
	//muPeriodico->visible = true;
	//////////////////////////
	muPeriodicoImagenes->k = kmuelles;
	muPeriodicoImagenes->rectA = &btnPeriodicos;
	muPeriodicoImagenes->rectB = &btnImagenes;
	muPeriodicoImagenes->indiceA = 0;
	muPeriodicoImagenes->indiceB = 11;
	muPeriodicoImagenes->dist = 28;
	//muPeriodicoImagenes->visible = true;
	//////////////////////////
	muPeriodicoImagenes2->k = kmuelles;
	muPeriodicoImagenes2->rectA = &btnPeriodicos;
	muPeriodicoImagenes2->rectB = &btnImagenes;
	muPeriodicoImagenes2->indiceA = 1;
	muPeriodicoImagenes2->indiceB = 10;
	muPeriodicoImagenes2->dist = 28;
	//muPeriodicoImagenes2->visible = true;
	//////////////////////////
	muPeriodicoImagenes3->k = kmuelles;
	muPeriodicoImagenes3->rectA = &btnPeriodicos;
	muPeriodicoImagenes3->rectB = &btnImagenes;
	muPeriodicoImagenes3->indiceA = 1;
	muPeriodicoImagenes3->indiceB = 11;
	muPeriodicoImagenes3->dist = 66;
	//muPeriodicoImagenes3->visible = true;
	//////////////////////////
	muPeriodicoImagenes4->k = kmuelles;
	muPeriodicoImagenes4->rectA = &btnPeriodicos;
	muPeriodicoImagenes4->rectB = &areaGrande;
	muPeriodicoImagenes4->indiceA = 10;
	muPeriodicoImagenes4->indiceB = 0;
	muPeriodicoImagenes4->dist = 66;
	//muPeriodicoImagenes4->visible = true;
	//////////////////////////
	muImageCuadros->k = kmuelles;
	muImageCuadros->rectA = &btnImagenes;
	muImageCuadros->rectB = &btnCuadros;
	muImageCuadros->indiceA = 1;
	muImageCuadros->indiceB = 0;
	muImageCuadros->dist = 28;
	//muImageCuadros->visible = true;
	//////////////////////////
	muImageCuadros2->k = kmuelles;
	muImageCuadros2->rectA = &btnImagenes;
	muImageCuadros2->rectB = &btnCuadros;
	muImageCuadros2->indiceA = 10;
	muImageCuadros2->indiceB = 11;
	muImageCuadros2->dist = 28;
	//muImageCuadros2->visible = true;
	//////////////////////////
	muImageCuadros3->k = kmuelles;
	muImageCuadros3->rectA = &btnCuadros;
	muImageCuadros3->rectB = &areaGrande;
	muImageCuadros3->indiceA = 11;
	muImageCuadros3->indiceB = 0;
	muImageCuadros3->dist = 28;
	//muImageCuadros3->visible = true;
	//////////////////////////
	muImageCuadros4->k = kmuelles;
	muImageCuadros4->rectA = &btnImagenes;
	muImageCuadros4->rectB = &btnCuadros;
	muImageCuadros4->indiceA = 10;
	muImageCuadros4->indiceB = 0;
	muImageCuadros4->dist = 66;
	//muImageCuadros4->visible = true;
	//////////////////////////
	muImageCuadros5->k = kmuelles;
	muImageCuadros5->rectA = &areaGrande;
	muImageCuadros5->rectB = &btnCuadros;
	muImageCuadros5->indiceA = 0;
	muImageCuadros5->indiceB = 10;
	muImageCuadros5->dist = 66;
	//muImageCuadros5->visible = false;
	//////////////////////////
	aux->k = kmuelles;
	aux->rectA = &btnPeriodicos;
	aux->rectB = &areaGrande;
	aux->indiceA = 10;
	aux->indiceB = 10;
	aux->dist = 590;
	//aux->visible = false;
	//////////////////////////
	aux2->k = kmuelles;
	aux2->rectA = &btnImagenes;
	aux2->rectB = &btnCuadros;
	aux2->indiceA = 1;
	aux2->indiceB = 11;
	aux2->dist = 66;
	//aux2->visible = false;
	//////////////////////////
	aux3->k = kmuelles;
	aux3->rectA = &btnImagenes;
	aux3->rectB = &btnPeriodicos;
	aux3->indiceA = 10;
	aux3->indiceB = 0;
	aux3->dist = 66;
	//aux3->visible = false;
	//////////////////////////
	aux4->k = kmuelles;
	aux4->rectA = &btnImagenes;
	aux4->rectB = &areaGrande;
	aux4->indiceA = 10;
	aux4->indiceB = 0;
	aux4->dist = 39;
	//aux4->visible = false;
    
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
    
    
    
    ///botones de idioma
    castellano.width = 38;
    castellano.height = 22;
    castellano.x = 0;
    castellano.y = 0;
    castellano.nombre = "ESP";
    castellano.botonIdiomaCheck = true;
    castellano.useBtnIdioma = true;
    
    gallego.width = 38;
    gallego.height = 22;
    gallego.x = castellano.x + castellano.width;
    gallego.y = 0;
    gallego.nombre = "GAL";
    gallego.useBtnIdioma = true;
    
    ingles.width = 38;
    ingles.height = 22;
    ingles.x = gallego.x + gallego.width;
    ingles.y = 0;
    ingles.nombre = "ENG"; 
    ingles.useBtnIdioma = true;
    
    frances.width = 38;
    frances.height = 22;
    frances.x = ingles.x + ingles.width;
    frances.y = 0;
    frances.nombre = "FR"; 
    frances.useBtnIdioma = true;
    
    ///boton cerrar ficha
    cerrar.width = 20;
    cerrar.height = 22;
    cerrar.x = 10;
    cerrar.y = 10;
    cerrar.nombre = "X";
    cerrar.useBtnIdioma = true;
    cerrar.botonClose = true;
    
    rectangulos.push_back(&castellano);
    rectangulos.push_back(&gallego);
    rectangulos.push_back(&ingles);
    rectangulos.push_back(&frances);
    rectangulos.push_back(&cerrar);
    
    frances.idiomaColor.set(255,255,255,255);
    ingles.idiomaColor.set(255,255,255,255);
    gallego.idiomaColor.set(255,255,255,255);
    castellano.idiomaColor.set(255,255,255,255);
    
    frances.idiomaActivoColor.set(255, 143, 95,255);
    ingles.idiomaActivoColor.set(255, 143, 95,255);
    gallego.idiomaActivoColor.set(255, 143, 95,255);
    castellano.idiomaActivoColor.set(255, 143, 95,255);
    
    
}


// datos del xml
//--------------------------------------------------------------
void fichaInfo::cargaXml(string _ulr){
    
    
    int idBuscado = 0;
    
    if(datosXml.loadFile(_ulr)){
        //has cargado el xml
        //buscas el id de la ficha que quieras
        
        datosXml.pushTag("mesa");
        totalFichas = datosXml.getNumTags("ficha");
        
        for (int i = 0; i< totalFichas; i++) {
            
            if (datosXml.pushTag("ficha", i)){
                if(datosXml.getValue("id", -1) == idBuscado){
                    /// has encontrado la ficha que buscas
                    
                    
                    datosXml.pushTag("images");
                    // le pasamos las imagenes al boton correspondiente que es el num 2 del vector
                    //
                    
                    totalImagenes = datosXml.getNumTags("image");
                    for (int j=0; j<totalImagenes; j++) {
                        datosXml.pushTag("image", j);
                        rectangulos.at(2)->urls.push_back(datosXml.getValue("url", ""));
                        
                        rectangulos.at(2)->txt_cast.push_back(datosXml.getValue("txt_cast", ""));
                        rectangulos.at(2)->txt_eng.push_back(datosXml.getValue("txt_eng", ""));
                        rectangulos.at(2)->txt_fr.push_back(datosXml.getValue("txt_fr", ""));
                        rectangulos.at(2)->txt_gal.push_back(datosXml.getValue("txt_gal", ""));
                        
                        rectangulos.at(2)->titular_cast.push_back(datosXml.getValue("titulo_cast", ""));
                        rectangulos.at(2)->titular_gal.push_back(datosXml.getValue("titulo_gal", ""));
                        rectangulos.at(2)->titular_eng.push_back(datosXml.getValue("titulo_eng", ""));
                        rectangulos.at(2)->titular_fr.push_back(datosXml.getValue("titulo_fr", ""));
                        
                        // comprobamos los pies
                        
                        // castellano
                        if(datosXml.pushTag("pie_cast")){
                            rectangulos.at(2)->pies_cast_titular.push_back(datosXml.getValue("titular", ""));
                            rectangulos.at(2)->pies_cast_cuerpo.push_back(datosXml.getValue("cuerpo", ""));
                            datosXml.popTag();
                        }    
                        // gallego
                        if(datosXml.pushTag("pie_gal")){
                            rectangulos.at(2)->pies_gal_titular.push_back(datosXml.getValue("titular", ""));
                            rectangulos.at(2)->pies_gal_cuerpo.push_back(datosXml.getValue("cuerpo", ""));
                            
                            datosXml.popTag();
                        }
                        // ingles
                        if(datosXml.pushTag("pie_eng")){
                            rectangulos.at(2)->pies_eng_titular.push_back(datosXml.getValue("titular", ""));
                            rectangulos.at(2)->pies_eng_cuerpo.push_back(datosXml.getValue("cuerpo", ""));
                            
                            datosXml.popTag();   
                        }
                        // frances
                        if(datosXml.pushTag("pie_fr")){
                            rectangulos.at(2)->pies_fr_titular.push_back(datosXml.getValue("titular", ""));
                            rectangulos.at(2)->pies_fr_cuerpo.push_back(datosXml.getValue("cuerpo", ""));
                            
                            datosXml.popTag();  
                        }
                        
                        datosXml.popTag();
                    }
                    
                    
                    
                    datosXml.popTag();
                    datosXml.pushTag("cuadros");
                    // le pasamos los cuadros al boton correspondiente que es el num 3 del vector
                    totalCuadros = datosXml.getNumTags("cuadro");
                    for (int k=0; k<totalCuadros; k++) {
                        datosXml.pushTag("cuadro", k);
                        rectangulos.at(3)->urls.push_back(datosXml.getValue("url", ""));
                        
                        rectangulos.at(3)->txt_cast.push_back(datosXml.getValue("txt_cast", ""));
                        rectangulos.at(3)->txt_eng.push_back(datosXml.getValue("txt_eng", ""));
                        rectangulos.at(3)->txt_fr.push_back(datosXml.getValue("txt_fr", ""));
                        rectangulos.at(3)->txt_gal.push_back(datosXml.getValue("txt_gal", ""));
                        
                        rectangulos.at(3)->titular_cast.push_back(datosXml.getValue("titulo_cast", ""));
                        rectangulos.at(3)->titular_gal.push_back(datosXml.getValue("titulo_gal", ""));
                        rectangulos.at(3)->titular_eng.push_back(datosXml.getValue("titulo_eng", ""));
                        rectangulos.at(3)->titular_fr.push_back(datosXml.getValue("titulo_fr", ""));
                        
                        
                        
                        
                        
                        // comprobamos los pies
                        
                        // castellano
                        if(datosXml.pushTag("pie_cast")){
                            rectangulos.at(3)->pies_cast_titular.push_back(datosXml.getValue("titular", ""));
                            rectangulos.at(3)->pies_cast_cuerpo.push_back(datosXml.getValue("cuerpo", ""));                            
                            datosXml.popTag();
                        }    
                        // gallego
                        if(datosXml.pushTag("pie_gal")){
                            rectangulos.at(3)->pies_gal_titular.push_back(datosXml.getValue("titular", ""));
                            rectangulos.at(3)->pies_gal_cuerpo.push_back(datosXml.getValue("cuerpo", ""));
                            datosXml.popTag();
                        }
                        // ingles
                        if(datosXml.pushTag("pie_eng")){
                            rectangulos.at(3)->pies_eng_titular.push_back(datosXml.getValue("titular", ""));
                            rectangulos.at(3)->pies_eng_cuerpo.push_back(datosXml.getValue("cuerpo", ""));
                            datosXml.popTag();   
                        }
                        // frances
                        if(datosXml.pushTag("pie_fr")){
                            rectangulos.at(3)->pies_fr_titular.push_back(datosXml.getValue("titular", ""));
                            rectangulos.at(3)->pies_fr_cuerpo.push_back(datosXml.getValue("cuerpo", ""));
                            datosXml.popTag();  
                        }
                        
                        
                        
                        
                        datosXml.popTag();
                    }
                    
                    
                    
                    
                    datosXml.popTag();
                    datosXml.pushTag("periodicos");
                    // le pasamos los periodicos al boton correspondiente que es el num 1 del vector
                    totalperiodicos = datosXml.getNumTags("periodico");
                    for (int l=0; l<totalperiodicos; l++) {
                        datosXml.pushTag("periodico", l);
                        rectangulos.at(1)->urls.push_back(datosXml.getValue("url", ""));
                        rectangulos.at(1)->txt_cast.push_back(datosXml.getValue("txt_cast", ""));
                        rectangulos.at(1)->txt_gal.push_back(datosXml.getValue("txt_gal", ""));
                        rectangulos.at(1)->txt_eng.push_back(datosXml.getValue("txt_eng", ""));
                        rectangulos.at(1)->txt_fr.push_back(datosXml.getValue("txt_fr", ""));
                        
                        rectangulos.at(1)->titular_cast.push_back(datosXml.getValue("titulo_cast", ""));
                        rectangulos.at(1)->titular_gal.push_back(datosXml.getValue("titulo_gal", ""));
                        rectangulos.at(1)->titular_eng.push_back(datosXml.getValue("titulo_eng", ""));
                        rectangulos.at(1)->titular_fr.push_back(datosXml.getValue("titulo_fr", ""));
                        
                        
                        // comprobamos los pies
                        
                        // castellano
                        if(datosXml.pushTag("pie_cast")){
                            rectangulos.at(1)->pies_cast_titular.push_back(datosXml.getValue("titular", ""));
                            rectangulos.at(1)->pies_cast_cuerpo.push_back(datosXml.getValue("cuerpo", ""));
                            datosXml.popTag();
                        }    
                        // gallego
                        if(datosXml.pushTag("pie_gal")){
                            rectangulos.at(1)->pies_gal_titular.push_back(datosXml.getValue("titular", ""));
                            rectangulos.at(1)->pies_gal_cuerpo.push_back(datosXml.getValue("cuerpo", ""));
                            datosXml.popTag();
                        }
                        // ingles
                        if(datosXml.pushTag("pie_eng")){
                            rectangulos.at(1)->pies_eng_titular.push_back(datosXml.getValue("titular", ""));
                            rectangulos.at(1)->pies_eng_cuerpo.push_back(datosXml.getValue("cuerpo", ""));
                            datosXml.popTag();   
                        }
                        // frances
                        if(datosXml.pushTag("pie_fr")){
                            rectangulos.at(1)->pies_fr_titular.push_back(datosXml.getValue("titular", ""));
                            rectangulos.at(1)->pies_fr_cuerpo.push_back(datosXml.getValue("cuerpo", ""));
                            datosXml.popTag();  
                        }
                        
                        
                        
                        
                        datosXml.popTag();
                    }
                    
                }
            }
        }
        
        // has cargado el xml y ahora miramos a ver que botones no van
        // a tener contenido para apagarlos
        if(totalCuadros==0)  btnCuadros.desactivate();
        if(totalImagenes==0)  btnImagenes.desactivate();
        if(totalperiodicos==0)  btnPeriodicos.desactivate();
    }
}


///-----------------
///----------------- EVENTOS MOUSE 
///-----------------

//--------------------------------------------------------------
void fichaInfo::_mouseDragged(ofMouseEventArgs &e){}
//--------------------------------------------------------------
void fichaInfo::_mousePressed(ofMouseEventArgs &e){
    
	for(int i = 0; i < rectangulos.size(); i++){
        /// compruebas si estas drageando una caja
		if(rectangulos.at(i)->inside(ofPoint(e.x, e.y))){
			rectangulos.at(i)->leader = true;
			
			
			px = e.x;
			py = e.y;
            
			// mira si es un boton
			if(rectangulos.at(i)->useBtn && !rectangulos.at(i)->desactivado && !rectangulos.at(i)->useBtnIdioma){
				//idLeader = i;
                seccionActiva = i;
                areaGrande.crece(0);
                
                cambiaSeccion(i);
                
                
                return;
			}
		}
	}
    
    /// comprueba si esta presionando una miniatura 
    /// desabilitado el drag en las minis
    
    for(int i = 0; i < minis.thumbs.size(); i++){
        if( minis.thumbs[i]->inside(e.x, e.y)){
            
            
            idLeader = i;
			px = e.x;
			py = e.y;
            
            minis.thumbs[i]->activala();
            
            cargaImagenes();
            
            for(int j = 0; j <  minis.thumbs.size(); j++){
                if(i!=j) minis.thumbs[j]->desactivala();
            }
        }
    }
    
    ///////////////////////////////////////////
    ///////////////////////////////////////////
    /// compruebas si quieres otro idioma /////
    ///////////////////////////////////////////
    for(int i = 0; i < rectangulos.size(); i++){
        ///  && rectangulos.at(i)->useBtnIdioma
        //if(rectangulos.at(i)->useBtnIdioma) cout << rectangulos.at(i)->y << " -- " << rectangulos.at(i)->x << endl;
        
        if(rectangulos.at(i)->inside(ofPoint(e.x, e.y))){
            
            if(rectangulos.at(i)->useBtnIdioma){
                string n = rectangulos.at(i)->nombre;
                
                if(n == "ESP"){
                    castellano.botonIdiomaCheck = true;
                    minis.lenguaje = IDIOMA_CAST;
                    cargaImagenes();
                    
                }else{
                    castellano.botonIdiomaCheck = false;
                }
                
                if(n == "GAL") {
                    gallego.botonIdiomaCheck = true;
                    minis.lenguaje = IDIOMA_GAL;
                    cargaImagenes();
                }else{
                    gallego.botonIdiomaCheck = false;
                }
                
                
                if (n == "FR") {
                    frances.botonIdiomaCheck = true;
                    minis.lenguaje = IDIOMA_FR;
                    cargaImagenes();
                }else{
                    frances.botonIdiomaCheck = false;
                }
                
                if (n == "ENG") {
                    ingles.botonIdiomaCheck = true;
                    minis.lenguaje = IDIOMA_ENG;
                    cargaImagenes();
                }else{
                    ingles.botonIdiomaCheck = false;
                }
                if(n== "X"){
                    debesMorir = true;
                }
                
            }
        } 
    }
    
}
//--------------------------------------------------------------
void fichaInfo::_mouseReleased(ofMouseEventArgs &e){
    
}


///-----------------
///----------------- VALORES GUI 
///-----------------

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
