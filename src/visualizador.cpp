/*
 *  visualizador.cpp
 *  tactil
 *
 *  Created by ignacio garcia on 08/01/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "visualizador.h"

visualizador::visualizador(){
    imgVisible = false;

    fuente.loadFont("SegoeSb.ttf", 13,96, true);
    fuente.setSpaceSize(.8);
    
    fuenteCuerpo.loadFont("SegoeL.ttf", 10,96, true);
    fuenteCuerpo.setLineHeight(15);
    fuenteCuerpo.setSpaceSize(.8);
    
    //fuenteInfo.loadFont("SegoeL.ttf", 11 ,96, true);
    //fuenteInfo.setLineHeight(15);
    //fuenteInfo.setSpaceSize(.8);
    
    offsetDrag.set(0, 0);
    verPie = false;
    verInfo = false;
    
    
    btnInfo.width = 50;
    btnInfo.height = 50;
    btnInfo.x = 0;
    btnInfo.y = 0;
    btnInfo.color.set(255, 143, 95);
    btnInfo.nombre = "+ info";
    
    desfaseAltoTextoInfo = 0;
    
    posxrect = 0;
    posyrect = 0;
    poswrect = 10;
    poshrect = 10;
}

// ---------------------------------------
visualizador::~visualizador(){
   ofUnregisterMouseEvents(this);
}

// ---------------------------------------
void visualizador::setup(){
    visor.setup(503, 308);
    ofRegisterMouseEvents(this);
}

// ---------------------------------------
void visualizador::update(){

    poswrect = this->width;
    poshrect = this->height;
    posxrect = this->x+12;
    posyrect = this->y+12;
    
   
    
    float difX = (this->x + this->width)-(btnInfo.x);
    float difY = (this->y + this->height)-(btnInfo.y);
    
    btnInfo.x += difX * .4;
    btnInfo.y += difY * .5;
    
    visor.update();
    
    
}
// ---------------------------------------
void visualizador::drawVisualizadorSombra(){
    // drawRound(); // la base
//    ofSetColor(255, 255, 255);
    ofSetColor(0, 0, 0);
    
   ofRect(posxrect, posyrect, poswrect-24, poshrect-24);
    
    
    
    

    
    btnInfo.drawRound();
}


// ---------------------------------------
void visualizador::drawVisualizador(){
   // drawRound(); // la base
    ofSetColor(255, 255, 255);
    
    
    if(verInfo) poshrect += desfaseAltoTextoInfo;
    
    ofRectangle rect = fuente.getStringBoundingBox(titularPie, 0, 0);
    
    
    
   // ofPushStyle();
    
    
    if(imgVisible && !verInfo){
        ofRect(posxrect, posyrect, visor.getAnchoMax(), visor.getAltoMax());

        
        visor.draw(posxrect,posyrect);
        
    }else{
        //ofRect(posxrect, posyrect, poswrect-24, poshrect-24);
    }
    
    
    ofSetColor(0, 0, 0);
    
    
    if(!verInfo) fuente.drawString(titularPie, this->x + 12, this->y + visor.getAltoMax() + 37);
    
    
    
    areaPieTitular.set(this->x , this->y + this->height - 15 - 10, rect.width + 24, rect.height + 24);
    
    
    if(verPie && cantidadCrece == altoTexto){
        fuenteCuerpo.drawString(pie, posxrect, this->y + visor.getAltoMax() + 56);
    }else if (verInfo && cantidadCrece == desfaseAltoTextoInfo){
        
        //ofSetColor(0,210);
        //ofRect(posxrect, posyrect, poswrect-24, poshrect-50);
        ofSetColor(0);
        fuenteCuerpo.drawString(informacion, posxrect+10, posyrect + 24);
       // fuenteInfo.drawString(informacion, posxrect+10, posyrect + 24);
    }
    
    
    
    btnInfo.drawRound();
    
    
    //ofSetColor(0);
    //ofDrawBitmapString(btnInfo.nombre, ofPoint(btnInfo.x + 8, btnInfo.y + 20));
    
 //   ofPopStyle();
    /*
    if(btnInfo.activo){
        ofPushStyle();
            ofNoFill();
            ofSetColor(0);
            ofSetLineWidth(2);
            btnInfo.roundedRect(btnInfo.x,btnInfo.y,btnInfo.width,btnInfo.height,5);
        ofPopStyle();
    }*/
}
// ---------------------------------------
string visualizador::wrapString(string text, int width, ofTrueTypeFont & _ft) {  
    
    string typeWrapped = "";  
    string tempString = "";  
    vector <string> words = ofSplitString(text, " ");  
    
    for(int i=0; i<words.size(); i++) {  
        
        string wrd = words[i];  
        
        // if we aren't on the first word, add a space  
        if (i > 0) {  
            tempString += " ";  
        }  
        tempString += wrd;  
        int stringwidth = _ft.stringWidth(tempString);
       // int stringwidth = fuenteCuerpo.stringWidth(tempString);  
        
        if(stringwidth >= width) {  
            typeWrapped += "\n";  
            tempString = wrd;       // make sure we're including the extra word on the next line  
        } else if (i > 0) {  
            // if we aren't on the first word, add a space  
            typeWrapped += " ";  
        }  
        
        typeWrapped += wrd;  
    }  
    
    return typeWrapped;  
    
} 

