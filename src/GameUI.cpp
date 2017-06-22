#include "GameUI.h"
//#include "ofApp.h"


GameUI::GameUI() {
	color_ = Color(0);
	ccolor = ofColor(232,60,55);
}

GameUI::~GameUI() {

}


int sp = 0;

void GameUI::setup() {
	//player pl;
	//pl.sethp(100);
	//pl.setscore(0);



	ofColor initColor = ofColor(255, 0, 120, 200);

	ofVec2f initPos = ofVec2f(ofGetWidth()/2,ofGetHeight()/2);
	ofVec2f minPos = ofVec2f(0, 0);
	//ofVec2f maxPos = ofVec2f(ofGetWidth(), ofGetHeight());

//	gui1.setup();
	//gui1.add(hpbar.setup("HP",200, 0, 400));

	ofTrueTypeFont::setGlobalDpi(72);

	verdana.load("Verdana.ttf", 30);
	verdana.setLineHeight(24);
	verdana.setLetterSpacing(1.0);
	
}

void GameUI::update() {
	
}

void GameUI::draw() {
	
	//ofSetColor(255, 255, 255);
	ofSetColor(ccolor);
	ofCircle(100, ofGetHeight() - 100, 50);

	char sc[255];
	sprintf(sc, "SCORE : %d", sp);
	ofSetColor(30, 200, 200);
	verdana.drawString(sc, 750, ofGetHeight() / 20);

	//gui1.draw();
}

void GameUI::setColor(Color _color) {
	color_ = _color;
	switch (color_) {
	case RED:
		ccolor = ofColor(232,60,55);
		break;
	case GREEN:
		ccolor = ofColor(72,232,124);
		break;
	case BLUE:
		ccolor = ofColor(53,61,255);
		break;
	}
}