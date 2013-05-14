//
//  SimplePanZoom.h
//  panZoomDemo
//
//  Created by Patricio Gonzalez Vivo on 4/17/13.
//
//

#ifndef SIMPLE_PAN_ZOOM
#define SIMPLE_PAN_ZOOM

#include "ofMain.h"
#include "ofxTuio.h"

#define	MAX_TOUCHES		2
#define MIN_FINGER_DISTANCE 70.0f /* in pixels - zooming when fingers were too close was unaccurate & jumpy*/

struct Finger : public ofVec2f {
    int ID;
};

struct FingerTap : public ofVec2f {
    int ID;
    unsigned long tiempo;
};

class SimplePanZoom : public ofRectangle {
public:
	
	SimplePanZoom();
    
	void    setZoom(float z){ zoom = desiredZoom = z;}  //set a zoom level
	float   getZoom(){ return zoom; } //current zoom level
    
	ofVec2f getOffset(){return -offset;}
    void    centrate();
	
    
    void tuioAdded(ofxTuioCursor & tuioCursor);
    void tuioRemoved(ofxTuioCursor & tuioCursor);
    void tuioUpdated(ofxTuioCursor & tuioCursor);
    
    
	void    update();
    void    draw( ofBaseHasTexture &_bTex );
    
    float   minZoom;
	float   maxZoom;
    float   desiredZoom;
    
    ofVec2f desiredOffset;
    
    float   smoothFactor;
    float   deltaTime;
    
    bool    bDebug;
    bool    tuioDoubleTap;
    
    
private:
    void    applyConstrains();
    
	ofVec2f offset;
    ofVec2f maxOffset;
    
    float zoomDiff;
    float zoom;
	
    vector<Finger> touches;
    
    FingerTap ultimoTap;
    //    vector<int> touchIDOrder;
    //    ofVec2f     lastTouch[MAX_TOUCHES];
    //    bool        touching[MAX_TOUCHES];
    
};

#endif
