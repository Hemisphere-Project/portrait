#include "ofMain.h"
#include "testApp.h"

//========================================================================
int main( ){
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context
    //ofSetupOpenGL(600,300,OF_WINDOW);
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetFrameRate(5);
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new testApp());

}
