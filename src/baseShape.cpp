/*
 *  RoundRectangle.cpp
 *  tactil
 *
 *  Created by ignacio garcia on 04/01/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "baseShape.h"

baseShape::baseShape(){
	//ofRectangle::set(0,0, 0,0);
	//this->set(ofPoint(0,0),0,0);
	
	/*
     
    p0 ---------- p1
     |            |
	p9     p4     p8
	 |            |
	p3 -p5-p6-p7- p2
	
	 punto de anclaje para el muelle
    
    */
	
    ofPoint p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14;
	
	p0.set(0,0);
	p1.set(0,0);
	p2.set(0,0);
	p3.set(0,0);
	p4.set(0,0);
	p5.set(0,0);
	p6.set(0,0);
	p7.set(0,0);
	p8.set(0,0);
	p9.set(0,0);
    p10.set(0,0);
    p11.set(0,0);
    p12.set(0,0);
    p13.set(0,0);
    p14.set(0,0);
	
	puntos.push_back(p0);
	puntos.push_back(p1);
	puntos.push_back(p2);
	puntos.push_back(p3);
	puntos.push_back(p4);
	puntos.push_back(p5);
	puntos.push_back(p6);
	puntos.push_back(p7);
	puntos.push_back(p8);
	puntos.push_back(p9);
    puntos.push_back(p10);
    puntos.push_back(p11);
    puntos.push_back(p12);
    puntos.push_back(p13);
    puntos.push_back(p14);
	
	vel.set(0, 0);
    acc.set(0,0,0);
    
	damping = 0.09f;
	mass = 1.f;
	
	color.set(0,0,0);
	
	leader = false; //leader es si te estan drageando
	principal	=	false;
    
    escala   =   1;
	
	cambiandose = false;
	useBtn = false;
	activo = false;
	desactivado = false;
    useBtnIdioma = false;
    
	cambioY = 0;
	
	nombre = "";
    cantidadCrece = 0;
    //ofRegisterMouseEvents(this);
}
//------------------------------------------------------------
baseShape::~baseShape(){
    //ofUnregisterMouseEvents(this);
    
    puntos.clear();
    urls.clear();
    
    txt_cast.clear();
    txt_eng.clear();
    txt_fr.clear();
    txt_gal.clear();
    
    pies_cast_titular.clear();
    pies_cast_cuerpo.clear();
    
    pies_gal_titular.clear();
    pies_gal_cuerpo.clear();
    
    pies_eng_titular.clear();
    pies_eng_cuerpo.clear();
    
    pies_fr_titular.clear();
    pies_fr_cuerpo.clear();
    
    titular_cast.clear();
    titular_eng.clear();
    titular_gal.clear();
    titular_fr.clear();
}

bool  baseShape::suicidate(){
	
	if(this->y > ofGetHeight()){
		return true;
	}else{
		return false;
	}
}

//------------------------------------------------------------
void baseShape::update(){
    
    this->set(this->x,this->y, this->width, this->height+cantidadCrece);

	/*
	 
	 p0 ---------- p1 -------
     |                                         |
	 p9              p4                        p8
	 |                                          |
	p11- p3 -p5-p6-p7- p2 - p12 - p13 - p14 -  p10
	 
	 */

    vel += acc;
    vel *= 1.0f - damping;

    this->x += vel.x;
	this->y += vel.y;
	
	if(principal){
        acc *= .9;
	}else{
         acc *= 0;
    }
	puntos.at(0).set(this->x,this->y);
	puntos.at(1).set(this->x+this->width * escala,this->y);
    puntos.at(2).set(this->x+265 * escala,this->y+this->height * escala);
    puntos.at(4).set(this->getCenter());
    
    //// separacion de 60,50 + 10 de margen
    
	puntos.at(3).set(this->x + 25,this->y+this->height * escala);
	puntos.at(5).set(this->x+85 * escala,this->y+this->height * escala);
	puntos.at(6).set(this->x+145 * escala,this->y+this->height * escala);
	puntos.at(7).set(this->x+205 * escala,this->y+this->height * escala);
	
    puntos.at(8).set(this->x+this->width * escala,this->y+(this->height/2) * escala);
	puntos.at(9).set(this->x,this->y+(this->height/2) * escala);
	
    puntos.at(10).set(this->x+this->width * escala,this->y+this->height * escala);
    
    puntos.at(11).set(this->x,this->y+this->height);
    
    puntos.at(12).set(this->x+325 * escala,this->y+this->height * escala);
    puntos.at(13).set(this->x+385 * escala,this->y+this->height * escala);
    puntos.at(14).set(this->x+445 * escala,this->y+this->height * escala);
}

