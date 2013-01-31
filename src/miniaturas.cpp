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
    
    thumbs.clear();
    circlePoints.clear();
}

void miniaturas::setup(int cuantas, float _px, float _py){
    
    /// fill the miniatures vector
    for(int i = 0; i < cuantas; i++){
        thumb * b = new thumb();
        b->set(0,0, 45, 45);
        b->color.set(171,209,217);
        b->nombre = "mini";
        thumbs.push_back(b);
    }
    /// create el grid
    creaGrid();
   
}
void miniaturas::creaGrid(){
    int cuantas = thumbs.size();
    int numColumnas = 4;
    
    int anchoMini = 50;
    int altoMini = 50;
    
    int col, row = 0;
    
    for (int i = 0; i < cuantas; i++) {
        col = i % numColumnas;
        row = int( i / numColumnas);
        
        thumbs[i]->x  = (anchoMini + 30) * col;
        thumbs[i]->y  = (altoMini + 30) * row;
    }

    //
    // ponemos los springs
    for (int i = 0; i < cuantas-1; i++) {
      
        row = int( i / numColumnas);
        cout << i << endl;
        
        Spring * sp = new Spring();
        sp->k = 0.04;
        sp->rectA = thumbs[i];
        sp->rectB = thumbs[i+1];
        sp->indiceA = 4;
        sp->indiceB = 4;
        sp->dist = ofDist(thumbs[i]->getCenter().x, thumbs[i]->getCenter().y, thumbs[i+1]->getCenter().x, thumbs[i+1]->getCenter().y);
        sp->visible = true;
        
        springs.push_back(sp);
        
    }
    

    
   
}

void miniaturas::update(){
    for(int i = 0; i < springs.size(); i++){
		springs[i]->update();
	}
    for(int i = 0; i < thumbs.size(); i++){
		thumbs[i]->update();
	}
    
    /// hay que actualizar el vector con las lineas
    
   // centro.x += _dx * .075;
   // centro.y += _dy * .075;
    
    //lineas.clear();
    
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