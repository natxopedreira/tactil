//
//  hotSpot.h
//  tactil
//
//  Created by ignacio pedreira gonzalez on 01/04/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef tactil_hotSpot_h
#define tactil_hotSpot_h
#include "ofMain.h"

class hotSpot {
    
public:
    hotSpot();
    
    void setup(int _numXml);
    void udpate();
    void draw();
    void setPosition(ofPoint _pos);
    
    ofPoint damePos();
    int dameIndex();
    
    int ancho, alto;   
private:
    ofPoint posicion;
    bool editable;
    int  numeroXml;

};


#endif
