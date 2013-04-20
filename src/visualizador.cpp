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
    fuente.setLineHeight(13);
    fuente.setSpaceSize(.8);
    
    fuenteCuerpo.loadFont("SegoeL.ttf", 10,96, true);
    fuenteCuerpo.setLineHeight(13);
    fuenteCuerpo.setSpaceSize(.8);
    
    fuenteInfo.loadFont("SegoeL.ttf", 10 ,96, true);
    fuenteInfo.setLineHeight(8);
    fuenteInfo.setSpaceSize(.8);
    
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
    ofRegisterMouseEvents(this);
    
    visorZoom.set(this->x+12,this->y+12,503,308);
	visorZoom.minZoom = 0.f;
    visorZoom.deltaTime = 0.016f;
}

// ---------------------------------------
void visualizador::update(){
    
    
    poswrect = this->width;
    poshrect = this->height;
    posxrect = this->x+12;
    posyrect = this->y+12;
    
    visorZoom.setPosition(posxrect, posyrect);
    
    float difX = (this->x + this->width)-(btnInfo.x);
    float difY = (this->y + this->height)-(btnInfo.y);
    
    btnInfo.x += difX * .4;
    btnInfo.y += difY * .5;
    
    visorZoom.update();
    
}
// ---------------------------------------
void visualizador::drawVisualizadorSombra(){

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
    
    
    
    if(imgVisible && !verInfo){
        //ofRect(posxrect, posyrect, visor.getAnchoMax(), visor.getAltoMax());
        visorZoom.draw(imagenZoom);
    }
    
    
    ofSetColor(0, 0, 0);
    
    
    if(verPie){
        fuente.drawString(titularPie, this->x + 12, this->y + 308 + 37);
    }
    
    
    areaPieTitular.set(this->x , this->y + this->height - 15 - 10, rect.width + 24, rect.height + 24);
    
    
    if(verPie && cantidadCrece == altoTexto){
       fuenteInfo.drawString(pie, posxrect, this->y + 308 + 56);
    }else if (verInfo && cantidadCrece == desfaseAltoTextoInfo){
        
        ofSetColor(0);
        fuenteCuerpo.drawString(informacion, posxrect+10, posyrect + 24);
    }
    
    
    
    btnInfo.drawRound();
    
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
    //visor.cargaImagen("imagenes/full/"+_url);
    if (imagenZoom.isAllocated()){
         imagenZoom.clear();
    }
    imgVisible = false;
    imagenZoom.loadImage("imagenes/full/"+_url);
   
    if (imagenZoom.isAllocated()) {
        
        /// cojo el ancho y alto
        int ancho = imagenZoom.getWidth();
        int alto = imagenZoom.getHeight();
        
        // creo un valor
        float ratio = 0;
        
        if(alto<ancho){
            ratio = alto/308;
        }else {
            ratio = ancho/503;
        }
        

        visorZoom.maxZoom = ratio;
        visorZoom.setZoom(ratio);
        
        imgVisible = true;
    }else{
        
        imgVisible = false;
    }
    
    
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
    if(visorZoom.inside(args.x, args.y)){
        
        ofTouchEventArgs touch;
        touch.x = args.x;
        touch.y = args.y;
        touch.id = args.button;
        visorZoom.touchMoved(touch); //fw event to cam
        
        return;
    }
    
    
    if(drag){

        ofPoint p = getCenter();
        ofPoint diff	= ofPoint(args.x, args.y) - p;

        //addForce(ofPoint(diff.x+offsetDrag.x,diff.y+offsetDrag.y).normalize()*1.5);
        moveTo(diff.x+offsetDrag.x,diff.y+offsetDrag.y);
    }
}

// ---------------------------------------
void visualizador::mousePressed(ofMouseEventArgs & args){

    if(visorZoom.inside(args.x, args.y)){
    
        ofTouchEventArgs touch;
        touch.x = args.x;
        touch.y = args.y;
        touch.id = args.button;
        visorZoom.touchDown(touch); //fw event to cam
        
        return;
    }
    
    if(this->inside(args.x, args.y)){
        
        offsetDrag.set(getCenter().x-args.x,getCenter().y-args.y);
        drag = true;
        
        
        

        
    }else{
        drag = false;
    }
}

// ---------------------------------------
void visualizador::mouseReleased(ofMouseEventArgs & args){
    if(visorZoom.inside(args.x, args.y)){
        
        ofTouchEventArgs touch;
        touch.x = args.x;
        touch.y = args.y;
        touch.id = args.button;
        visorZoom.touchUp(touch); //fw event to cam
        
        return;
    }
    
    
    
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

