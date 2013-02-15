//
//  miniaturas.h
//  tactil
//
//  Created by natxo pedreira on 14/01/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef MINIATURAS
#define MINIATURAS
#include "ofMain.h"
#include "thumb.h"
#include "Spring.h"
#include "visualizador.h"

class miniaturas{
public:
    miniaturas();
    ~miniaturas();
    
    void setup(float _px, float _py, ofColor _color);
    void setAncla(visualizador * a);
	void cambiaK(float v);
	void limpiaMinis();

	void cambiaKDiagonal(float v);
	void cambiaKHorizontal(float v);
	void cambiaDampMiniaturas(float v);
	
    void update();
    void drawCircle();
    void creaGrid(ofColor _color);
	
    ofPoint origen;
    vector<thumb*> thumbs; /// cambiamos el vector para ser de baseShape
    vector<Spring*> springs;
	vector<thumb*>	thumbsSalida; ///cuando cambiamos de seccion pasamos aqui las minis
    
    visualizador * anclaVisualizador;
	
	float _kMuellesDiagonales;
	float _kHorizontal;
	float _kmuelles;
	float _dampCajasMiniaturas;
    float radio;
    float k,damp;
    
    
	bool _listas; // si las minis esta colocadas
    
	/// proceso es:
	// - posicion
	// - tension
	// -  repulsion;
    
    int  miniActiva;
    vector<string>  urls_mini;
    vector<string>  txt_cast_mini;
    vector<string>  txt_eng_mini;
    vector<string>  txt_fr_mini;
};

#endif
