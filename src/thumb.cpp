//
//  thumb.cpp
//  tactil
//
//  Created by natxo pedreira on 15/01/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "thumb.h"

thumb::thumb(){
    nombre = "";
    activo = false;
    escala = 1.0;
}

thumb::~thumb(){}
void thumb::ponListeners(){}
void thumb::urdate(){
    update();
    
    mascara.begin();
        ofClear(0);
        if(img.getWidth()>0 && cambioY<.1){
            ofSetColor(0,0,0);
            ofRect(0,0,50,50);
            if(activo){
                ofSetColor(255,255,255,255);
            }else{
                ofSetColor(255,255,255,120);
            }
            ofRectRounded(0, 0, (width-cambioY) * escala, (height-cambioY) * escala, 10);
        }else{
            ofSetColor(255,255,255);
            ofRectRounded(0, 0, (width-cambioY) * escala, (height-cambioY) * escala, 10);
        }
    mascara.end();
}

void thumb::drawThumb(){
    //drawRound();
	ofPushStyle();
    
    ofSetColor(0,0,0,200);
    ofRectRounded(x-((width-cambioY)/2) + width/2 + 3, y-((height-cambioY)/2) + height/2 + 3, (width-cambioY) * escala, (height-cambioY) * escala, 10);
    
	ofSetColor(150,150,150,255);
    ofRectRounded(x-((width-cambioY)/2) + width/2 + 1, y-((height-cambioY)/2) + height/2 + 1, (width-cambioY) * escala - 1, (height-cambioY) * escala - 1, 10);
    
    ofSetColor(255,255,255,255);
	//ofPopStyle();
    if(img.getWidth()>0 && cambioY<.1){
       // img.draw(x, y, 50, 50);
        
        ofPushMatrix();
        ofTranslate(x-((width-cambioY)/2) + width/2, y-((height-cambioY)/2) + height/2);
        
        mascaraShader->begin();
        
        
        glActiveTexture(GL_TEXTURE0_ARB);
        img.getTextureReference().bind();
        
        glActiveTexture(GL_TEXTURE1_ARB);
        mascara.getTextureReference().bind();
        
        //draw a quad the size of the frame
        glBegin(GL_QUADS);
        
        //move the mask around with the mouse by modifying the texture coordinates   
        glMultiTexCoord2d(GL_TEXTURE0_ARB, 0, 0);  
        glMultiTexCoord2d(GL_TEXTURE1_ARB, 0, 0);  
        glVertex2f( 0, 0);  
        
        glMultiTexCoord2d(GL_TEXTURE0_ARB, 50, 0);  
        glMultiTexCoord2d(GL_TEXTURE1_ARB, 50, 0);  
        glVertex2f(50, 0);  
        
        glMultiTexCoord2d(GL_TEXTURE0_ARB, 50, 50);  
        glMultiTexCoord2d(GL_TEXTURE1_ARB, 50, 50);  
        glVertex2f(50,50);  
        
        glMultiTexCoord2d(GL_TEXTURE0_ARB, 0,50);  
        glMultiTexCoord2d(GL_TEXTURE1_ARB, 0,50);  
        glVertex2f( 0, 50);  
        
        glEnd();
        
        //deactive and clean up  
        glActiveTexture(GL_TEXTURE1_ARB);  
        img.getTextureReference().unbind();  
        
        glActiveTexture(GL_TEXTURE0_ARB);  
        mascara.getTextureReference().unbind();  
        
        mascaraShader->end();
        ofPopMatrix();
    }else{
        mascara.draw(x-((width-cambioY)/2) + width/2, y-((height-cambioY)/2) + height/2);
    }
    
    /*
    if (activo) {
        /// si la mini esta pulsada le ponemos un border
        ofPushStyle();
        ofSetColor(255);
        ofNoFill();
        ofSetLineWidth(2);
        roundedRect(x-((width-cambioY)/2) + width/2, y-((height-cambioY)/2) + height/2, (width-cambioY) * escala, (height-cambioY) * escala, 10);
        
        ofPopStyle();
    }*/
}

void thumb::activala(){
    activo = true;
}

void thumb::desactivala(){
    activo = false;
}

void thumb::ponShader(ofShader * _mascaraShader){
    mascaraShader = _mascaraShader;
    
    mascara.allocate(50, 50);
    mascara.begin();
    ofClear(0);
    mascara.end();
    
    mascaraShader->begin();
	mascaraShader->setUniformTexture("Tex0", img.getTextureReference(), 0);
	mascaraShader->setUniformTexture("Tex1", mascara.getTextureReference(), 1);
	mascaraShader->end();

    
}