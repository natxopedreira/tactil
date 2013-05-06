//
//  SimplePanZoom.cpp
//  panZoomDemo
//
//  Created by Patricio Gonzalez Vivo on 4/17/13.
//
//

#include "SimplePanZoom.h"

SimplePanZoom::SimplePanZoom(){
    smoothFactor = 0.55;
	zoom = desiredZoom =  1.0f;
	for (int i = 0; i < MAX_TOUCHES; i++){
		touching[i] = false;
	}
	
	minZoom = 0.1f;
	maxZoom = 10.0f;
	zoomDiff = -1.0f;
    
	offset.x = offset.y = desiredOffset.x = desiredOffset.y = 0.0f;
    
    bDebug = true;
    nosehatocado = true;
}

void SimplePanZoom::update(){
    //if(nosehatocado) centrate();
    
    float time = 1; //deltaTime / 60.0f;
	zoom = (time * smoothFactor) * desiredZoom + (1.0f - smoothFactor * time) * zoom;
	offset = (time * smoothFactor) * desiredOffset + (1.0f - smoothFactor * time) * offset;
    
    applyConstrains();
    
   //
}

void SimplePanZoom::draw( ofBaseHasTexture &_bTex ){
    maxOffset.x = _bTex.getTextureReference().getWidth();
    maxOffset.y = _bTex.getTextureReference().getHeight();
    
    _bTex.getTextureReference().bind();
    
    //    ofMesh  mesh;
    //    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    //    mesh.addTexCoord();
    
    glBegin(GL_QUADS);
    
    glTexCoord2f(-offset.x + 0      * 1.0f/zoom  , -offset.y + 0      * 1.0f/zoom);   glVertex3f(x,y,0);
    glTexCoord2f(-offset.x + width  * 1.0f/zoom  , -offset.y + 0      * 1.0f/zoom);   glVertex3f(x+width,y,0);
    glTexCoord2f(-offset.x + width  * 1.0f/zoom  , -offset.y + height * 1.0f/zoom);   glVertex3f(x+width,y+height,0);
    glTexCoord2f(-offset.x + 0      * 1.0f/zoom  , -offset.y + height * 1.0f/zoom);   glVertex3f(x,y+height,0);
    
    glEnd();
    _bTex.getTextureReference().unbind();
    
    
    if (bDebug){
        ofSetRectMode(OF_RECTMODE_CORNER);
        for (int i = 0; i < MAX_TOUCHES; i++){
            if (touching[i]) glColor4f(0, 1, 0, 1);
            else glColor4f(1, 0, 0, 1);
            float w = 8;
            ofRect( i * (w + 3), 3, w, w);
        }
        
        //	string order = " touchOrder: ";
        //	for (int i = 0; i < touchIDOrder.size(); i++){
        //		order += ofToString( touchIDOrder[i] ) + ", ";
        //	}
        
        char msg[1000];
        sprintf(msg, " zoom: %.1f \n offset: %.1f, %.1f \n ", zoom, offset.x, offset.y);
        glColor4f(1, 1, 1, 1);
        ofDrawBitmapString(msg, 3.0f, 25.0f);
        //ofDrawBitmapString(order, 3.0f, 55.0f);
    }
    
}

void SimplePanZoom::applyConstrains(){
    
    if ( desiredOffset.x > 0 ){
        desiredOffset.x = 0;
    }
    if( desiredOffset.y > 0 ){
        desiredOffset.y = 0;
    }
    
    if ( desiredOffset.x < -(maxOffset.x - width * 1.0/zoom) ){
        desiredOffset.x = -(maxOffset.x - width * 1.0/zoom);
    }
    
    if ( desiredOffset.y < -(maxOffset.y - height * 1.0/zoom) ){
        desiredOffset.y = -(maxOffset.y - height * 1.0/zoom);
    }
    
    if(zoom>maxZoom){
        setZoom(maxZoom);
    }else if (zoom<minZoom) {
        setZoom(minZoom);
    }
    
}

