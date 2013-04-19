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

#define	MAX_TOUCHES		12
#define MIN_FINGER_DISTANCE 70.0f /* in pixels - zooming when fingers were too close was unaccurate & jumpy*/


class SimplePanZoom : public ofRectangle {
public:
	
	SimplePanZoom();
    
	void    setZoom(float z){ zoom = desiredZoom = z;}  //set a zoom level
	float   getZoom(){ return zoom; } //current zoom level
    
	ofVec2f getOffset(){return -offset;}
	
    ofVec2f screenToWorld(const ofVec2f & p); //convert a point from current screen units to world units
	ofVec2f worldToScreen(const ofVec2f & p); //convert a point from world units to current screen units
	
    void    touchDown(ofTouchEventArgs &touch);
	void    touchMoved(ofTouchEventArgs &touch);
	void    touchUp(ofTouchEventArgs &touch);
	void    touchDoubleTap(ofTouchEventArgs &touch);
    
	void    update();
    void    draw( ofBaseHasTexture &_bTex );

    float   minZoom;
	float   maxZoom;
    float   desiredZoom;
    
    ofVec2f desiredOffset;
    
    float   smoothFactor;
    float   deltaTime;
    
    bool    bDebug;
    
private:
    void    applyConstrains();
    
	ofVec2f offset;
    ofVec2f maxOffset;
    
    float zoomDiff;
    float zoom;
	
    vector<int> touchIDOrder;
    ofVec2f lastTouch[MAX_TOUCHES];
    bool touching[MAX_TOUCHES];
    
};

#endif
