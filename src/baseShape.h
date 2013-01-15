/*
 *  RoundRectangle.h
 *  tactil
 *
 *  Created by ignacio garcia on 04/01/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef BASE_SHAPE
#define BASE_SHAPE

#include "ofMain.h"

class baseShape : public ofRectangle {
public:
	baseShape();
	~baseShape();
	
	void roundedRect(float x, float y, float w, float h, float r);  
	void quadraticBezierVertex(float cpx, float cpy, float x, float y, float prevX, float prevY);
	
	void    addForce( ofPoint _force );
	void    addAttractionForce(ofPoint p, ofPoint offset, float radius, float scale);
	void    addRepulsionForce(ofPoint p, float radius, float scale);
	
	void    addRepulsionForce(baseShape *p, float radius, float scale);
	
	void    bounceOffWalls();
	ofPoint	dimeCentro();
	
	void	update();
	void	drawRound();
	
	float   damping;
	float	mass;
    int     nId;
    int     escala;
	
	ofColor color;
	bool	leader; /// eres leader cuando eres el que dragea
	bool	principal; /// indica si eres el recuadro donde se ven las cosas, osease el grande
	vector<ofPoint>		puntos;
	
private:
    ofPoint vel;
    ofPoint acc;
};

#endif