//------------------------------------------------------------
void baseShape::drawRound(){

	ofPushStyle();
        ofSetColor(0,0,0,150);
		roundedRect(this->x+3, this->y+3, this->width * escala, this->height * escala,14);
    
        ofSetColor(color.r,color.g,color.b,255);
		
        roundedRect(this->x, this->y, this->width * escala, this->height * escala,14);
	
	if(cambiandose){
		/// dibujamos la cortina
		ofSetColor(colorCambio);
		roundedRect(this->x, this->y, this->width * escala, (this->height-cambioY) * escala ,14);
		
	}
    
    
    /// debug de los puntos para verlos
    /*
    ofSetColor(0);
    for (int i  = 0 ; i < puntos.size(); i++) {
        ofCircle(puntos[i].x, puntos[i].y, 5);
    }
	ofPopStyle();
    */
}



//------------------------------------------------------------
//---------- FUERZAS -----------------------------------------
//------------------------------------------------------------
void baseShape::addForce(ofPoint _force){
    acc += _force;
}

//------------------------------------------------------------
void baseShape::addAttractionForce(ofPoint posOfForce, ofPoint offset, float radius, float scale){
	
	// ----------- (2) calculate the difference & length
	
	ofPoint diff	= (this->getCenter()) - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
		diff.normalize();
		acc -= diff * scale * pct;
    }
}

//-----------------------------
void baseShape::moveTo(float _x, float _y){
    // mover a
    x += _x;
    y += _y;
}

//------------------------------------------------------------
void baseShape::addRepulsionForce(ofPoint posOfForce, float radius, float scale){
    
	// ----------- (2) calculate the difference & length
	
	ofPoint diff	= (this->getCenter()) - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
        diff.normalize();
        acc += diff * scale * pct;
    }
}
//------------------------------------------------------------
ofPoint	 baseShape::dimeCentro(){
	return this->getCenter();
}
//------------------------------------------------------------
void baseShape::addRepulsionForce(baseShape *p, float radius, float scale){
	if (p != NULL){
		
        // ----------- (1) make a vector of where this Vertex p is:
        ofPoint posOfForce;
        posOfForce.set(p->dimeCentro().x,p->dimeCentro().y);
        
		
		
        // ----------- (2) calculate the difference & length
        
        ofPoint diff	= this->dimeCentro() - posOfForce;
        float length	= diff.length();
       
        // ----------- (3) check close enough
        
        bool bAmCloseEnough = true;
        if (radius > 0){
            if (length > radius){
                bAmCloseEnough = false;
            }
        }
        
        // ----------- (4) if so, update force
        
        if (bAmCloseEnough == true){
            float pct = 1 - (length / radius);  // stronger on the inside
            diff.normalize();
            addForce(diff * scale * pct);
            p->addForce(diff * scale * pct * -1);
			
        }
    }
}

//------------------------------------------------------------
void baseShape::bounceOffWalls(){
}


///
void baseShape::roundedRect(float x, float y, float w, float h, float r) {  
    ofBeginShape();  
        ofVertex(x+r, y);  
        ofVertex(x+w-r, y);  
        quadraticBezierVertex(x+w, y, x+w, y+r, x+w-r, y);  
        ofVertex(x+w, y+h-r);  
        quadraticBezierVertex(x+w, y+h, x+w-r, y+h, x+w, y+h-r);  
        ofVertex(x+r, y+h);  
        quadraticBezierVertex(x, y+h, x, y+h-r, x+r, y+h);  
        ofVertex(x, y+r);  
        quadraticBezierVertex(x, y, x+r, y, x, y+r);  
    ofEndShape();  
}  

void baseShape::quadraticBezierVertex(float cpx, float cpy, float x, float y, float prevX, float prevY) {  
	float cp1x = prevX + 2.0/3.0*(cpx - prevX);  
	float cp1y = prevY + 2.0/3.0*(cpy - prevY);  
	float cp2x = cp1x + (x - prevX)/3.0;  
	float cp2y = cp1y + (y - prevY)/3.0;  
	
	// finally call cubic Bezier curve function  
	ofBezierVertex(cp1x, cp1y, cp2x, cp2y, x, y);  
};  


void baseShape::cambiate(int _r,int _g, int _b, float _delay){
	/// cambias de color
	/// moviendo la cortina
	cambiandose = true;
	cambioY = this->getHeight()-10;
	Tweenzor::add(&cambioY, cambioY, 0, _delay, 0.5f, EASE_IN_SINE);
	
    
    
	Tweenzor::addCompleteListener( Tweenzor::getTween(&cambioY), this, &baseShape::onCompleteCambio);
	colorCambio.set(_r,_g,_b);
}

void baseShape::crece(int _altura){
	/// cambias de color
	/// moviendo la cortina

	cambiandose = true;
    float diff = (this->height+cantidadCrece)-_altura;
    float g = ofMap(abs(this->height-diff), 0, 400, .1, .7);
    
	Tweenzor::add(&cantidadCrece, cantidadCrece, _altura, 0.0f,  g, EASE_IN_SINE);
}

void baseShape::onCompleteCambio(float* arg){
	color.set(colorCambio.r, colorCambio.g, colorCambio.b);
	cambiandose = false;
	ofNotifyEvent(meCambie,nombre,this); //seleccionBoton
}


