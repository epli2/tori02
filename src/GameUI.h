#pragma once

//#include "ofApp.h"
#include "ofMain.h"
#include "ofGraphics.h"
#include "ofxGui.h"
#include "Common.h"

class GameUI{
private:
	int sp;
	Color color_;
	ofColor ccolor;

public:
	
	GameUI();
	~GameUI();

	void setup();
	void update();
	void draw();
	void setColor(Color _color);

	//gui
	/*
	ofxPanel gui1;
	ofxIntSlider hpbar;
	ofxVec2Slider position;
	ofxColorSlider barcolor;
	*/
	ofTrueTypeFont verdana;
};