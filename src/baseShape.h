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
#include "ofxTweenzor.h"

class baseShape : public ofRectangle {
public:
	baseShape();
	~baseShape();
	string  nombre;
	
	void roundedRect(float x, float y, float w, float h, float r);  
	void quadraticBezierVertex(float cpx, float cpy, float x, float y, float prevX, float prevY);
	
	void    addForce( ofPoint _force );
	bool    suicidate();
	
	void    addAttractionForce(ofPoint p, ofPoint offset, float radius, float scale);
	
	void    addRepulsionForce(ofPoint p, float radius, float scale);
    void    moveTo(float _x, float _y);
	
	void    addRepulsionForce(baseShape *p, float radius, float scale);
	
	void    bounceOffWalls();
	ofPoint	dimeCentro();
	
	void	update();
	void	drawRound();
	
	void onCompleteCambio(float* arg);
	
	float   damping;
	float	mass;
    int     nId;
    int     escala;
	
	ofColor color, colorCambio;
	bool	leader; /// eres leader cuando eres el que dragea
	bool	principal; /// indica si eres el recuadro donde se ven las cosas, osease el grande
	bool	activo; /// para cuando eres un boton
	bool	useBtn; /// eres un boton?
	
	vector<ofPoint>		puntos;
	
	void	cambiate(int _r,int _g, int _b, float _delay); // al cambiar de seccion el rectanlge cambia de color
	bool	cambiandose;
	float	cambioY; // posicion de la cortina
	
	ofEvent<string>	meCambie;
	
private:
    ofPoint vel;
    ofPoint acc;
};

#endif