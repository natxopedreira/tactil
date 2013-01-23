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
    
    string  nombre;
    
    void activalo();
    void desactivalo();
    
    void urdate();
    void drawThumb();
    
    void onCompleteScala(float* arg);
    
private:
    bool    activo;
    bool    runningTween;
    float   escalador;
};
#endif
