#include "ofMain.h"
#include "ofApp.h"
#include "SiftGPU/SiftGPU.h"

//========================================================================
int main( ){
	ofSetupOpenGL(1600,900,OF_WINDOW);			// <-------- setup the GL context
	ofSetWindowTitle("Main Loop");
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

	return 1;
}
