#pragma once

//#include "ofApp.h"
#include "ofMain.h"
#include "ofGraphics.h"
#include "ofxGui.h"

class ofUI{
public:
	
	ofUI();
	~ofUI();

	void setup();
	void update();
	void draw();

	//gui
	ofxPanel gui1;
	ofxIntSlider hpbar;
	ofxVec2Slider position;
	ofxColorSlider barcolor;
};