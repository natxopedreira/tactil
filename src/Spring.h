#ifndef SPRING
#define SPRING

#include "ofMain.h"
#include "baseShape.h"

class Spring {
public:
	
    Spring();
	// ~Spring();
	
    void update();
    void draw();
    
    baseShape * rectA;
    baseShape * rectB;
	
    float dist;
    float k;	 // this is the k, Springiness constant
	
	bool	visible;
	bool	diagonal;
	bool	horizontal;
	
	int	indiceA;	//es el indice  del rectA para saber cual de los puntos que forman en rectangle es el ancla
	int	indiceB;	//es el indice  del rectB para saber cual de los puntos que forman en rectangle es el ancla
};

#endif