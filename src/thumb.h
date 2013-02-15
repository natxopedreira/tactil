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
    
    void urdate();
    void drawThumb();
    ofImage img;
    
private:
    bool    activo;
};
#endif
