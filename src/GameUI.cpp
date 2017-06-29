#include "GameUI.h"

GameUI::GameUI() : color_(GREEN), ccolor_(ofColor(232, 60, 55)), sp_(0) {}

GameUI::~GameUI() {}

void GameUI::Setup() {
  // player pl;
  // pl.sethp(100);
  // pl.setscore(0);

  ofColor initColor = ofColor(255, 0, 120, 200);

  ofVec2f initPos = ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2);
  ofVec2f minPos = ofVec2f(0, 0);
  // ofVec2f maxPos = ofVec2f(ofGetWidth(), ofGetHeight());

  // gui1.setup();
  // gui1.add(hpbar.setup("HP",200, 0, 400));

  ofTrueTypeFont::setGlobalDpi(72);

  verdana.load("Verdana.ttf", 30);
  verdana.setLineHeight(24);
  verdana.setLetterSpacing(1.0);
}

void GameUI::Update() {}

void GameUI::Draw() {

  // ofSetColor(255, 255, 255);
  ofSetColor(ccolor_);
  ofCircle(100, ofGetHeight() - 100, 50);

  char sc[255];
  sprintf(sc, "SCORE : %d", sp_);
  ofSetColor(30, 200, 200);
  verdana.drawString(sc, 750, ofGetHeight() / 20);

  // gui1.draw();
}

void GameUI::SetColor(Color _color) {
  color_ = _color;
  switch (color_) {
  case RED:
    ccolor_ = ofColor(232, 60, 55);
    break;
  case GREEN:
    ccolor_ = ofColor(72, 232, 124);
    break;
  case BLUE:
    ccolor_ = ofColor(53, 61, 255);
    break;
  }
}