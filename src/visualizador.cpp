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
    
    fuenteInfo.loadFont("SegoeL.ttf", 12 ,90, true);
    fuenteInfo.setLineHeight(18);

    
    offsetDrag.set(0, 0);
    verPie = false;
    verInfo = false;
    
    
    btnInfo.width = 70;
    btnInfo.height = 30;
    btnInfo.x = 0;
    btnInfo.y = 0;
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
    visor.setup(480, 350);
    ofRegisterMouseEvents(this);
}

// ---------------------------------------
void visualizador::update(){

    poswrect = this->width;
    poshrect = this->height;
    posxrect = this->x+10;
    posyrect = this->y+10;
    
    /*
    if(poswrect != (this->width - 20 * this->escala) || poshrect != (this->height-50 * this->escala)){
        this->setWidth(poswrect);
        this->setHeight(poshrect);
    }
    */
    visor.update();
    
    float difX = (this->x + this->width - btnInfo.width)-(btnInfo.x);
    float difY = (this->y + this->height + (btnInfo.height/2) +cantidadCrece)-(btnInfo.y);
    
    btnInfo.x += difX * .4;
    btnInfo.y += difY * .5;
    
}

// ---------------------------------------
void visualizador::drawVisualizador(){
    drawRound(); // la base
    
    
    
    if(verInfo) poshrect += desfaseAltoTextoInfo;
    
    ofRectangle rect = fuente.getStringBoundingBox(titularPie, 0, 0);
    
    
    
    ofPushStyle();
    ofRect(posxrect, posyrect, poswrect-20, poshrect-50);
    
    if(imgVisible) visor.draw(posxrect,posyrect);
    
    ofSetColor(0, 0, 0);
    
    
    if(!verInfo) fuente.drawString(titularPie, this->x + 10, this->y + this->height - 15);
    
    areaPieTitular.set(this->x , this->y + this->height - 15 - 10, rect.width + 20, rect.height + 20);
    
    
    if(verPie && cantidadCrece == altoTexto){
        fuenteCuerpo.drawString(pie, posxrect, posyrect + poshrect + 30);
    }else if (verInfo && cantidadCrece == desfaseAltoTextoInfo){
        
        ofSetColor(0,210);
        ofRect(posxrect, posyrect, poswrect-20, poshrect-50);
        ofSetColor(255);
        
        fuenteInfo.drawString(informacion, posxrect+10, posyrect + 20);
    }
    
    
    btnInfo.color.set(this->color.r,this->color.g,this->color.b);
    btnInfo.drawRound();
    
    
    ofSetColor(0);
    ofDrawBitmapString(btnInfo.nombre, ofPoint(btnInfo.x + 8, btnInfo.y + 20));
    
    ofPopStyle();
    
    if(btnInfo.activo){
        ofPushStyle();
            ofNoFill();
            ofSetColor(0);
            ofSetLineWidth(2);
            btnInfo.roundedRect(btnInfo.x,btnInfo.y,btnInfo.width,btnInfo.height,5);
        ofPopStyle();
    }
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
    pie = wrapString(_pie,480,fuenteCuerpo);
    titularPie = _titularPie;
    cont = x + 200;
    altoTexto = fuenteCuerpo.getStringBoundingBox(pie, 0, 0).height + 50;
    //this->setHeight(this->height + altoTexto);
    //this->cantidadCrece = this->height + altoTexto;
    crece(altoTexto);
    
    informacion = wrapString(_informacion,460,fuenteInfo);
    altoTextoInfo = fuenteInfo.getStringBoundingBox(informacion, 0, 0).height + 20;
    if(altoTextoInfo > (this->height-50 * this->escala)){
        desfaseAltoTextoInfo = altoTextoInfo - (this->height-50 * this->escala);
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
        
        addForce(ofPoint(diff.x+offsetDrag.x,diff.y+offsetDrag.y));
        //moveTo(diff.x+offsetDrag.x,diff.y+offsetDrag.y);

    }
}

// ---------------------------------------
void visualizador::mousePressed(ofMouseEventArgs & args){
    ofRectangle areamasaltura;
    areamasaltura.set(this->x, this->y, this->width, this->height + cantidadCrece);
    if(areamasaltura.inside(args.x, args.y)){
        offsetDrag.set(getCenter().x-args.x,getCenter().y-args.y);
        drag = true;
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

