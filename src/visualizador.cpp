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
    tieneVideo = false;
    verVidrio = false;
    

    fuente.loadFont("SegoeSb.ttf", 13,96, true);
    fuente.setLineHeight(13);
    fuente.setSpaceSize(.8);
    
    fuenteCuerpo.loadFont("SegoeL.ttf", 10,96, true);
    fuenteCuerpo.setLineHeight(13);
    fuenteCuerpo.setSpaceSize(.8);
    
    fuenteInfo.loadFont("SegoeL.ttf", 10 ,96, true);
    fuenteInfo.setLineHeight(17);
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
    
    pos.set(0, 0);
    //pos.set(800, 400);
    
    
    poswrect = 10;
    poshrect = 10;
    
    
    visorZoom.set(0, 0, 503, 308);
	visorZoom.minZoom = 0.f;
    visorZoom.maxZoom = 2.0f;
    visorZoom.deltaTime = 0.016f;
}

// ---------------------------------------
visualizador::~visualizador(){}

// ---------------------------------------
void visualizador::setup(){
    fboImageZoom.allocate(1764, 1080);
    
    fboImageZoom.begin();
    ofClear(255);
    fboImageZoom.end();
    
    
    imagenBtnInfo.loadImage("iconos/iconPICASSO-informacion.png");
    gestos.loadImage("gestos.png");
}

// ---------------------------------------
void visualizador::update(){

    if(verVidrio) videoplayer.update();
    
    float difGrandeX = (pos.x)-(this->x);
    float difGrandeY = (pos.y)-(this->y);
    float difX = (this->x + this->width)-(btnInfo.x);
    float difY = (this->y + this->height)-(btnInfo.y); 
    float difZoomX = (this->x + 12)-(visorZoom.x);
    float difZoomY = (this->y + 12)-(visorZoom.y); 
    
    
    
    this->x += difGrandeX * .7;
    this->y += difGrandeY * .7;  

    
    btnInfo.x += difX * .4;
    btnInfo.y += difY * .5;
    
    
    visorZoom.x += difZoomX;
    visorZoom.y += difZoomY;
    
    
    poswrect = this->width;
    poshrect = this->height;

    
    
    
    visorZoom.update();
     

    
    vel += acc;
    vel *= 0.07;
	pos += vel;
	acc *= 0;
    

}
// ---------------------------------------
void visualizador::drawVisualizadorSombra(){

    ofSetColor(0, 0, 0);
    //ofRect(posxrect, posyrect, poswrect-24, poshrect-24);
    ofRect(pos, poswrect-24, poshrect-24);
    //btnInfo.drawRound();
}


