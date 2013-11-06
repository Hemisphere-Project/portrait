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
    
   // if(FIRST_LOAD && imgIndex >= loadingIndex)
   //     imgIndex = 0;
    
    // after the FIRST_LOAD (means that the img array has been filled up
    // we load a new image every MAX_COUNT update call
    if(!FIRST_LOAD){
        //count++;
        //if(count >=MAX_COUNT){
        //    count = 0;
        //    load();
        //}
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

	if(img[imgIndex].bAllocated()){
        // draw with image previously resized
        //img[imgIndex].draw(w/2 - img[imgIndex].getWidth()/2, h/2 - img[imgIndex].getHeight()/2);
        
        float imgHeight = IMG_WIDTH*img[imgIndex].getHeight()/img[imgIndex].getWidth();
        img[imgIndex].draw(w/2 - IMG_WIDTH/2, h/2 - imgHeight/2,IMG_WIDTH,imgHeight);
        
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


/*
void Portrait::urlResponse(ofHttpResponse & response){
    
	if(response.status==200 && response.request.name == "imgPortrait"){
		img[loadingIndex].loadImage(response.data);
        img[loadingIndex].resize(IMG_WIDTH, (int)floor(img[loadingIndex].getHeight()*IMG_WIDTH/img[loadingIndex].getWidth()));
        
        loadingIndex++;
        
        if(FIRST_LOAD && loadingIndex < PORTRAIT_IMG_STACK_LENGHT){ // in the beginning we load twice
            load();
        }else
            FIRST_LOAD = false;
        
        if(loadingIndex >= PORTRAIT_IMG_STACK_LENGHT)
            loadingIndex = 0;
        
	}else {
		//cout << response.status << " " << response.error << endl;
	}
}
*/

void Portrait::loadFirst(){
    for(int k=0;k<IMG_STACK_LENGHT;k++){
        
        img[loadingIndex].clear();
        int imgNbr = (int)floor(1+ofRandom(1)*44.99);
        loader.loadFromURL(img[loadingIndex], "http://pm.alainbarthelemy.com/portrait/resized/img" + ofToString(imgNbr) + ".jpg");
        
        loadingIndex++;
        if(loadingIndex >= IMG_STACK_LENGHT)
            loadingIndex = 0;
    }
    
}

void Portrait::load(){
    
    
    
   /* int imgNbr = (int)floor(1+ofRandom(1)*44.99);
    ostringstream ss;
    ss << imgNbr;
    string imgName = "img"+ss.str();
    string imgUrl = "http://pm.alainbarthelemy.com/portrait/"+imgName+".jpg";
    cout << "img" << imgUrl << '\n';
    ofLoadURLAsync(imgUrl,"imgPortrait");*/
    

    
    tmpImg.clear();
    int imgNbr = (int)floor(1+ofRandom(1)*44.99);
    loader.loadFromURL(tmpImg, "http://pm.alainbarthelemy.com/portrait/resized/img" + ofToString(imgNbr) + ".jpg");
    

    
    /*img[loadingIndex].clear();
    int imgNbr = (int)floor(1+ofRandom(1)*44.99);
    loader.loadFromURL(img[loadingIndex], "http://pm.alainbarthelemy.com/portrait/img" + ofToString(imgNbr) + ".jpg");
    
    loadingIndex++;
    if(loadingIndex >= IMG_STACK_LENGHT)
        loadingIndex = 0;*/
    
    
    
    /*if(FIRST_LOAD){ // in the beginning we load twice
        for(int k=0;k<IMG_STACK_LENGHT;k++){
           
            img[loadingIndex].clear();
            int imgNbr = (int)floor(1+ofRandom(1)*44.99);
            loader.loadFromURL(img[loadingIndex], "http://pm.alainbarthelemy.com/portrait/img" + ofToString(imgNbr) + ".jpg");
            
            loadingIndex++;
            if(loadingIndex >= IMG_STACK_LENGHT)
                loadingIndex = 0;
        }
        //FIRST_LOAD = false;
    }else{
        img[loadingIndex].clear();
        int imgNbr = (int)floor(1+ofRandom(1)*44.99);
        loader.loadFromURL(img[loadingIndex], "http://pm.alainbarthelemy.com/portrait/img" + ofToString(imgNbr) + ".jpg");
        
        loadingIndex++;
        if(loadingIndex >= IMG_STACK_LENGHT)
            loadingIndex = 0;
    }*/
    
    

    
    
}


void Portrait::exit() {
	//ofUnregisterURLNotification(this);
    loader.stopThread();
}