//
//  fichaZoom.h
//  tactil
//
//  Created by ignacio pedreira gonzalez on 29/03/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

/// basicamente una version de esto para obtener la parte de tuio
/// https://github.com/patriciogonzalezvivo/ofxKeyboard/blob/master/src/ofxKeyboard.h

#ifndef tactil_fichaZoom_h
#define tactil_fichaZoom_h

#include "ofMain.h"
#define USE_TUIO

#ifdef USE_TUIO
#define tuioCursorSpeedMult				0.5	// the iphone screen is so small, easy to rack up huge velocities! need to scale down 
#define tuioStationaryForce				0.001f	// force exerted when cursor is stationary
#include "ofxTuio.h"
#endif


struct tCursor {
	int	idN;
	ofPoint loc;
};

class fichaZoom{
    public:
    fichaZoom();
    
    void setup(ofPoint _pto, int _ancho, int _alto, ofColor _color);
    void update();
    void draw();
    void cargaImagen(string _url);
    
    // Acctions
	void rotate(float _angle){ angle += _angle;};
	void resize(float _resize);
	
    
    bool isOver(ofPoint _loc);
    bool isOnBorder(ofPoint _loc);
    
    ofTrueTypeFont  fuente;
    
    bool    visible;
    ofColor colorBase;
    string titulo;
    
#ifdef USE_TUIO
	ofxTuioClient * tuioClient;
	void	setTuioClient (ofxTuioClient * _tuioClient);
    
	// TUIO Events Handlers
	void	tuioAdded(ofxTuioCursor & tuioCursor);
	void	tuioRemoved(ofxTuioCursor & tuioCursor);
	void	tuioUpdated(ofxTuioCursor & tuioCursor);
    
    vector<tCursor>	cursorsOnBorder;
	ofPoint        oldLoc[3];
#endif
    
    
private:
    
    ofPoint	position;							// Cartesian coordinates of the cent
	float	angle;								// The keyboard could be rotated.
	float	width,height;						// Width and Height
    ofImage imagen;
    float anchoImagen;
    
    ofEvent<float>      scaling;
	ofEvent<float>      rotation;
	ofEvent<ofPoint>	moving;
};
#endif
