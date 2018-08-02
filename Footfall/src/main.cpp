#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofSetupOpenGL(1,1,OF_FULLSCREEN);			// <-------- setup the GL context
	ofSetBackgroundColor(0, 0, 0, 255);
	ofHideCursor();

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
}
