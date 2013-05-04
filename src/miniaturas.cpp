//
//  miniaturas.cpp
//  tactil
//
//  Created by natxo pedreira on 14/01/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "miniaturas.h"

miniaturas::miniaturas(){
    origen.set(0, 0);
	anclaVisualizador = NULL;
	
	_kMuellesDiagonales = .0;
	_kHorizontal = .0;
	_kmuelles = .0;
	_dampCajasMiniaturas = .175;
	k = .325;
    
	_listas = false;
    
    
    lenguaje = IDIOMA_CAST;
    
    zoomVisible = false;
}

// ---------------------------------------
miniaturas::~miniaturas(){
    
    for (int i = 0; i < thumbs.size(); i++) {
        delete thumbs[i];
    }
	
	for (int i = 0; i < thumbsSalida.size(); i++) {
        delete thumbsSalida[i];
    }
	
	//delete anclaVisualizador;
	
    thumbs.clear();
	thumbsSalida.clear();
	springs.clear();
    
	urls_mini.clear();
	txt_cast_mini.clear();
	txt_eng_mini.clear();
	txt_fr_mini.clear();
    
    pies_cast_titular_mini.clear();
    pies_cast_cuerpo_mini.clear();
    
    pies_gal_titular_mini.clear();
    pies_gal_cuerpo_mini.clear();
    
    pies_eng_titular_mini.clear();
    pies_eng_cuerpo_mini.clear();
    
    pies_fr_titular_mini.clear();
    pies_fr_cuerpo_mini.clear();
    
    titular_cast_mini.clear();
    titular_eng_mini.clear();
    titular_fr_mini.clear();
    titular_gal_mini.clear();
}

// ---------------------------------------
void miniaturas::setup(float _px, float _py, ofColor _color){
	_listas = false;
    maskShader.load("composite");
	//limpiaMinis();
    /// fill the miniatures vector
    for(int i = 0; i < urls_mini.size(); i++){
        thumb * b = new thumb();
        b->set(0,0, 49, 49);
        b->color.set(0,209,217);
        b->nombre = "M"+ofToString(i);
        b->img.loadImage("imagenes/thumbs/" + urls_mini.at(i));
        b->ponListeners();
        b->ponShader(&maskShader);
		thumbs.push_back(b);
    }
   
    origen.set(_px, _py);
	/// create el grid
    /// si hay minis
    if(thumbs.size()>0) creaGrid(_color);
}

// ---------------------------------------
void miniaturas::update(){
	/// todos se repelen entre si
    
    /*
     p9     p4     p8
     |             |
     p3 -p5-p6-p7- p2
     */
    
    
    // thumbs de salida
    for (int i = thumbsSalida.size()-1; i >= 0 ; i--){
        thumbsSalida[i]->update();
        
        if (!thumbsSalida[i]->suicidate() ){
            ofPoint ptoCaete;
			ptoCaete.x += ofRandom(-2,2);
			ptoCaete.y += ofRandom(4,6);
            
            thumbsSalida[i]->addForce(ptoCaete);
        } else {
            delete thumbsSalida[i];
            thumbsSalida.erase(thumbsSalida.begin()+i);
        }
    }
    
    
    
    // thumbs de lo que estas viendo
	for (vector<thumb*>::iterator itThumb = thumbs.begin(); itThumb!=thumbs.end();++itThumb) {
        (*itThumb)->urdate();
        
        for (vector<thumb*>::iterator itThumb2 = itThumb; itThumb2!=thumbs.end(); ++itThumb2) {
            (*itThumb)->addRepulsionForce((*itThumb2),50,80);
        }

        ofRectangle r;
        r.set(anclaVisualizador->x, anclaVisualizador->y, anclaVisualizador->width, (anclaVisualizador->height));
        
        if(r.intersects(*(*itThumb))){
            (*itThumb)->addForce(ofPoint(0,25));
        }
        
       
    }
    
    
    // muelles
    for (vector<Spring*>::iterator itSpring = springs.begin(); itSpring!=springs.end(); ++itSpring) {
        (*itSpring)->update();
    }
    
}

