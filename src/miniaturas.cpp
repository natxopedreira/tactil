//
//  miniaturas.cpp
//  tactil
//
//  Created by natxo pedreira on 14/01/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "miniaturas.h"

miniaturas::miniaturas(){
    circleResolution = 0;
    origen.set(0, 0);
	anclaVisualizador = NULL;

}

miniaturas::~miniaturas(){
    for (int i = 0; i < thumbs.size(); i++) {
        delete thumbs[i];
    }
    
	delete anclaVisualizador;
	
    thumbs.clear();
    circlePoints.clear();
}

void miniaturas::setup(int cuantas, float _px, float _py){
    
    /// fill the miniatures vector
    for(int i = 0; i < cuantas; i++){
        thumb * b = new thumb();
        b->set(0,0, 45, 45);
        b->color.set(171,209,217);
        b->nombre = "M"+ofToString(i);
        thumbs.push_back(b);
    }
   
   origen.set(_px, _py);
}
void miniaturas::setAncla(visualizador * a){
    anclaVisualizador = a;
    
    /// create el grid
    creaGrid();
}


void miniaturas::creaGrid(){

    /////// arreglo de Patricio
    /////// thanks !!!!!
    
    
    int cuantas = thumbs.size();
    int numColumnas = 5;
    
    //  Crear una tabla de punteros donde re organizar los elementos
    //
    vector< vector<thumb*> > tabla;
    for (int i = 0; i < numColumnas; i++ ){
        vector<thumb*> newColum;
        tabla.push_back(newColum);
    }
    int anchoMini = 70;
    int altoMini = 70;
	
	
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
		thumbs[i]->x  = (anchoMini + 53) * col;
		thumbs[i]->y  = (altoMini + 61) * row;
		// los movemos al origen, deberias de hacerlo en el de antes
		thumbs[i]->x  += origen.x;
		thumbs[i]->y  += origen.y;
		
		thumbs[i]->color.set(10, 10, 10);

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
                sp->visible = true;
                springs.push_back(sp);
            }
            
            //  Si no es la última columna...
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
                    sp->visible = true;
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
	
	Spring * anclaP2 = new Spring();
	anclaP2->k = k;
	anclaP2->rectA = thumbs[4];  // D
	anclaP2->rectB = anclaVisualizador;
	anclaP2->indiceA = 4;
	anclaP2->indiceB = 2;
	anclaP2->visible = true;
	anclaP2->dist = 150;	
	
	Spring * anclaP3 = new Spring();
	anclaP3->k = k;
	anclaP3->rectA = thumbs[0];  // D
	anclaP3->rectB = anclaVisualizador;
	anclaP3->indiceA = 4;
	anclaP3->indiceB = 3;
	anclaP3->visible = true;
	anclaP3->dist = 150;
	
	Spring * anclaP5 = new Spring();
	anclaP5->k = k;
	anclaP5->rectA = thumbs[1];  // D
	anclaP5->rectB = anclaVisualizador;
	anclaP5->indiceA = 4;
	anclaP5->indiceB = 5;
	anclaP5->visible = true;
	anclaP5->dist = 150;

	Spring * anclaP6 = new Spring();
	anclaP6->k = k;
	anclaP6->rectA = thumbs[2];  // D
	anclaP6->rectB = anclaVisualizador;
	anclaP6->indiceA = 4;
	anclaP6->indiceB = 6;
	anclaP6->visible = true;
	anclaP6->dist = 150;
	
	Spring * anclaP7 = new Spring();
	anclaP7->k = k;
	anclaP7->rectA = thumbs[3];  // D
	anclaP7->rectB = anclaVisualizador;
	anclaP7->indiceA = 4;
	anclaP7->indiceB = 7;
	anclaP7->visible = true;
	anclaP7->dist = 150;

	Spring * diago0 = new Spring();
	diago0->k = k;
	diago0->rectA = anclaVisualizador;
	diago0->rectB = thumbs[1];  // D
	diago0->indiceA = 3;
	diago0->indiceB = 4;
	diago0->visible = false;
	diago0->diagonal = true;
	diago0->dist = 193;
	
	Spring * diago1 = new Spring();
	diago1->k = k;
	diago1->rectA = anclaVisualizador;
	diago1->rectB = thumbs[0];  // D
	diago1->indiceA = 5;
	diago1->indiceB = 4;
	diago1->visible = false;
	diago1->diagonal = true;
	diago1->dist = 193;
	
	Spring * diago2 = new Spring();
	diago2->k = k;
	diago2->rectA = anclaVisualizador;
	diago2->rectB = thumbs[2];  // D
	diago2->indiceA = 5;
	diago2->indiceB = 4;
	diago2->visible = false;
	diago2->diagonal = true;
	diago2->dist = 193;
	
	Spring * diago3 = new Spring();
	diago3->k = k;
	diago3->rectA = anclaVisualizador;
	diago3->rectB = thumbs[1];  // D
	diago3->indiceA = 6;
	diago3->indiceB = 4;
	diago3->visible = false;
	diago3->diagonal = true;
	diago3->dist = 193;
	
	Spring * diago4 = new Spring();
	diago4->k = k;
	diago4->rectA = anclaVisualizador;
	diago4->rectB = thumbs[3];  // D
	diago4->indiceA = 6;
	diago4->indiceB = 4;
	diago4->visible = false;
	diago4->diagonal = true;
	diago4->dist = 193;
	
	Spring * diago5 = new Spring();
	diago5->k = k;
	diago5->rectA = anclaVisualizador;
	diago5->rectB = thumbs[2];  // D
	diago5->indiceA = 7;
	diago5->indiceB = 4;
	diago5->visible = false;
	diago5->diagonal = true;
	diago5->dist = 193;

	Spring * diago6 = new Spring();
	diago6->k = k;
	diago6->rectA = anclaVisualizador;
	diago6->rectB = thumbs[4];  // D
	diago6->indiceA = 7;
	diago6->indiceB = 4;
	diago6->visible = false;
	diago6->diagonal = true;
	diago6->dist = 193;
	
	Spring * diago7 = new Spring();
	diago7->k = k;
	diago7->rectA = anclaVisualizador;
	diago7->rectB = thumbs[3];  // D
	diago7->indiceA = 2;
	diago7->indiceB = 4;
	diago7->diagonal = true;
	diago7->visible = false;
	diago7->dist = 193;
	
	
	springs.push_back(anclaP2);
    springs.push_back(anclaP3);
	springs.push_back(anclaP5);
	springs.push_back(anclaP6);
	springs.push_back(anclaP7);
	
	springs.push_back(diago0);
	springs.push_back(diago1);
	springs.push_back(diago2);
	springs.push_back(diago3);
	springs.push_back(diago4);
	springs.push_back(diago5);
	springs.push_back(diago6);
	springs.push_back(diago7);
}

