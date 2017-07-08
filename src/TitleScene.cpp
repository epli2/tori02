#include "TitleScene.h"

TitleScene::TitleScene() {
  leap_.open();
  leap_.setReceiveBackgroundFrames(true);
  backgroundshader_.load("", shaderpath_background_);
  cam_.setOrientation(ofPoint(0, 0, 0));
  light_.setPosition(1000, 1000, 2000);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glEnable(GL_LIGHTING);
  light_.enable();
  weapon_.SetColor(GREEN);
}

void TitleScene::Update() {
  fingersFound_.clear();
  simpleHands_ = leap_.getSimpleHands();

  if (leap_.isFrameNew() && simpleHands_.size()) {
    leap_.setMappingX(-230, 230, -ofGetWidth() / 2, ofGetWidth() / 2);
    leap_.setMappingY(90, 490, -ofGetHeight() / 2, ofGetHeight() / 2);
    leap_.setMappingZ(-150, 150, -200, 200);
  }
  leap_.markFrameAsOld();
  weapon_.Update();
}

void TitleScene::Draw() {
  backgroundshader_.begin();
  backgroundshader_.setUniform1f("time", ofGetElapsedTimef());
  backgroundshader_.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
  ofDrawPlane(0, 0, 0, ofGetWidth() * 100, ofGetHeight() * 100);
  backgroundshader_.end();
  glClear(GL_DEPTH_BUFFER_BIT);

  cam_.begin(ofRectangle(0, 0, ofGetWidth(), ofGetHeight()));
  for (auto simpleHand : simpleHands_) {
    ofPoint handPos = simpleHand.handPos;
    weapon_.SetPosition(handPos);
    weapon_.SetColor(GREEN);
    weapon_.DrawGun();
  }
  weapon_.DrawBullet();
  cam_.end();
}

void TitleScene::KeyPressed(int _key) {
  if (_key == 'f' && simpleHands_.size()) {
    weapon_.Fire();
  }
}