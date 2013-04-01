//
//  controllerHotSpot.h
//  tactil
//
//  Created by ignacio pedreira gonzalez on 01/04/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef tactil_controllerHotSpot_h
#define tactil_controllerHotSpot_h

#include "hotSpot.h"
#include "ofxXmlSettings.h"

class controllerHotSpot {
    
public:
    
    void    setup();
    void    update();
    void    draw();
    
    void    savePositions();
    void    loadPositions();
    
    void    debugOn();
    void    debugOff();
    
    vector<hotSpot> puntos;
    
    int cuantos;
    int idPress;
    
    
    bool    editable;
    
    
    void mouseMoved(ofMouseEventArgs & arg);
    void mouseDragged(ofMouseEventArgs & arg);
    void mousePressed(ofMouseEventArgs & arg);
    void mouseReleased(ofMouseEventArgs & arg);
    
    
};

#endif
