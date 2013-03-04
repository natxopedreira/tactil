//
//  Ancla.cpp
//  tactil
//
//  Created by natxo pedreira on 01/02/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "Ancla.h"

//---------------------------------------------------------------------
Ancla::Ancla(){
	rectA = NULL;
	rectB = NULL;
	visible = false;
	indiceA = 0;
	indiceB = 0;
}
//---------------------------------------------------------------------
Ancla::~Ancla(){
	if ((rectA == NULL) || (rectB == NULL)){
		return;
	}
	
	delete rectA;
	delete rectB;
}


//---------------------------------------------------------------------
void Ancla::update(){
	if ((rectA == NULL) || (rectB == NULL)){
		return;
	}
	ofPoint puntoA = rectA->puntos.at(indiceA);
	ofPoint puntoB = rectB->puntos.at(indiceB);
	
	float mutualDist = (puntoA - puntoB).length();
	float springForce = (k * (dist - mutualDist));
	
	
	ofPoint frcToAdd = (puntoA - puntoB).normalized() * springForce;
	
	/// queremos que los cuadrados pekes no afecten al grande, que no tiren de el
    
	if(!rectA->leader) rectA->addForce(frcToAdd);
	frcToAdd *= -1;
	if(!rectB->leader && !rectB->principal) rectB->addForce(frcToAdd);
    
}


//---------------------------------------------------------------------
void Ancla::draw(){
	
	if ((rectA == NULL) || (rectB == NULL) || !visible){
        return;
        
	}
	
	ofPushStyle();
    ofSetLineWidth(1);
    ofLine(rectA->puntos.at(indiceA), rectB->puntos.at(indiceB));
    ofCircle(rectA->puntos.at(indiceA), 2);
    ofCircle(rectB->puntos.at(indiceB), 2);
	ofPopStyle();
}