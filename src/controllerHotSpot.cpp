//
//  controllerHotSpot.cpp
//  tactil
//
//  Created by ignacio pedreira gonzalez on 01/04/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "controllerHotSpot.h"


void  controllerHotSpot::setup(){
    
    cuantos = 35;
    editable = false;
    
    loadPositions();
    
    ofRegisterMouseEvents(this);
    
    idPress = -1;
    
    
    /*
    for (int i = 0; i< cuantos; i++) {
        hotSpot pto;
        
        pto.setup(i+1);
        pto.setPosition(ofPoint(ofRandom(10,1910),ofRandom(10,1070)));
        
        puntos.push_back(pto);
    }*/
}

// ------------------------------
void controllerHotSpot::update(){

}

// ------------------------------
void controllerHotSpot::draw(){
    for (int i = 0; i< cuantos; i++) {
        puntos.at(i).draw();
    }
}

// ------------------------------
void controllerHotSpot::debugOn(){
    if(! editable){
       // ofRegisterMouseEvents(this);
        editable = true;
    }
}


// ------------------------------
void controllerHotSpot::debugOff(){
    if(editable){
        //ofUnregisterMouseEvents(this);
        editable = false;
    }
}

// ------------------------------
void controllerHotSpot::mouseMoved(ofMouseEventArgs & arg){

}

// ------------------------------
void controllerHotSpot::mouseDragged(ofMouseEventArgs & arg){
    
    
    if(idPress >=0 && puntos.size() > idPress){
        if (editable) {
            puntos.at(idPress).setPosition(ofPoint(arg.x, arg.y));
        }
    }
}

// ------------------------------
void controllerHotSpot::mousePressed(ofMouseEventArgs & arg){
    //if(!editable) return;
    
    for (int i = 0; i< cuantos; i++) {
        ofRectangle rect;
        
        rect.set(puntos.at(i).damePos().x, puntos.at(i).damePos().y, 30, 30);
        
        if(rect.inside(arg.x, arg.y)){
            idPress = i;
            
            return;
        }
    }
}

// ------------------------------
void controllerHotSpot::mouseReleased(ofMouseEventArgs & arg){
    if(!editable && (idPress >=0 && puntos.size() > idPress)){
        
        customDataEvent event;
        event.nombre = puntos.at(idPress).urlXml;
        event.valor = idPress+1;
        event.pto.set(arg.x, arg.y);
        
        ofNotifyEvent(verFicha,event);
        
      
    }
    
    if(idPress >=0) idPress = -1;
}



// ------------------------------
void controllerHotSpot::savePositions(){
    ofxXmlSettings posiciones;
    
    posiciones.addTag("puntos");
    posiciones.pushTag("puntos");
    
    for (int i = 0; i< cuantos; i++) {
        
        posiciones.addTag("punto");
        posiciones.pushTag("punto",i);
        
        posiciones.addValue("x", puntos.at(i).damePos().x);
        posiciones.addValue("y", puntos.at(i).damePos().y);
        posiciones.addValue("index", puntos.at(i).dameIndex());
        posiciones.addValue("url", puntos.at(i).urlXml);
        
        posiciones.popTag();//pop position
    }
    
    posiciones.popTag(); //pop position
    posiciones.saveFile("posiciones.xml");
    
    
}


// ------------------------------
void controllerHotSpot::loadPositions(){
ofxXmlSettings settings;
    if(settings.loadFile("posiciones.xml")){
        settings.pushTag("puntos");
        int numberOfSavedPoints = settings.getNumTags("punto");
        
        for(int i = 0; i < numberOfSavedPoints; i++){
            settings.pushTag("punto", i);
            
            hotSpot pto;
            pto.setup(settings.getValue("index", 0));
            pto.setPosition(ofPoint(settings.getValue("x", 0),settings.getValue("y", 0)));
            pto.urlXml = settings.getValue("url", "");
            puntos.push_back(pto);
            
            settings.popTag();
        }
    
        settings.popTag(); //pop position
    }else{
        ofLogError("Position file did not load!");
    }
}