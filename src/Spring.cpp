#include "Spring.h"

//---------------------------------------------------------------------
Spring::Spring(){
	rectA = NULL;
	rectB = NULL;
	visible = false;
	indiceA = 0;
	indiceB = 0;
}
//---------------------------------------------------------------------
Spring::~Spring(){
	if ((rectA == NULL) || (rectB == NULL)){
		return;
	}
	
	delete rectA;
	delete rectB;
}

//---------------------------------------------------------------------
void Spring::update(){
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
void Spring::draw(){
	
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