// ---------------------------------------
void miniaturas::drawCircle(){
    ofPushMatrix();
	
	for(int i = 0; i < springs.size(); i++){
		springs[i]->draw();
	}
    
    for (int i = 0; i < thumbs.size(); i++) {
        thumbs[i]->drawThumb();
    }
	
	for(int i = 0; i < thumbsSalida.size(); i++){
		thumbsSalida[i]->drawThumb();
	}
    
    ofPopMatrix(); 
}

// ---------------------------------------
void miniaturas::setAncla(visualizador * a){
    anclaVisualizador = a;
}

// ---------------------------------------
void miniaturas::limpiaMinis(){
	/// antes miramos si ya hay minis
	
	springs.clear();
    
	for (int i = 0; i < thumbs.size(); i++) {
		thumbsSalida.push_back(thumbs[i]);
    }
    
	thumbs.clear();
    
    urls_mini.clear();
    txt_cast_mini.clear();
    txt_eng_mini.clear();
    txt_fr_mini.clear();
    txt_gal_mini.clear();
    
    titular_cast_mini.clear();
    titular_eng_mini.clear();
    titular_fr_mini.clear();
    titular_gal_mini.clear();
    
    pies_cast_titular_mini.clear();
    pies_cast_cuerpo_mini.clear();
    
    pies_gal_titular_mini.clear();
    pies_gal_cuerpo_mini.clear();
    
    pies_eng_titular_mini.clear();
    pies_eng_cuerpo_mini.clear();
    
    pies_fr_titular_mini.clear();
    pies_fr_cuerpo_mini.clear();
}