void miniaturas::update(){
	/// todos se repelen entre si
    for(int i = 0; i < springs.size(); i++){
		springs[i]->update();
	}
	
	for(int i = 0; i < thumbs.size(); i++){
		int index = i;
		
		/*
		 repulsion para los botones
		 */
		for(int j = 0; j < thumbs.size(); j++){
			if(i != j){
				thumbs.at(j)->addRepulsionForce(thumbs.at(i),90,80);
			}
		}
		//repelen el fondo del visualizador
		/*
		 p9     p4     p8
		 |             |
		 p3 -p5-p6-p7- p2
		 */
		
		thumbs.at(i)->addRepulsionForce(anclaVisualizador->puntos.at(2),150,150);
		thumbs.at(i)->addRepulsionForce(anclaVisualizador->puntos.at(3),150,150);
		
		thumbs.at(i)->addRepulsionForce(anclaVisualizador->puntos.at(8),180,150);
		thumbs.at(i)->addRepulsionForce(anclaVisualizador->puntos.at(9),180,150);	
		
		thumbs.at(i)->addRepulsionForce(anclaVisualizador->puntos.at(5),110,120);
		thumbs.at(i)->addRepulsionForce(anclaVisualizador->puntos.at(6),110,120);
		thumbs.at(i)->addRepulsionForce(anclaVisualizador->puntos.at(7),110,120);
		
		
        thumbs.at(i)->bounceOffWalls();
		thumbs.at(i)->update();
	}
}

void miniaturas::drawCircle(){
    ofPushMatrix();
    
	for(int i = 0; i < springs.size(); i++){
		springs[i]->draw();
	}

    for (int i = 0; i < thumbs.size(); i++) {
        thumbs[i]->drawThumb();
    }

    
    ofPopMatrix(); 
}

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