// ---------------------------------------
void visualizador::cargaImagen(string _url){
    visor.cargaImagen("imagenes/full/"+_url);
    imgVisible = true;
}

// ---------------------------------------
void visualizador::ponTexto(string _titularPie,string _pie, string _informacion){
    pie = wrapString(_pie,470,fuenteCuerpo);
    titularPie = _titularPie;
    cont = x + 200;
    altoTexto = fuenteCuerpo.getStringBoundingBox(pie, 0, 0).height - 24;

    crece(altoTexto);
    
    //informacion = wrapString(_informacion,460,fuenteInfo);
    informacion = wrapString(_informacion,460,fuenteCuerpo);
    //altoTextoInfo = fuenteInfo.getStringBoundingBox(informacion, 0, 0).height;
    altoTextoInfo = fuenteCuerpo.getStringBoundingBox(informacion, 0, 0).height;
    
    if(altoTextoInfo > (this->height * this->escala)){
        desfaseAltoTextoInfo = altoTextoInfo - (this->height * this->escala) + 40;
    }
    
    verPie = true;
    verInfo = false;
    btnInfo.activo = verInfo;
}

// ---------------------------------------
void visualizador::mouseDragged(ofMouseEventArgs & args){
        /// estas drageando un boton o el visualizador
    if(drag){

        ofPoint p = getCenter();
        ofPoint diff	= ofPoint(args.x, args.y) - p;

        //addForce(ofPoint(diff.x+offsetDrag.x,diff.y+offsetDrag.y).normalize()*1.5);
        moveTo(diff.x+offsetDrag.x,diff.y+offsetDrag.y);

    }
}

// ---------------------------------------
void visualizador::mousePressed(ofMouseEventArgs & args){

    if(this->inside(args.x, args.y)){
        offsetDrag.set(getCenter().x-args.x,getCenter().y-args.y);
        drag = true;
    }else{
        drag = false;
    }
}

// ---------------------------------------
void visualizador::mouseReleased(ofMouseEventArgs & args){
    if(drag){
        drag = false;
        offsetDrag.set(0, 0);
    }
    if(btnInfo.inside(ofPoint(args.x,args.y)) && !verInfo){
        //cout << "mira texto" << endl;
        
        verInfo = !verInfo;
        btnInfo.activo = verInfo;
        if(!verInfo){
            verPie = true;
            crece(altoTexto);         
        }else{
            verPie = false;
            crece(desfaseAltoTextoInfo);
        }
        
    }
}

// ---------------------------------------
void visualizador::mouseMoved(ofMouseEventArgs & args){}