// ---------------------------------------
void miniaturas::creaGrid(ofColor _color){

    /////// arreglo de Patricio
    /////// thanks !!!!!
    int cuantas = thumbs.size();
    int numColumnas = 8;
    //  Crear una tabla de punteros donde re organizar los elementos
    //
    vector< vector<thumb*> > tabla;
    for (int i = 0; i < numColumnas; i++ ){
        vector<thumb*> newColum;
        tabla.push_back(newColum);
    }
    int anchoMini = 49;
    int altoMini = 49;
    //  Posicionar los elementos y popular los punteros en la tabla
    //
    int col = 0;
    int row = 0;
    for (int i = 0; i < cuantas; i++) {
        col = i % numColumnas;
        row = i / numColumnas;
        
        //  Ponerlo en la tabla
        //
        tabla[col].push_back( thumbs[i] );
        
        //  Ubicarlo en el espacio
        //
		thumbs[i]->x  = origen.x -( (anchoMini + 10) * col); // las colocamos de izda a derecha
		thumbs[i]->y  = origen.y + ( (altoMini + 10) * row);
		// los movemos al origen, deberias de hacerlo en el de antes
		
		thumbs[i]->color.set(_color.r, _color.g, _color.b);
		thumbs[i]->cambiate(_color.r, _color.g, _color.b, 0.1*i);

    }
    //  Ahora que esta en la tabla podemos recorrerlo de forma más sencilla
    //
    for (int x = 0; x < numColumnas; x++) {
        
        //  Spring Verticales
        //
        for( int y = 0; y < tabla[x].size(); y++){
            
            // A [ x,y ] ---- [ x+1,y ]  B
            //                  /
            //      |       /
            //      |   /
            //
            // C [ x,y+1 ]    [ x+1, y+1 ] D      
            
            bool hayB = false;
            bool hayC = false;
            bool hayD = false;
            
            //  Si A tiene un C
            //
            if ( y != tabla[x].size()-1 ){
                
				//vertical
                hayC = true;
                Spring * sp = new Spring();
                sp->k = k;
                sp->rectA = tabla[x][y]; //A
                sp->rectB = tabla[x][y+1]; //C
                sp->indiceA = 4;
                sp->indiceB = 4;
                sp->dist = ofDist(tabla[x][y]->getCenter().x, tabla[x][y]->getCenter().y,
                                  tabla[x][y+1]->getCenter().x, tabla[x][y+1]->getCenter().y);
                //sp->visible = true;
                springs.push_back(sp);
            }
            
            //  Si no es la ultima columna...
            //
            if ( x < numColumnas-1 ){
                
                // ... y tiene un elemento a la misma altura en Y
                //
                if ( y < tabla[x+1].size() ){
                    
					//horisontal
                    hayB = true;
                    Spring * sp = new Spring();
                    sp->k = k;
                    sp->rectA = tabla[x][y]; //A
                    sp->rectB = tabla[x+1][y]; //B
                    sp->indiceA = 4;
                    sp->indiceB = 4;
                    sp->dist = ofDist(tabla[x][y]->getCenter().x, tabla[x][y]->getCenter().y,
                                      tabla[x+1][y]->getCenter().x, tabla[x+1][y]->getCenter().y);
                    
                    //sp->visible = true;
					sp->horizontal = true;
                    springs.push_back(sp);
                    
                    if ( y+1 < tabla[x+1].size() ){
                        hayD = true;
                    }
                }
            }
            
            //  Si tiene B y C puede agregar la diagonal que le da estabilidad
            //
            if ( hayB && hayC ){
                //DIAGONAL
                Spring * sp = new Spring();
                sp->k = k;
                sp->rectA = tabla[x][y+1];  // C
                sp->rectB = tabla[x+1][y];  // B
                sp->indiceA = 4;
                sp->indiceB = 4;
                sp->dist = ofDist(tabla[x][y+1]->getCenter().x, tabla[x][y+1]->getCenter().y,
                                  tabla[x+1][y]->getCenter().x, tabla[x+1][y]->getCenter().y);
                //sp->visible = true;
                sp->diagonal = true;
                springs.push_back(sp);
                
            }
            
            if ( hayD ){
				//DIAGONAL
                Spring * sp = new Spring();
                sp->k = k;
                sp->rectA = tabla[x][y]; //A
                sp->rectB = tabla[x+1][y+1];  // D
                sp->indiceA = 4;
                sp->indiceB = 4;
                sp->dist = ofDist(tabla[x][y]->getCenter().x, tabla[x][y]->getCenter().y,
                                  tabla[x+1][y+1]->getCenter().x, tabla[x+1][y+1]->getCenter().y);
               //sp->visible = true;
                sp->diagonal = true;
                springs.push_back(sp);
            }
        }
    }
    
    //anclamos las miniaturas al visualizador
	/*
	 p0 ---------- p1
     |             |
	 |     p4      |
	 |             |
	 p3 -p5-p6-p7- p2
	 */
    //reverse de los muelles para
    
    Spring * anclaP3 = new Spring();
	anclaP3->k = k;
	anclaP3->rectA = thumbs[0];  // D
	anclaP3->rectB = anclaVisualizador;
	anclaP3->indiceA = 4;
	anclaP3->indiceB = 15;
	anclaP3->visible = false;
	anclaP3->dist = 80;
    springs.push_back(anclaP3);
    
    
    
    
    if(thumbs.size()>1){
        /// si hay mas de una sigue
        
        //if(thumbs.size()>1){
        
        
        Spring * anclaP5 = new Spring();
        anclaP5->k = k;
        anclaP5->rectA = thumbs[1];  // D
        anclaP5->rectB = anclaVisualizador;
        anclaP5->indiceA = 4;
        anclaP5->indiceB = 14;
        anclaP5->visible = false;
        anclaP5->dist = 80;
        springs.push_back(anclaP5);
        
        Spring * diago0 = new Spring();
        diago0->k = k;
        diago0->rectA = anclaVisualizador;
        diago0->rectB = thumbs[1];  // D
        diago0->indiceA = 15;
        diago0->indiceB = 4;
        diago0->visible = false;
        diago0->diagonal = true;
        diago0->dist = 100;
        springs.push_back(diago0);
        
        Spring * diago3 = new Spring();
        diago3->k = k;
        diago3->rectA = anclaVisualizador;
        diago3->rectB = thumbs[1];  // D
        diago3->indiceA = 13;
        diago3->indiceB = 4;
        diago3->visible = false;
        diago3->diagonal = true;
        diago3->dist = 100;
        springs.push_back(diago3);
        //}
        
        if(thumbs.size()>2){
            Spring * anclaP6 = new Spring();
            anclaP6->k = k;
            anclaP6->rectA = thumbs[2];  // D
            anclaP6->rectB = anclaVisualizador;
            anclaP6->indiceA = 4;
            anclaP6->indiceB = 13;
            anclaP6->visible = false;
            anclaP6->dist = 80;
            springs.push_back(anclaP6);
            
            Spring * diago2 = new Spring();
            diago2->k = k;
            diago2->rectA = anclaVisualizador;
            diago2->rectB = thumbs[2];  // D
            diago2->indiceA = 14;
            diago2->indiceB = 4;
            diago2->visible = false;
            diago2->diagonal = true;
            diago2->dist = 100;
            springs.push_back(diago2);
            
            Spring * diago5 = new Spring();
            diago5->k = k;
            diago5->rectA = anclaVisualizador;
            diago5->rectB = thumbs[2];  // D
            diago5->indiceA = 12;
            diago5->indiceB = 4;
            diago5->visible = false;
            diago5->diagonal = true;
            diago5->dist = 100;
            springs.push_back(diago5);
        }
        
        if(thumbs.size()>3){
            Spring * anclaP7 = new Spring();
            anclaP7->k = k;
            anclaP7->rectA = thumbs[3];  // D
            anclaP7->rectB = anclaVisualizador;
            anclaP7->indiceA = 4;
            anclaP7->indiceB = 12;
            anclaP7->visible = false;
            anclaP7->dist = 80;
            springs.push_back(anclaP7);
            
            Spring * diago4 = new Spring();
            diago4->k = k;
            diago4->rectA = anclaVisualizador;
            diago4->rectB = thumbs[3];  // D
            diago4->indiceA = 13;
            diago4->indiceB = 4;
            diago4->visible = false;
            diago4->diagonal = true;
            diago4->dist = 100;
            springs.push_back(diago4);
            
            Spring * diago7 = new Spring();
            diago7->k = k;
            diago7->rectA = anclaVisualizador;
            diago7->rectB = thumbs[3];  // D
            diago7->indiceA = 2;
            diago7->indiceB = 4;
            diago7->diagonal = true;
            diago7->visible = false;
            diago7->dist = 100;
            springs.push_back(diago7);
        }
        
        
        
        if(thumbs.size()>4){
            Spring * diago6 = new Spring();
            diago6->k = k;
            diago6->rectA = anclaVisualizador;
            diago6->rectB = thumbs[4];  // D
            diago6->indiceA = 12;
            diago6->indiceB = 4;
            diago6->visible = false;
            diago6->diagonal = true;
            diago6->dist = 100;
            
            springs.push_back(diago6);
            //}
            
            //if(thumbs.size()>4){
            Spring * anclaP2 = new Spring();
            anclaP2->k = k;
            anclaP2->rectA = thumbs[4];  // D
            anclaP2->rectB = anclaVisualizador;
            anclaP2->indiceA = 4;
            anclaP2->indiceB = 2;
            anclaP2->visible = false;
            anclaP2->dist = 80;	
            
            springs.push_back(anclaP2);
        }
        
        if(thumbs.size()>5){
            Spring * diago6 = new Spring();
            diago6->k = k;
            diago6->rectA = anclaVisualizador;
            diago6->rectB = thumbs[5];  // D
            diago6->indiceA = 2;
            diago6->indiceB = 4;
            diago6->visible = false;
            diago6->diagonal = true;
            diago6->dist = 100;
            
            springs.push_back(diago6);
            //}
            
            //if(thumbs.size()>4){
            Spring * anclaP2 = new Spring();
            anclaP2->k = k;
            anclaP2->rectA = thumbs[5];  // D
            anclaP2->rectB = anclaVisualizador;
            anclaP2->indiceA = 4;
            anclaP2->indiceB = 7;
            anclaP2->visible = false;
            anclaP2->dist = 80;	
            
            springs.push_back(anclaP2);
        }
        
        if(thumbs.size()>6){
            Spring * diago6 = new Spring();
            diago6->k = k;
            diago6->rectA = anclaVisualizador;
            diago6->rectB = thumbs[6];  // D
            diago6->indiceA = 7;
            diago6->indiceB = 4;
            diago6->visible = false;
            diago6->diagonal = true;
            diago6->dist = 100;
            
            springs.push_back(diago6);
            //}
            
            //if(thumbs.size()>4){
            Spring * anclaP2 = new Spring();
            anclaP2->k = k;
            anclaP2->rectA = thumbs[6];  // D
            anclaP2->rectB = anclaVisualizador;
            anclaP2->indiceA = 4;
            anclaP2->indiceB = 6;
            anclaP2->visible = false;
            anclaP2->dist = 80;	
            
            springs.push_back(anclaP2);
        }
    }
	
	Spring * diago1 = new Spring();
	diago1->k = k;
	diago1->rectA = anclaVisualizador;
	diago1->rectB = thumbs[0];  // D
	diago1->indiceA = 14;
	diago1->indiceB = 4;
	diago1->visible = false;
	diago1->diagonal = true;
	diago1->dist = 100;
	springs.push_back(diago1);
    
/*
	
	Spring * anclaP3 = new Spring();
	anclaP3->k = k;
	anclaP3->rectA = thumbs[0];  // D
	anclaP3->rectB = anclaVisualizador;
	anclaP3->indiceA = 4;
	anclaP3->indiceB = 3;
	anclaP3->visible = false;
	anclaP3->dist = 80;
    springs.push_back(anclaP3);
    
    
    
    
    if(thumbs.size()>1){
    /// si hay mas de una sigue
        
        //if(thumbs.size()>1){
           
        
            Spring * anclaP5 = new Spring();
            anclaP5->k = k;
            anclaP5->rectA = thumbs[1];  // D
            anclaP5->rectB = anclaVisualizador;
            anclaP5->indiceA = 4;
            anclaP5->indiceB = 5;
            anclaP5->visible = false;
            anclaP5->dist = 80;
            springs.push_back(anclaP5);
        
            Spring * diago0 = new Spring();
            diago0->k = k;
            diago0->rectA = anclaVisualizador;
            diago0->rectB = thumbs[1];  // D
            diago0->indiceA = 3;
            diago0->indiceB = 4;
            diago0->visible = false;
            diago0->diagonal = true;
            diago0->dist = 100;
            springs.push_back(diago0);
        
            Spring * diago3 = new Spring();
            diago3->k = k;
            diago3->rectA = anclaVisualizador;
            diago3->rectB = thumbs[1];  // D
            diago3->indiceA = 6;
            diago3->indiceB = 4;
            diago3->visible = false;
            diago3->diagonal = true;
            diago3->dist = 100;
            springs.push_back(diago3);
        //}
        
        if(thumbs.size()>2){
            Spring * anclaP6 = new Spring();
            anclaP6->k = k;
            anclaP6->rectA = thumbs[2];  // D
            anclaP6->rectB = anclaVisualizador;
            anclaP6->indiceA = 4;
            anclaP6->indiceB = 6;
            anclaP6->visible = false;
            anclaP6->dist = 80;
            springs.push_back(anclaP6);
        
            Spring * diago2 = new Spring();
            diago2->k = k;
            diago2->rectA = anclaVisualizador;
            diago2->rectB = thumbs[2];  // D
            diago2->indiceA = 5;
            diago2->indiceB = 4;
            diago2->visible = false;
            diago2->diagonal = true;
            diago2->dist = 100;
            springs.push_back(diago2);
        
            Spring * diago5 = new Spring();
            diago5->k = k;
            diago5->rectA = anclaVisualizador;
            diago5->rectB = thumbs[2];  // D
            diago5->indiceA = 7;
            diago5->indiceB = 4;
            diago5->visible = false;
            diago5->diagonal = true;
            diago5->dist = 100;
            springs.push_back(diago5);
        }
        
        if(thumbs.size()>3){
            Spring * anclaP7 = new Spring();
            anclaP7->k = k;
            anclaP7->rectA = thumbs[3];  // D
            anclaP7->rectB = anclaVisualizador;
            anclaP7->indiceA = 4;
            anclaP7->indiceB = 7;
            anclaP7->visible = false;
            anclaP7->dist = 80;
            springs.push_back(anclaP7);
        
            Spring * diago4 = new Spring();
            diago4->k = k;
            diago4->rectA = anclaVisualizador;
            diago4->rectB = thumbs[3];  // D
            diago4->indiceA = 6;
            diago4->indiceB = 4;
            diago4->visible = false;
            diago4->diagonal = true;
            diago4->dist = 100;
            springs.push_back(diago4);
        
            Spring * diago7 = new Spring();
            diago7->k = k;
            diago7->rectA = anclaVisualizador;
            diago7->rectB = thumbs[3];  // D
            diago7->indiceA = 2;
            diago7->indiceB = 4;
            diago7->diagonal = true;
            diago7->visible = false;
            diago7->dist = 100;
            springs.push_back(diago7);
        }
    
        
        
        if(thumbs.size()>4){
            Spring * diago6 = new Spring();
            diago6->k = k;
            diago6->rectA = anclaVisualizador;
            diago6->rectB = thumbs[4];  // D
            diago6->indiceA = 7;
            diago6->indiceB = 4;
            diago6->visible = false;
            diago6->diagonal = true;
            diago6->dist = 100;
            
            springs.push_back(diago6);
        //}
        
        //if(thumbs.size()>4){
            Spring * anclaP2 = new Spring();
            anclaP2->k = k;
            anclaP2->rectA = thumbs[4];  // D
            anclaP2->rectB = anclaVisualizador;
            anclaP2->indiceA = 4;
            anclaP2->indiceB = 2;
            anclaP2->visible = false;
            anclaP2->dist = 80;	
            
            springs.push_back(anclaP2);
        }

        
    }
	
	Spring * diago1 = new Spring();
	diago1->k = k;
	diago1->rectA = anclaVisualizador;
	diago1->rectB = thumbs[0];  // D
	diago1->indiceA = 5;
	diago1->indiceB = 4;
	diago1->visible = false;
	diago1->diagonal = true;
	diago1->dist = 100;
	springs.push_back(diago1);
    */
	///
	/// PONGO LA TENSION UNA VEZ COLOCADOS LOS MUELLES
    
	cambiaKDiagonal(_kMuellesDiagonales);
	cambiaKHorizontal(_kHorizontal);
	cambiaK(_kmuelles);
	cambiaDampMiniaturas(_dampCajasMiniaturas);
    
    /// marcas la primera como activa
    thumbs[0]->activala();
    
    // cargas la url de la primera thumb en el visualizador
    switch (lenguaje) {
        case IDIOMA_CAST:
            anclaVisualizador->ponTexto(titular_cast_mini[0], pies_cast_cuerpo_mini[0], txt_cast_mini[0]);    
            //anclaVisualizador->ponTexto(pies_cast_titular_mini[0], pies_cast_cuerpo_mini[0], txt_cast_mini[0]);
            break;
            
        case IDIOMA_GAL:
            anclaVisualizador->ponTexto(titular_gal_mini[0], pies_gal_cuerpo_mini[0], txt_gal_mini[0]);    
            //anclaVisualizador->ponTexto(pies_gal_titular_mini[0], pies_gal_cuerpo_mini[0], txt_gal_mini[0]);
            break;
            
        case IDIOMA_ENG:
            anclaVisualizador->ponTexto(titular_eng_mini[0], pies_eng_cuerpo_mini[0], txt_eng_mini[0]);
            //anclaVisualizador->ponTexto(pies_eng_titular_mini[0], pies_eng_cuerpo_mini[0], txt_eng_mini[0]);
            break;
            
        case IDIOMA_FR:
            anclaVisualizador->ponTexto(titular_fr_mini[0], pies_fr_cuerpo_mini[0], txt_fr_mini[0]);
            //anclaVisualizador->ponTexto(pies_fr_titular_mini[0], pies_fr_cuerpo_mini[0], txt_fr_mini[0]);
            break;
            
        default:
            break;
    }
    anclaVisualizador->cargaImagen(urls_mini.at(0));
    
    
}
void miniaturas::viendoZoom(bool _visible){
    zoomVisible = _visible;
}
///-----------------
///----------------- VALORES GUI 
///-----------------

void miniaturas::cambiaK(float v){
    /// seteamos un nuevo valor k para los muelles
    for(int i = 0; i < springs.size(); i++){
        if(!springs.at(i)->diagonal)springs.at(i)->k = v;
    }
}
void miniaturas::cambiaKDiagonal(float v){
    /// seteamos un nuevo valor k para los muelles diagonales
    for(int i = 0; i < springs.size(); i++){
        if(springs.at(i)->diagonal)springs.at(i)->k = v;
    }
}
void miniaturas::cambiaKHorizontal(float v){
    /// seteamos un nuevo valor k para los muelles horizontales
    for(int i = 0; i < springs.size(); i++){
        if(springs.at(i)->horizontal)springs.at(i)->k = v;
    }
}
void miniaturas::cambiaDampMiniaturas(float v){
    /// seteamos un nuevo valor k para los muelles
    for(int i = 0; i < thumbs.size(); i++){
        thumbs.at(i)->damping = v;
    }
}
