#include "DeadScene.h"

DeadScene::DeadScene() {
  name_ = "dead";
  isend_ = false;
  isgameover_ = false;
  ofTrueTypeFont::setGlobalDpi(72);
  ofBackground(0, 0, 0);
}

void DeadScene::Update() {}

void DeadScene::Draw() {
  verdana.load("Verdana.ttf", 30);
  verdana.setLineHeight(24);
  verdana.setLetterSpacing(1.0);
  ofSetColor(120, 120, 120);
  // ofRect(ofGetWidth()/2,ofGetHeight()/2,400,200);
  verdana.drawString("Game Over", ofGetWidth() / 2 - 10, ofGetHeight() / 2);
}

void DeadScene::KeyPressed(int key) {}

DeadScene::~DeadScene() {}