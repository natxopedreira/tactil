//
//  imageViewer.h
//  tactil
//
//  Created by ignacio pedreira gonzalez on 10/03/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef tactil_imageViewer_h
#define tactil_imageViewer_h

#include "baseShape.h"

class imageViewer : public baseShape {
public:
    imageViewer();
	~imageViewer();
    
    void    setup(float _anchoMax, float _altoMax);
    void    update();
    void    draw(float _px, float _py);
    
    void    cargaImagen(string _url);
    void    cambiaTamano(float _nuevoAlto);
    
private:
    float   anchoMax, altoMax;
    ofFbo   fbo;
    ofImage imagen;
    ofVideoPlayer vidrio;
    float   escalaX,escalaY;
    bool    esVideo;
};

#endif
