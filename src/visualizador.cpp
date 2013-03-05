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

    fuente.loadFont("SegoeSbI.ttf", 13,90, true);
    fuenteCuerpo.loadFont("SegoeL.ttf", 10.5,90, true);
    fuenteCuerpo.setLineHeight(18);
    offsetDrag.set(0, 0);
    verPie = false;
}

void visualizador::ponListeners(){
    ofRegisterMouseEvents(this);
}
visualizador::~visualizador(){
    ofUnregisterMouseEvents(this);
}
string visualizador::wrapString(string text, int width) {  
    
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
        
        int stringwidth = fuenteCuerpo.stringWidth(tempString);  
        
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
void visualizador::drawVisualizador(){
    drawRound(); // la base

    int posxrect = this->x + 10;
    int posyrect = this->y + 10;
    int poswrect = this->width - 20 * this->escala;
    int poshrect = this->height-50 * this->escala;
    ofRectangle rect = fuente.getStringBoundingBox(titularPie, 0, 0);
    //ofRectangle rectPie = fuenteCuerpo.getStringBoundingBox(pie, 0, 0);
    
    
    ofPushStyle();
    ofRect(posxrect, posyrect, poswrect, poshrect);
    
    if(imgVisible) imagen.draw(posxrect,posyrect);
    
    ofSetColor(0, 0, 0);
    
    
    fuente.drawString(titularPie, this->x + 10, this->y + this->height - 15);
    
    areaPieTitular.set(this->x , this->y + this->height - 15 - 10, rect.width + 20, rect.height + 20);
    
    
    if(verPie && cantidadCrece == altoTexto){
        fuenteCuerpo.drawString(pie, posxrect, posyrect + poshrect + 60);
    }
    

    
    ofPopStyle();
}

void visualizador::cargaImagen(string _url){
    imagen.loadImage("grande/" + _url);
    imgVisible = true;
}

void visualizador::ponTexto(string _titularPie,string _pie){
    pie = wrapString(_pie,480);
    titularPie = _titularPie;
    cont =x + 200;
    altoTexto = fuenteCuerpo.getStringBoundingBox(pie, 0, 0).height + 20;
    crece(altoTexto);
    verPie = true;
}

void visualizador::mouseDragged(ofMouseEventArgs & args){
        /// estas drageando un boton o el visualizador
    if(drag){
        ofPoint p = getCenter();
        ofPoint diff	= ofPoint(args.x, args.y) - p;
        ofPoint destino = ofPoint(args.x, args.y) - diff/2;
        moveTo(diff.x+offsetDrag.x,diff.y+offsetDrag.y);
    }
}

void visualizador::mousePressed(ofMouseEventArgs & args){
    ofRectangle areamasaltura;
    areamasaltura.set(this->x, this->y, this->width, this->height + cantidadCrece);
    if(areamasaltura.inside(args.x, args.y)){
        offsetDrag.set(getCenter().x-args.x,getCenter().y-args.y);
        drag = true;
    }
}

void visualizador::mouseReleased(ofMouseEventArgs & args){
 /*   if(areaPieTitular.inside(args.x, args.y)){
        verPie = !verPie;
        if(verPie){
            crece(altoTexto,.6);
        }else{
            crece(0,.3);
        }
    }*/
    if(drag){
        drag = false;
        offsetDrag.set(0, 0);
    }
}

void visualizador::mouseMoved(ofMouseEventArgs & args){}