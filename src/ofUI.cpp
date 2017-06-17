#include "ofUI.h"
//#include "ofApp.h"

/*
class player {
private:
	int hp;
	int score;
public:
	void sethp(int hpbar);
	void setscore(int sc);
};

class col {
private:
	int r, g, b;
public:
	void setr(int cr);
	void setg(int cg);
	void setb(int cb);
};
*/

ofUI::ofUI() {

}

ofUI::~ofUI() {

}




void ofUI::setup() {
	//player pl;
	//pl.sethp(100);
	//pl.setscore(0);


	ofSetFrameRate(60);

	ofColor initColor = ofColor(255, 0, 120, 200);

	ofVec2f initPos = ofVec2f(ofGetWidth()/2,ofGetHeight()/2);
	ofVec2f minPos = ofVec2f(0, 0);
	//ofVec2f maxPos = ofVec2f(ofGetWidth(), ofGetHeight());

	gui1.setup();
	gui1.add(hpbar.setup("HP",200, 0, 400));

	
}

void ofUI::update() {
	
}

void ofUI::draw() {
	
	//ofColor();
	ofDrawCircle(0, 0, 0, 5);

	gui1.draw();
}