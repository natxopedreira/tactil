//
//  SimplePanZoom.cpp
//  panZoomDemo
//
//  Created by Patricio Gonzalez Vivo on 4/17/13.
//
//

#include "SimplePanZoom.h"

SimplePanZoom::SimplePanZoom(){
    smoothFactor = .7;
	zoom = desiredZoom =  1.0f;
    
    //	for (int i = 0; i < MAX_TOUCHES; i++){
    //		touching[i] = false;
    //	}
	
	minZoom = 0.1f;
	maxZoom = 10.0f;
	zoomDiff = -1.0f;
    
	offset.x = offset.y = desiredOffset.x = desiredOffset.y = 0.0f;
    
    bDebug = true;
    tuioDoubleTap = false;
    
    this->set(0,0,503,308);
    
    //zoom = desiredZoom = .4;
    
    tuioDoubleTap = false;
}

void SimplePanZoom::update(){
    if(smoothFactor>.1) smoothFactor-= .1;
	zoom = (smoothFactor) * desiredZoom + (1.0f - smoothFactor) * zoom;
	offset = (smoothFactor) * desiredOffset + (1.0f - smoothFactor) * offset;
    
    applyConstrains();
    
    
}

void SimplePanZoom::draw( ofBaseHasTexture &_bTex ){
    maxOffset.x = _bTex.getTextureReference().getWidth();
    maxOffset.y = _bTex.getTextureReference().getHeight();
    
    _bTex.getTextureReference().bind();
    
    glBegin(GL_QUADS);
    
    glTexCoord2f(-offset.x + 0      * 1.0f/zoom  , -offset.y + 0      * 1.0f/zoom);   glVertex3f(x,y,0);
    glTexCoord2f(-offset.x + width  * 1.0f/zoom  , -offset.y + 0      * 1.0f/zoom);   glVertex3f(x+width,y,0);
    glTexCoord2f(-offset.x + width  * 1.0f/zoom  , -offset.y + height * 1.0f/zoom);   glVertex3f(x+width,y+height,0);
    glTexCoord2f(-offset.x + 0      * 1.0f/zoom  , -offset.y + height * 1.0f/zoom);   glVertex3f(x,y+height,0);
    
    glEnd();
    _bTex.getTextureReference().unbind();
    
    
    if (bDebug){
        ofSetRectMode(OF_RECTMODE_CORNER);
        //        for (int i = 0; i < MAX_TOUCHES; i++){
        //            if (touching[i]) glColor4f(0, 1, 0, 1);
        //            else glColor4f(1, 0, 0, 1);
        //            float w = 8;
        //            ofRect( i * (w + 3), 3, w, w);
        //        }
        
        char msg[1000];
        sprintf(msg, " zoom: %.1f \n offset: %.1f, %.1f \n toques: %1i \n ", zoom, offset.x, offset.y,touches.size());
        glColor4f(1, 1, 1, 1);
        ofDrawBitmapString(msg, 3.0f, 25.0f);
        //ofDrawBitmapString(order, 3.0f, 55.0f);
    }
    
}
void SimplePanZoom::centrate(){
    
    float diffx = 0;
    if(maxOffset.x * zoom>503) diffx = 503 - maxOffset.x * zoom;
    
    float diffy = 0;
    
    if(maxOffset.y * zoom>308) diffy = 308 - maxOffset.y * zoom;
    
    desiredOffset.x = offset.x = diffx;
    desiredOffset.y = offset.x = diffy;
    
}
void SimplePanZoom::applyConstrains(){
    
    if ( desiredOffset.x > 0 ){
        desiredOffset.x = 0;
    }
    if( desiredOffset.y > 0 ){
        desiredOffset.y = 0;
    }
    
    if ( desiredOffset.x < -(maxOffset.x - 503 * 1.0/zoom) ){
        desiredOffset.x = -(maxOffset.x - 503 * 1.0/zoom);
    }
    
    if ( desiredOffset.y < -(maxOffset.y - 308 * 1.0/zoom) ){
        desiredOffset.y = -(maxOffset.y - 308 * 1.0/zoom);
    }
    
    if(zoom>maxZoom){
        setZoom(maxZoom);
    }else if (zoom<minZoom) {
        setZoom(minZoom);
    }
    
}

