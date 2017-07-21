#include "StartScene.h"

StartScene::StartScene() {
  name_ = "start";
  isend_ = false;
  isgameover_ = false;
  isgameclear_ = false;
  img_tori_.load(imgpath_tori_);
  img_title_.load(imgpath_title_);
  img_title_.resize(img_title_.getWidth() / 2.5, img_title_.getHeight() / 2.5);
  ofBackground(0, 0, 0);
  starttime = ofGetElapsedTimef();
}

void StartScene::Update() {}

void StartScene::Draw() {
  float etime = ofGetElapsedTimef() - starttime;
  if (etime <= 4) {
    ofPushStyle();
    ofSetColor(255, 255, 255, 255 - 255 * (etime * etime * etime / 64));
    img_tori_.draw(ofGetWidth() / 2 - img_tori_.getWidth() / 2, ofGetHeight() / 2 - img_tori_.getHeight() / 2);
    ofPopStyle();
  }
  else if (etime > 4 && etime <= 8) {
    etime -= 4;
    ofPushStyle();
    ofSetColor(255, 255, 255, 255 - 255 * (etime * etime * etime / 64));
    img_title_.draw(ofGetWidth() / 2 - img_title_.getWidth() / 2, ofGetHeight() / 2 - img_title_.getHeight() / 2);
    ofPopStyle();
  }
  if (etime > 8.5) {
    isend_ = true;
  }
}

void StartScene::KeyPressed(int _key) {}