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
#include "redondo.h"

class baseShape : public ofRectangle {
public:
	baseShape();
	~baseShape();
	string  nombre;
	
	
    void ofRoundedRect(float x,float y,float w,float h,float r);
    
	void    addForce( ofPoint _force );
	bool    suicidate();
    void    crece(int _altura);
	
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
    float   cantidadCrece;
	
	ofColor color, colorCambio;
	bool	leader; /// eres leader cuando eres el que dragea
	bool	principal; /// indica si eres el recuadro donde se ven las cosas, osease el grande
	bool	activo; /// para cuando eres un boton
	bool	useBtn; /// eres un boton?
    bool    useBtnIdioma; // eres un boton de idioma
    bool desactivado; /// eres un boton desactivado?
	
	vector<ofPoint>		puntos;
	
	void	cambiate(int _r,int _g, int _b, float _delay); // al cambiar de seccion el rectanlge cambia de color
	bool	cambiandose;
	float	cambioY; // posicion de la cortina
	
	ofEvent<string>	meCambie;
    
    vector<string>  urls;
    vector<string>  txt_cast;
    vector<string>  txt_eng;
    vector<string>  txt_fr;
    vector<string>  txt_gal;
    
    vector<string>  pies_cast_titular;
    vector<string>  pies_cast_cuerpo;
    
    vector<string>  pies_gal_titular;
    vector<string>  pies_gal_cuerpo;
    
    vector<string>  pies_eng_titular;
    vector<string>  pies_eng_cuerpo;
    
    vector<string>  pies_fr_titular;
    vector<string>  pies_fr_cuerpo;
    
    vector<string>  titular_cast;
    vector<string>  titular_eng;
    vector<string>  titular_gal;
    vector<string>  titular_fr;
    
private:
    ofPoint vel;
    ofPoint acc;
};

#endif