//------------------------------------ Tuio
void  SimplePanZoom::tuioAdded(ofxTuioCursor & tuioCursor){
    ofVec2f pos = ofVec2f(tuioCursor.getX() * ofGetWidth(), tuioCursor.getY() * ofGetHeight());
    
    if(inside(pos) && touches.size() < MAX_TOUCHES){
    
        Finger newFinger;
        newFinger.set(pos);
        newFinger.ID = tuioCursor.getFingerId();
        touches.push_back(newFinger);
    
        if (touches.size() >= 2){
            zoomDiff = touches[ touches.size()-2 ].distance( touches[touches.size()-1] );
        }
        
        if(ultimoTap.tiempo != .0) {  // only do this if we have a previous tap
            unsigned long nowTime = ofGetElapsedTimeMillis();
            
            unsigned long lastTime = ultimoTap.tiempo;
            //cout << "nowTime " << nowTime << " :: lastTime " << lastTime << endl;
            
            if(nowTime - lastTime < 200) {    // check time different between current and previous tap
                float dx = tuioCursor.getX() - ultimoTap.x; // horizontal distance
                float dy = tuioCursor.getY() - ultimoTap.y; // vertical distance
                float d2 = dx * dx + dy * dy; // square of distance between taps
                //            println(d2);
                if(d2 < .2){
                 tuioDoubleTap = true;
                    desiredZoom = minZoom;
                    desiredOffset.set(0, 0);
                } 
            }
        }
        
        FingerTap tap;
        tap.ID = tuioCursor.getFingerId();
        tap.set(tuioCursor.getX(),tuioCursor.getY());
        tap.tiempo = ofGetElapsedTimeMillis();
        
        ultimoTap = tap; // store info for next tap
        //ultimoTap
    }
}
void  SimplePanZoom::tuioRemoved(ofxTuioCursor & tuioCursor){
    
    if(touches.size()<=0) return;
    //cout << "entro a borrar " << touches.size() << endl;
    for (int i = touches.size()-1; i >= 0; i--) {
        if (touches[i].ID == tuioCursor.getFingerId() ){
            touches.erase(touches.begin()+i);
        }
    }
}

void  SimplePanZoom::tuioUpdated(ofxTuioCursor & tuioCursor){
    ofVec2f pos = ofVec2f(tuioCursor.getX() * ofGetWidth(),tuioCursor.getY() * ofGetHeight());

    if(tuioDoubleTap) !tuioDoubleTap;
    
    if(inside(pos)){
    
    for (int i = touches.size()-1; i >= 0; i--) {
        if (touches[i].ID == tuioCursor.getFingerId() ){
            ofVec2f diff = touches[i] - pos;
            touches[i].set(pos);
            desiredOffset = desiredOffset - diff * (maxZoom/zoom);
            applyConstrains();
        }
    }
    
    //	}else
    if (touches.size() >= 2){
        
        // 2 fingers >> zoom
        ofVec2f A,B;
        A.set(touches[ touches.size()-2 ]);
        B.set(touches[ touches.size()-1 ]);
        
        float dist = A.distance( B );
        
        if (dist > MIN_FINGER_DISTANCE ){
            
            //printf(" zoomDiff: %f  d:%f  > zoom: %f\n", zoomDiff, d, zoom);
            if ( zoomDiff > 0 ){
                desiredZoom *= ( dist / zoomDiff ) ;
                desiredZoom = ofClamp( desiredZoom, minZoom, maxZoom );
                float tx = ( A.x + B.x ) * 0.5f ;
                float ty = ( A.y + B.y ) * 0.5f ;
                tx -= ofGetWidth() * 0.5f;
                ty -= ofGetHeight() * 0.5f;
                //printf(" tx: %f   ty: %f  d / zoomDiff: %f \n", tx, ty, d / zoomDiff);
                if (desiredZoom > minZoom && desiredZoom < maxZoom){
                    desiredOffset.x += tx * ( 1.0f - dist / zoomDiff ) / desiredZoom ;
                    desiredOffset.y += ty * ( 1.0f - dist / zoomDiff ) / desiredZoom;
                }
                //printf(" zoom after %f \n", zoom);
            }
            
            applyConstrains();
        }
        
        zoomDiff = dist;
	}
    }
}