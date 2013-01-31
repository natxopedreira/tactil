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
	
	this->set(ofPoint(0,0),0,0);
	
	/*
     
    p0 ---------- p1
     |            |
	 |     p4     |
	 |            |
	p3 ---------- p2
	
	 punto de anclaje para el muelle
	 */
	ofPoint p0,p1,p2,p3,p4;
	
	p0.set(0,0);
	p1.set(0,0);
	p2.set(0,0);
	p3.set(0,0);
	p4.set(0,0);
	
	puntos.push_back(p0);
	puntos.push_back(p1);
	puntos.push_back(p2);
	puntos.push_back(p3);
	puntos.push_back(p4);
	
	vel.set(0, 0);
    acc.set(0,0,0);
    
	damping = 0.17f;
	mass = 1.f;
	
	color.set(0,0,0);
	
	leader = false; //leader es si te estan drageando
	principal	=	false;
    
    escala   =   1;
}
//------------------------------------------------------------
baseShape::~baseShape(){
    puntos.clear();
}


//------------------------------------------------------------
void baseShape::update(){
	/*
	 
	 p0 ---------- p1
	 |             |
	 |      p4     |
	 |             |
	 p3 ---------- p2
	 
	 */

    vel += acc;
    vel *= 1.0f - damping;

    this->x += vel.x;
	this->y += vel.y;
	
	
    acc *= 0;
	
	puntos.at(0).set(this->x,this->y);
	puntos.at(1).set(this->x+this->width * escala,this->y);
	puntos.at(2).set(this->x+this->width * escala,this->y+this->height * escala);
	puntos.at(3).set(this->x,this->y+this->height * escala);
	puntos.at(4).set(this->getCenter());
	
}

//------------------------------------------------------------
void baseShape::drawRound(){
	ofPushStyle();
		ofSetColor(color);
		roundedRect(this->x, this->y, this->width * escala, this->height * escala,10);
	ofPopStyle();
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
			
			//cout << "dsdfsdf" << endl;
        }
    }
}

//------------------------------------------------------------
void baseShape::bounceOffWalls(){
	
	// sometimes it makes sense to damped, when we hit
	bool bDampedOnCollision = true;
	bool bDidICollide = false;
	
	// what are the walls
	float minx = 0;
	float miny = 0;
	float maxx = ofGetWidth()-this->width;
	float maxy = ofGetHeight()-this->height/2;
	
	if (this->x > maxx){
		this->x = maxx; // move to the edge, (important!)
		vel.x *= -1;
		bDidICollide = true;
	} else if (this->x < minx){
		this->x = minx; // move to the edge, (important!)
		vel.x *= -1;
		bDidICollide = true;
	}
	
	if (this->y > maxy){
		this->y = maxy; // move to the edge, (important!)
		vel.y *= -1;
		bDidICollide = true;
	} else if (this->y < miny){
		this->y = miny; // move to the edge, (important!)
		vel.y *= -1;
		bDidICollide = true;
	}
	
	if (bDidICollide == true && bDampedOnCollision == true){
		vel *= 0.3;
	}
	
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