//------------------------------------ Events
void SimplePanZoom::touchDown(ofTouchEventArgs &touch){
    
    if(!inside(touch.x, touch.y)) return;
    
	touchIDOrder.push_back(touch.id);
	
	lastTouch[touch.id].x = touch.x;
	lastTouch[touch.id].y = touch.y;
    
	//printf("####### touchDown %d (zoomdif: %f) %f %f \n", touch.id, zoomDiff , touch.x, touch.y);
    
	if (touchIDOrder.size() >= 2){
		zoomDiff = lastTouch[ touchIDOrder[0] ].distance( lastTouch[ touchIDOrder[1] ] );
	}
    
	touching[touch.id] = true;
    
    nosehatocado = false;
}

void SimplePanZoom::centrate(){
    
    float diffx = 0;
    if(maxOffset.x * zoom>503) diffx = 503 - maxOffset.y * zoom;
    
    float diffy = 0;
    
    if(maxOffset.y * zoom>308) diffy = 308 - maxOffset.y * zoom;
    
    desiredOffset.x = offset.x = diffx;
    desiredOffset.y = offset.x = diffy;
    
}

void SimplePanZoom::touchMoved(ofTouchEventArgs &touch){
	if(!inside(touch.x, touch.y)) touchUp(touch);
    
	ofVec2f p, now;
	float d;
	
	//printf("####### touchMoved %d (%.1f %.1f zoomdif: %f) \n", touch.id, touch.x, touch.y, zoomDiff);
	if (touching[touch.id] == false) return;
    
	if (touchIDOrder.size() == 1){
        
		// 1 finger >> pan
		p = lastTouch[ touchIDOrder[0] ] - ofVec2f(touch.x,touch.y) ;
		desiredOffset = desiredOffset - p * (maxZoom/zoom);
        
		applyConstrains();
        
	}else{
        
		if (touchIDOrder.size() >= 2){
            
			// 2 fingers >> zoom
			d = lastTouch[ touchIDOrder[0] ].distance( lastTouch[ touchIDOrder[1] ] );
			if (d > MIN_FINGER_DISTANCE ){
                
				//printf(" zoomDiff: %f  d:%f  > zoom: %f\n", zoomDiff, d, zoom);
				if ( zoomDiff > 0 ){
					desiredZoom *= ( d / zoomDiff ) ;
					desiredZoom = ofClamp( desiredZoom, minZoom, maxZoom );
					float tx = ( lastTouch[0].x + lastTouch[1].x ) * 0.5f ;
					float ty = ( lastTouch[0].y + lastTouch[1].y ) * 0.5f ;
					tx -= ofGetWidth() * 0.5f;
					ty -= ofGetHeight() * 0.5f;
					//printf(" tx: %f   ty: %f  d / zoomDiff: %f \n", tx, ty, d / zoomDiff);
					if (desiredZoom > minZoom && desiredZoom < maxZoom){
						desiredOffset.x += tx * ( 1.0f - d / zoomDiff ) / desiredZoom ;
						desiredOffset.y += ty * ( 1.0f - d / zoomDiff ) / desiredZoom;
					}
					//printf(" zoom after %f \n", zoom);
				}
                
				applyConstrains();
			}
            
			//pan with 2 fingers too
			if ( touchIDOrder.size() == 2 ){
				p = 0.5 * ( lastTouch[touch.id] - ofVec2f(touch.x,touch.y) ); //0.5 to average both touch offsets
				desiredOffset += - p * (zoom-maxZoom);
			}
            
			zoomDiff = d;
		}
	}
    
	lastTouch[touch.id].x = touch.x;
	lastTouch[touch.id].y = touch.y;
}

void SimplePanZoom::touchUp(ofTouchEventArgs &touch){
	
    
	vector<int>::iterator it = std::find(touchIDOrder.begin(), touchIDOrder.end(), touch.id);
	if ( it == touchIDOrder.end()){
		//not found! wtf!
		//printf("wtf at touchup! can't find touchID %d\n", touch.id);
	}else{
		//printf("####### touchUp %d (zoomdif: %f) \n", touch.id, zoomDiff);
		touching[touch.id] = false;
		lastTouch[touch.id].x = touch.x;
		lastTouch[touch.id].y = touch.y;
        
		if ( touchIDOrder.size() >= 1) {
			zoomDiff = -1.0f;
		}
        
		touchIDOrder.erase(it);
	}
}


void SimplePanZoom::touchDoubleTap(ofTouchEventArgs &touch){
    
}