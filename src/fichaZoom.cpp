//
//  fichaZoom.cpp
//  tactil
//
//  Created by ignacio pedreira gonzalez on 29/03/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "fichaZoom.h"

fichaZoom::fichaZoom(){
    
	angle = 0;
    
	position.x = ofGetWidth()/2;
	position.y = ofGetHeight()/2;
    
	width = 0;
	height = 0;
}

//---------------------------------
void fichaZoom::setup(ofPoint _pto, int _ancho, int _alto, ofColor _color){
    position = _pto;

	width = _ancho;
	height = _alto;
    
    colorBase.set(_color);
}

//---------------------------------
void fichaZoom::update(){

}

//---------------------------------
void fichaZoom::draw(){

    // Draw the keyboard frame
	ofPushMatrix();
        ofSetColor(colorBase);
        ofTranslate(position.x,position.y);
        ofRotateZ(ofRadToDeg(angle));
    
        ofRectRounded(-width*0.5, -height*0.5, width, height, 20);
	ofPopMatrix();
}

//---------------------------------
bool fichaZoom::isOver(ofPoint _loc){
	ofPoint dirToCenter = position - _loc;
	float theta = atan2(dirToCenter.x,dirToCenter.y)-(PI/2);
	float r = dirToCenter.length();
	float x = r * cos(theta + angle);
	float y = r * sin(theta + angle);
    
	if ( (x <= width/2) && (x >= -width/2) && (y <= height/2) && (y >= -height/2)) return true;
	else return false;
}

//---------------------------------
bool fichaZoom::isOnBorder(ofPoint _loc){
	float dist = position.distance(_loc);
    
	if ( (dist <= width*0.5) && (dist >= width*0.4)) return true;
    else return false;
}

//---------------------------------
#ifdef USE_TUIO
void fichaZoom::setTuioClient (ofxTuioClient * _tuioClient){
	tuioClient = _tuioClient;
    
	// HELP with this in order to be independent from the main.
	ofAddListener(tuioClient->cursorAdded,this,&fichaZoom::tuioAdded);
	ofAddListener(tuioClient->cursorRemoved,this,&fichaZoom::tuioRemoved);
	ofAddListener(tuioClient->cursorUpdated,this,&fichaZoom::tuioUpdated);
}

//---------------------------------
void fichaZoom::tuioAdded(ofxTuioCursor &tuioCursor){
	ofPoint loc = ofPoint(tuioCursor.getX()*ofGetWidth(),tuioCursor.getY()*ofGetHeight());
    
	if (isOver(loc)){					// IF the cursor is over the keyboard
					// ... and is not pressing a key
			//if (isOnBorder(loc)){		// ... and wish location is near the borders 
            tCursor c;
            c.idN = tuioCursor.getSessionId();
            c.loc = loc;
            
            if (cursorsOnBorder.size() == 0){	// If it´s the first finger over the border it will save remember it
                cursorsOnBorder.push_back(c);
                
            } else if (cursorsOnBorder.size() == 1){	// If it´s the second one it will check if it´s at the right distance
                cursorsOnBorder.push_back(c);
                
                oldLoc[0] = cursorsOnBorder[0].loc;
                oldLoc[1] = cursorsOnBorder[1].loc;
            }
			//}
    }
}

//---------------------------------
void fichaZoom::resize(float _resize){
	width *= _resize;
	height *= _resize;
}

//---------------------------------
void fichaZoom::tuioUpdated(ofxTuioCursor &tuioCursor){
	// First it will update the information of the fingers that are over the border
	for ( int i = 0; i < cursorsOnBorder.size(); i++)
		if (cursorsOnBorder[i].idN == tuioCursor.getSessionId())
			cursorsOnBorder[i].loc = ofPoint(tuioCursor.getX()*ofGetWidth(),tuioCursor.getY()*ofGetHeight());
    
	// Then check if there is two fingers over it
	if (cursorsOnBorder.size() == 2){
		int sta = -1;	// a NULL parameter
		int din = -1;	// a NULL parameter
        
		// First it will watch witch one is the static finger and witch one is the dinamic
		for ( int i = 0; i < cursorsOnBorder.size(); i++)
			if (cursorsOnBorder[i].loc == oldLoc[i]) sta = i;
			else din = i;
        
		// If one it´s the dinamic and the other one the static it´s all OK and it´s time to calculate new parameters
		if ((sta != -1) && (din != -1) && (din != sta)){
			ofPoint Di = oldLoc[sta] - oldLoc[din];		// Get Vector between OLD finger position
			ofPoint Dii = oldLoc[sta] - cursorsOnBorder[din].loc; // Get Vector between NEW finger position
            
			float di = Di.length();						// Get OLD finger distance
			float dii = Dii.length();					// Get NEW finger distance
            
			float scaleF = dii / di;					// Set the scale diference before and after
            
			float ri = -1*atan2(Di.x,Di.y)+(PI/2);		// Get OLD fingers inclination
			float rii = -1*atan2(Dii.x,Dii.y)+(PI/2);	// Get NEW fingers inclination
            
			float rotateF = rii - ri;					// Set the angle diference before and after
            
			ofPoint oldStaCursorToCenter = position - oldLoc[sta] ;	// Get the OLD vector from the static finger to the center of the keyboard
			float oldAngleToCenter = -1*atan2(oldStaCursorToCenter.x,oldStaCursorToCenter.y)+(PI/2);	// Get OLD Angle to the center 
			float oldRadioToCenter = oldStaCursorToCenter.length();		// Get the OLD distance from the static figer to the center
            
			float newRadioToCenter = oldRadioToCenter * scaleF;		// Set the NEW distance to the center
			float newAngleToCenter = oldAngleToCenter + rotateF;	// Set the NEW angle to the center
			ofPoint newStaCursorToCenter = ofPoint(newRadioToCenter*cos(newAngleToCenter),newRadioToCenter*sin(newAngleToCenter)); // Set the NEW vector from the static finger to the center of the keyboard
            
			resize(scaleF);											// RESIZE the scale diference proportion
			rotate(rotateF);										// ROTATE the diference in angle
			position = oldLoc[sta] + newStaCursorToCenter;			// MOVE	the draged distance
            
            
		}
        
		oldLoc[0] = cursorsOnBorder[0].loc;
		oldLoc[1] = cursorsOnBorder[1].loc;
	}
}

void fichaZoom::tuioRemoved(ofxTuioCursor &tuioCursor){
	for (int i = 0; i < cursorsOnBorder.size(); i++ )
		if (cursorsOnBorder[i].idN == tuioCursor.getSessionId())
			cursorsOnBorder.erase(cursorsOnBorder.begin()+i);
}
#endif