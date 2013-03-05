//
//  thumb.h
//  tactil
//
//  Created by natxo pedreira on 15/01/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef THUMB
#define THUMB

#include "baseShape.h"

class thumb : public baseShape {
public:
    thumb();
	~thumb();
    
    void activala();
    void desactivala();
    void ponListeners();
    
    void urdate();
    void drawThumb();
    ofImage img;
    
    void mouseMoved(ofMouseEventArgs & args);
    void mouseDragged(ofMouseEventArgs & args);
    void mousePressed(ofMouseEventArgs & args);
    void mouseReleased(ofMouseEventArgs & args);
    
    bool dragBoton;
    // offset para el dragging
    ofVec2f offsetDragThumb;
    
    
private:
    bool    activo;
};
#endif
