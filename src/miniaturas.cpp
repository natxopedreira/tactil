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
    centro.set(0, 0);
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
        b->nombre = "mini_"+ofToString(i);
        thumbs.push_back(b);
    }
   
   
}
void miniaturas::setAncla(visualizador a){
    anclaVisualizador = &a;
    
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
    int anchoMini = 50;
    int altoMini = 50;
    
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
        thumbs[i]->x  = (anchoMini + 57) * col;
        thumbs[i]->y  = (altoMini + 57) * row;
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
                
                hayC = true;
                
                Spring * sp = new Spring();
                sp->k = 0.0025;
                sp->rectA = tabla[x][y];
                sp->rectB = tabla[x][y+1];
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
                    
                    hayB = true;
                    
                    Spring * sp = new Spring();
                    sp->k = 0.0025;
                    sp->rectA = tabla[x][y];
                    sp->rectB = tabla[x+1][y];
                    sp->indiceA = 4;
                    sp->indiceB = 4;
                    sp->dist = ofDist(tabla[x][y]->getCenter().x, tabla[x][y]->getCenter().y,
                                      tabla[x+1][y]->getCenter().x, tabla[x+1][y]->getCenter().y);
                    sp->visible = true;
                    
                    springs.push_back(sp);
                    
                    if ( y+1 < tabla[x+1].size() ){
                        hayD = true;
                    }
                }
            }
            
            //  Si tiene B y C puede agregar la diagonal que le da estabilidad
            //
            if ( hayB && hayC ){
                
                Spring * sp = new Spring();
                sp->k = 0.0025;
                sp->rectA = tabla[x][y+1];  // C
                sp->rectB = tabla[x+1][y];  // B
                sp->indiceA = 4;
                sp->indiceB = 4;
                sp->dist = ofDist(tabla[x][y+1]->getCenter().x, tabla[x][y+1]->getCenter().y,
                                  tabla[x+1][y]->getCenter().x, tabla[x+1][y]->getCenter().y);
                sp->visible = true;
                
                springs.push_back(sp);
                
            }
            
            if ( hayD ){
                Spring * sp = new Spring();
                sp->k = 0.0025;
                sp->rectA = tabla[x][y];
                sp->rectB = tabla[x+1][y+1];  // D
                sp->indiceA = 4;
                sp->indiceB = 4;
                sp->dist = ofDist(tabla[x][y]->getCenter().x, tabla[x][y]->getCenter().y,
                                  tabla[x+1][y+1]->getCenter().x, tabla[x+1][y+1]->getCenter().y);
                sp->visible = true;
                
                springs.push_back(sp);
            }
        }
    }
    
    //anclamos las miniaturas al visualizador
    Spring * anclaDerecha = new Spring();
    anclaDerecha->k = 0.0025;
    anclaDerecha->rectA = anclaVisualizador;
    anclaDerecha->rectB = thumbs[0];
    anclaDerecha->indiceA = 4;
    anclaDerecha->indiceB = 4;
    
    
    //springs.push_back(anclaDerecha);
}

void miniaturas::update(){
    for(int i = 0; i < springs.size(); i++){
		springs[i]->update();
	}
    for(int i = 0; i < thumbs.size(); i++){
		thumbs[i]->update();
	}
    
    cout << anclaVisualizador->x << endl;
    /// tenemos un punto(destx, desty)
    /// para alinear las minis
    /// hay que calcular la distancia desde
    /// este punto al thumb
    
    
    
    
    
    
    /// hay que actualizar el vector con las lineas
    
   // centro.x += _dx * .075;
   // centro.y += _dy * .075;
    
    //lineas.clear();
    
}

void miniaturas::drawCircle(){
    ofPushMatrix();


    for (int i = 0; i < thumbs.size(); i++) {
        thumbs[i]->drawThumb();
    }
    for(int i = 0; i < springs.size(); i++){
		springs[i]->draw();
	}
    
    ofPopMatrix(); 

    
}