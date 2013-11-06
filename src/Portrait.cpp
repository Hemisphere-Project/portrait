//
//  Portrait.cpp
//  promenade_mobile_tvs
//
//  Created by Alain Barthelemy on 27/10/13.
//
//

#include "Portrait.h"

Portrait::Portrait(float _x, float _y, float _w, float _h)
{    
	x = _x;
	y = _y;
	w = _w;
    h = _h;
	
    imgIndex = 0;
    
    //loading=false;
    loadingIndex=0;
    FIRST_LOAD=true;
    
	//ofRegisterURLNotification(this);
    
    count = 0;
    
    loadFirst();
}


void Portrait::update(){
	w = ofGetWidth();
    h = ofGetHeight();
    
    imgIndex++;
    if(imgIndex >= IMG_STACK_LENGHT)
        imgIndex = 0;
    
    if(FIRST_LOAD && isStackFull()){
        FIRST_LOAD = false;
        load();
    }
    
    if(!FIRST_LOAD){
        if(tmpImg.bAllocated()){
            img[loadingIndex].clone(tmpImg);
            loadingIndex++;
            if(loadingIndex >= IMG_STACK_LENGHT)
                loadingIndex = 0;
            load();
        }
    }
    

	
}


void Portrait::draw(){
    ofSetColor(255);
    ofRect(x,y,w,h);
    
    cout << "IMG INDEX "<<imgIndex<<"  \n";
    if(!FIRST_LOAD){
        if(img[imgIndex].bAllocated()){
            // draw with image previously resized
            //img[imgIndex].draw(w/2 - img[imgIndex].getWidth()/2, h/2 - img[imgIndex].getHeight()/2);
            
            float imgHeight = IMG_WIDTH*img[imgIndex].getHeight()/img[imgIndex].getWidth();
            img[imgIndex].draw(w/2 - IMG_WIDTH/2, h/2 - imgHeight/2,IMG_WIDTH,imgHeight);
            
        }
    }

    
}

bool Portrait::isStackFull(){
    int k = 0;
    while (img[k].bAllocated() && k < IMG_STACK_LENGHT ) {
        k++;
    }
    if(k>=IMG_STACK_LENGHT)
        return true;
    else
        return false;
    
}



void Portrait::loadFirst(){
    for(int k=0;k<IMG_STACK_LENGHT;k++){
        
        img[loadingIndex].clear();
        int imgNbr = (int)floor(1+ofRandom(1)*44.99);
        loader.loadFromURL(img[loadingIndex], "http://pm.alainbarthelemy.com/portrait/resized/img" + ofToString(imgNbr) + ".jpg");
        cout << "http://pm.alainbarthelemy.com/portrait/resized/img" + ofToString(imgNbr) + ".jpg  \n";
        
        loadingIndex++;
        if(loadingIndex >= IMG_STACK_LENGHT)
            loadingIndex = 0;
    }
    
}

void Portrait::load(){

    tmpImg.clear();
    int imgNbr = (int)floor(1+ofRandom(1)*44.99);
    loader.loadFromURL(tmpImg, "http://pm.alainbarthelemy.com/portrait/resized/img" + ofToString(imgNbr) + ".jpg");
    cout << "http://pm.alainbarthelemy.com/portrait/resized/img" + ofToString(imgNbr) + ".jpg  \n";
    
    
}


void Portrait::exit() {
    loader.stopThread();
}