// ---------------------------------------
void visualizador::drawVisualizador(){
    
   // drawRound(); // la base
    ofSetColor(255, 255, 255);
    
    
    if(verInfo) poshrect += desfaseAltoTextoInfo;
    
    ofRectangle rect = fuente.getStringBoundingBox(titularPie, 0, 0);
    
    
    
    if(imgVisible && !verInfo){
        //ofRect(posxrect, posyrect, visor.getAnchoMax(), visor.getAltoMax());
        visorZoom.draw(fboImageZoom);
        
        gestos.draw(this->x + 452 , this->y+323);
    }else if (verVidrio && !verInfo) {
        //if(hayVideo) 
        if(!videoplayer.isLoaded()) ofRect(0,0,200,700);
        visorZoom.draw(videoplayer);
    }
    
    
    if(!verVidrio){
        
    
        ofPushStyle();
        ofSetColor(0, 0, 0);
    
    
        if(verPie){
            fuente.drawString(titularPie, this->x + 12, this->y + 308 + 37);
        }
    
    
        areaPieTitular.set(this->x , this->y + this->height - 15 - 10, rect.width + 24, rect.height + 24);
    
    
        if(verPie && cantidadCrece == altoTexto){
            fuenteInfo.drawString(pie, this->x+12, this->y + 308 + 56);
        }else if (verInfo && cantidadCrece == desfaseAltoTextoInfo){
        
            ofSetColor(0);
            fuenteCuerpo.drawString(informacion, this->x+15, this->y + 40);
        }
        ofPopStyle();
    
    }
    
    btnInfo.drawButtonImg(imagenBtnInfo);
    
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
void visualizador::cargaVideo(string _url){
    if (imagenZoom.isAllocated()){
        imagenZoom.clear();
    }
    imgVisible = false;
    videoplayer.loadMovie(_url);
    videoplayer.play();
    
    if(videoplayer.isLoaded()){
       
    }
     verVidrio = true;
    visorZoom.minZoom = 1;
    visorZoom.setZoom(1);
}



//------------------------------------------------------------
void visualizador::botaParedes(){
    // sometimes it makes sense to damped, when we hit
	bool bDampedOnCollision = true;
	bool bDidICollide = false;
    
	// what are the walls
	float minx = 0;
	float miny = 0;
	float maxx = ofGetWidth()-520;
	float maxy = ofGetHeight()-400;
    
	if (x > maxx){
		x = maxx; // move to the edge, (important!)
		vel.x *= -1;
		bDidICollide = true;
	} else if (x < minx){
		x = minx; // move to the edge, (important!)
		vel.x *= -1;
		bDidICollide = true;
	}
    
	if (y > maxy){
		y = maxy; // move to the edge, (important!)
		vel.y *= -1;
		bDidICollide = true;
	} else if (y < miny){
		y = miny; // move to the edge, (important!)
		vel.y *= -1;
		bDidICollide = true;
	}
    
	if (bDidICollide == true && bDampedOnCollision == true){
		vel *= 0.3;
	}
}

// ---------------------------------------
void visualizador::cargaImagen(string _url){
    //visor.cargaImagen("imagenes/full/"+_url);
   /* if(verVidrio){
        
        
    }verVidrio=!verVidrio;
    
    cout << "verVidrio " << verVidrio<< endl;
    cout << "isPlaying "  << videoplayer.isPlaying() << endl;
    */
    //visorZoom.nosehatocado = true;
    if (imagenZoom.isAllocated()){
         imagenZoom.clear();
    }
    imgVisible = false;
    imagenZoom.loadImage("imagenes/full/"+_url);
   
    if (imagenZoom.isAllocated()) {
        visorZoom.smoothFactor = .9;
        if(imagenZoom.getHeight()<1100){
        
        int altoNuevoRatio = 0;
        int anchoNuevoRatio = 0;

        if(imagenZoom.getWidth() > imagenZoom.getHeight()){
            /// formato horizontal
            /// aplicamos el ratio
            altoNuevoRatio = imagenZoom.getWidth() * 0.61232604373757;
            anchoNuevoRatio = imagenZoom.getWidth();
        
        }else {
            /// formato vertical
            /// aplicamos el ratio
            anchoNuevoRatio = imagenZoom.getHeight() * 1.63311688312;
            altoNuevoRatio = imagenZoom.getHeight();
        }
        
        /// comprobamos si tenemos que reallocate el fbo
        /*if(anchoNuevoRatio > fboImageZoom.getWidth() || altoNuevoRatio > fboImageZoom.getHeight()){
            
            fboImageZoom.allocate(anchoNuevoRatio, altoNuevoRatio);
            fboImageZoom.begin();
            ofClear(255);
            fboImageZoom.end();
        
        }*/
            if(anchoNuevoRatio>1764){
                fboImageZoom.allocate(anchoNuevoRatio, altoNuevoRatio);
            }else{
                fboImageZoom.allocate(1764, 1080);
            }
            
            
            fboImageZoom.begin();
            ofClear(255);
            fboImageZoom.end();
            
        
        float desfaseX = (fboImageZoom.getWidth()-imagenZoom.getWidth())/2;
        float desfaseY = (fboImageZoom.getHeight()-imagenZoom.getHeight())/2;
        
        
        ///pintamos el fbo
        fboImageZoom.begin();
        ofClear(255);
        ofSetColor(255);
        ofRect(0, 0, fboImageZoom.getWidth(), fboImageZoom.getHeight());
        imagenZoom.draw(desfaseX, desfaseY);
        fboImageZoom.end();
        
        
        // creo un valor
        float ratio = 0;
        
        if(fboImageZoom.getWidth()<fboImageZoom.getHeight()){
            ratio = 503.0/ fboImageZoom.getWidth();
        }else {
            ratio = 308.0 / fboImageZoom.getHeight();
        }
        
        visorZoom.minZoom = ratio;
        visorZoom.setZoom(ratio);
        
        
        //cout << " ------------------------------------------ " << endl;
        //cout << anchoNuevoRatio << " < " << altoNuevoRatio << endl;
        //cout << fboImageZoom.getWidth() << " --- fbo --- " << fboImageZoom.getHeight() << endl;
        
        
        imgVisible = true;
            
            
        }else{
            int anchoImagenZoom = imagenZoom.getWidth();
            int altoImagenZoom = imagenZoom.getHeight();
            
            //// eres un periodico
            fboImageZoom.allocate(anchoImagenZoom, altoImagenZoom);
            fboImageZoom.begin();
            ofClear(255);
            fboImageZoom.end();
            
            
            // creo un valor
            float ratio = 0;
            
            if(anchoImagenZoom<altoImagenZoom){
                ratio = 503.0/ anchoImagenZoom;
            }else {
                ratio = 308.0 / altoImagenZoom;
            }
            
            
            
           // ratio = static_cast<float>(static_cast<int>(ceil(ratio * 10.))) / 10.;
            
            visorZoom.minZoom = ratio;
            visorZoom.setZoom(ratio);
            
            imgVisible = true;
            

            
            fboImageZoom.begin();
            ofSetColor(255);
            imagenZoom.draw(0, 0);
            
            fboImageZoom.end();
            
        }
        
        
    }else{
        
        //imgVisible = false;
    }
    
    
}

// ---------------------------------------
void visualizador::ponTexto(string _titularPie,string _pie, string _informacion){
    pie = wrapString(_pie,490,fuenteCuerpo);
    titularPie = _titularPie;
    cont = x + 200;
    altoTexto = fuenteCuerpo.getStringBoundingBox(pie, 0, 0).height +10;

    
    
    crece(altoTexto);
    
    //informacion = wrapString(_informacion,460,fuenteInfo);
    informacion = wrapString(_informacion,490,fuenteCuerpo);
    //altoTextoInfo = fuenteInfo.getStringBoundingBox(informacion, 0, 0).height;
    altoTextoInfo = fuenteCuerpo.getStringBoundingBox(informacion, 0, 0).height;
    
    if(altoTextoInfo > (this->height * this->escala)){
        desfaseAltoTextoInfo = altoTextoInfo - (this->height * this->escala) + 40;
    }
    
    verPie = true;
    verInfo = false;
    btnInfo.activo = verInfo;
}










#ifdef USE_TUIO
/// tuio

void visualizador::tuioAdded(ofxTuioCursor & tuioCursor){
    ofVec2f loc = ofVec2f(tuioCursor.getX() * ofGetWidth(),tuioCursor.getY() * ofGetHeight());
    
    
    //visorZoom.tuioAdded(tuioCursor);
    //cout << "pto agregado en " << loc.x << "," << loc.y << "esta inside " << inside(loc) << "hay " << cursorsOnBorder.size() << " toques" <<  endl;
    //
    
    
    if((imgVisible || verVidrio) && !verInfo){
        if (inside(loc) && !visorZoom.inside(loc)){
            tCursor c;
            c.idN = tuioCursor.getSessionId();
            c.loc = loc;
        
            // First finger over the photo (first trigger)
            //
            if (cursorsOnBorder.size() == 0){   
                cursorsOnBorder.push_back(c);
                oldLoc[0] = loc;
            } 
            // Second finger over the photo (second and finall trigger)
            //
            else if (cursorsOnBorder.size() == 1){
                cursorsOnBorder.push_back(c);
                oldLoc[0] = cursorsOnBorder[0].loc;
                oldLoc[1] = cursorsOnBorder[1].loc;
            }
        }
    }else {
        if (inside(loc)){
            tCursor c;
            c.idN = tuioCursor.getSessionId();
            c.loc = loc;
            
            // First finger over the photo (first trigger)
            //
            if (cursorsOnBorder.size() == 0){   
                cursorsOnBorder.push_back(c);
                oldLoc[0] = loc;
            } 
            // Second finger over the photo (second and finall trigger)
            //
            else if (cursorsOnBorder.size() == 1){
                cursorsOnBorder.push_back(c);
                oldLoc[0] = cursorsOnBorder[0].loc;
                oldLoc[1] = cursorsOnBorder[1].loc;
            }
        }
    }
}
void visualizador::tuioRemoved(ofxTuioCursor & tuioCursor){
    
    ofVec2f loc = ofVec2f(tuioCursor.getX() * ofGetWidth(), tuioCursor.getY() * ofGetHeight());
    
    
    //visorZoom.tuioRemoved(tuioCursor);
    
    for (int i = 0; i < cursorsOnBorder.size(); i++ ){
        if (cursorsOnBorder[i].idN == tuioCursor.getSessionId()){
            cursorsOnBorder.erase(cursorsOnBorder.begin()+i);
        }
    }
}

void visualizador::tuioUpdated(ofxTuioCursor & tuioCursor){
    ofVec2f loc = ofVec2f( tuioCursor.getX() * ofGetWidth(), tuioCursor.getY() * ofGetHeight() );
    
    //visorZoom.tuioUpdated(tuioCursor);
    
    if ( inside(loc) ){
        
        // Store the position of the fingers over the photo
        //
        for ( int i = 0; i < cursorsOnBorder.size(); i++)
            if (cursorsOnBorder[i].idN == tuioCursor.getSessionId())
                cursorsOnBorder[i].loc = loc;

            if (cursorsOnBorder.size() == 1 ){
                ofVec2f oldStaCursorToCenter = pos - oldLoc[0];
                pos = loc + oldStaCursorToCenter;
                oldLoc[0] = loc;
                
            } 
    }
}

#else
void visualizador::mouseDragged(ofMouseEventArgs & arg){
    ofVec2f loc = ofVec2f( arg.x,arg.y);
    
    //visorZoom.tuioUpdated(tuioCursor);
    
    if ( inside(loc) ){
        
        // Store the position of the fingers over the photo
        //
        for ( int i = 0; i < cursorsOnBorder.size(); i++)
            if (cursorsOnBorder[i].idN == arg.button)
                cursorsOnBorder[i].loc = loc;
        
        if (cursorsOnBorder.size() == 1 ){
            ofVec2f oldStaCursorToCenter = pos - oldLoc[0];
            pos = loc + oldStaCursorToCenter;
            oldLoc[0] = loc;
            
        } 
    }
}
void visualizador::mousePressed(ofMouseEventArgs & arg){
    ofVec2f loc = ofVec2f(arg.x,arg.y);
    
    
    //visorZoom.tuioAdded(tuioCursor);
    //cout << "pto agregado en " << loc.x << "," << loc.y << "esta inside " << inside(loc) << "hay " << cursorsOnBorder.size() << " toques" <<  endl;
    //
    
    
    if(imgVisible && !verInfo){
        if (inside(loc) && !visorZoom.inside(loc)){
            tCursor c;
            c.idN = arg.button;
            c.loc = loc;
            
            // First finger over the photo (first trigger)
            //
            if (cursorsOnBorder.size() == 0){   
                cursorsOnBorder.push_back(c);
                oldLoc[0] = loc;
            } 
            // Second finger over the photo (second and finall trigger)
            //
            else if (cursorsOnBorder.size() == 1){
                cursorsOnBorder.push_back(c);
                oldLoc[0] = cursorsOnBorder[0].loc;
                oldLoc[1] = cursorsOnBorder[1].loc;
            }
        }
    }else {
        if (inside(loc)){
            tCursor c;
            c.idN = arg.button;
            c.loc = loc;
            
            // First finger over the photo (first trigger)
            //
            if (cursorsOnBorder.size() == 0){   
                cursorsOnBorder.push_back(c);
                oldLoc[0] = loc;
            } 
            // Second finger over the photo (second and finall trigger)
            //
            else if (cursorsOnBorder.size() == 1){
                cursorsOnBorder.push_back(c);
                oldLoc[0] = cursorsOnBorder[0].loc;
                oldLoc[1] = cursorsOnBorder[1].loc;
            }
        }
    }
}
void visualizador::mouseReleased(ofMouseEventArgs & arg){
    ofVec2f loc = ofVec2f(arg.x,arg.y);
    
    
    //visorZoom.tuioRemoved(tuioCursor);
    
    for (int i = 0; i < cursorsOnBorder.size(); i++ ){
        if (cursorsOnBorder[i].idN == arg.button){
            cursorsOnBorder.erase(cursorsOnBorder.begin()+i);
        }
    }

}
#endif