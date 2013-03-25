//
//  mar.cpp
//  tactil
//
//  Created by ignacio pedreira gonzalez on 25/03/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "mar.h"


void mar::setup(){
    ofDisableArbTex();
    fondo.loadImage("LA-HUELLA-PICASSO.jpg");
    
    ofEnableArbTex();

    
    shaderFondo.load("shaders/sine.vert", "shaders/sine.frag");
    waveDirection = 0;
    waveFrequency = 1;

    cam.disableMouseInput();
	cam.setDistance(850);
    cam.setScale(1,-1,1);
    
    creaGrid();
}


void mar::update(){}

void mar::draw(){
    ofPushStyle();
    ofPushMatrix();
       
    ofSetColor(255);
    
    cam.begin();
    ofTranslate(1900/2 * -1, 1080/2 * -1);
    
    shaderFondo.begin();
    shaderFondo.setUniformTexture("text", fondo.getTextureReference(), 0);
    shaderFondo.setUniform1f("time", ofGetElapsedTimef() );
    shaderFondo.setUniform1i("waveDirection", waveDirection );
    shaderFondo.setUniform1i("waveFrequency", waveFrequency );
    
    mesh.draw();
    
    shaderFondo.end();
    
    cam.end();
    
    ofPopMatrix();
    ofPopStyle();
}

void mar::creaGrid(){
    int spacing = 25;
    int ancho = 1920/spacing;
    int alto = 1080/spacing;
    
    
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    for (int y = 0; y < alto ; y++) {
        for (int x = 0 ; x < ancho ; x++) {
            
            ofVec3f v = ofVec3f(x * spacing, y * spacing, 0);
            ofPoint pto = fondo.getTextureReference().getCoordFromPoint(x * spacing, y * spacing);
            
            mesh.addTexCoord(ofVec2f(pto.x,pto.y));
            mesh.addVertex(v);
        }
    }
    
    for (int y = 0; y < alto-1; y ++) {
        for (int x = 0 ; x < ancho-1; x ++) {
            
            mesh.addIndex(x+y*ancho);				// 0
			mesh.addIndex((x+1)+y*ancho);			// 1
			mesh.addIndex(x+(y+1)*ancho);			// 10
			
			mesh.addIndex((x+1)+y*ancho);			// 1
			mesh.addIndex((x+1)+(y+1)*ancho);		// 11
			mesh.addIndex(x+(y+1)*ancho);			// 10
            
            
        }
    }

}