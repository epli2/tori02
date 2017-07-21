#include "GameUI.h"

GameUI::GameUI() : color_(GREEN), ccolor_(ofColor(232, 60, 55)), sp_(0) {}

GameUI::~GameUI() {}

void GameUI::Setup() {
  bosshp_ = -1;
  ofTrueTypeFont::setGlobalDpi(72);
  verdana.load("Verdana.ttf", 30);
  verdana.setLineHeight(24);
  verdana.setLetterSpacing(1.0);

  uipanel_.loadModel(modelpath_uipanel_);
  uimat_.loadModel(modelpath_uimat_);
  uibar_r_.loadModel(modelpath_uibar_[0]);
  uibar_g_.loadModel(modelpath_uibar_[1]);
  uibar_b_.loadModel(modelpath_uibar_[2]);
  uipanel_.setScaleNormalization(false);
  uimat_.setScaleNormalization(false);
  uibar_r_.setScaleNormalization(false);
  uibar_g_.setScaleNormalization(false);
  uibar_b_.setScaleNormalization(false);
  uipanel_.setScale(20, 20, 1);
  uimat_.setScale(20, 20, 10);
  uibar_r_.setScale(20, 20, 10);
  uibar_g_.setScale(20, 20, 10);
  uibar_b_.setScale(20, 20, 10);
  //uipanel_.enableMaterials();
  uimat_.enableMaterials();
  shader_.load("", shaderpath_uimat_);
  uibar_decr_ = ofVec3f(0);
}

void GameUI::Update() {
  if (uibar_decr_.x > 0) {
    uibar_decr_.x -= 0.01;
  }
  if (uibar_decr_.y > 0) {
    uibar_decr_.y -= 0.01;
  }
  if (uibar_decr_.z > 0) {
    uibar_decr_.z -= 0.01;
  }
  uibar_r_.setPosition(20 + uibar_decr_.x * 6.8, ofGetHeight(), 0);
  uibar_r_.setScale(20 - uibar_decr_.x, 20, 10);
  uibar_g_.setPosition(20 + uibar_decr_.y * 6.8, ofGetHeight(), 0);
  uibar_g_.setScale(20 - uibar_decr_.y, 20, 10);
  uibar_b_.setPosition(20 + uibar_decr_.z * 6.8, ofGetHeight(), 0);
  uibar_b_.setScale(20 - uibar_decr_.z, 20, 10);
}

void GameUI::Draw() {
  ofPushStyle();
  ofSetColor(30, 200, 200);
  verdana.drawString("SCORE : " + ofToString(sp_), ofGetWidth() - (ofGetWidth() / 9), ofGetHeight() / 20);
  verdana.drawString("HP: " + ofToString(playerhp_), ofGetWidth() - (ofGetWidth() / 9), ofGetHeight() / 10);
  if (bosshp_ >= 0) {
    verdana.drawString("BOSS HP: " + ofToString(bosshp_), 0, ofGetHeight() / 20);
  }
  ofPopStyle();

  uipanel_.setPosition(0, ofGetHeight(), 0);
  uipanel_.drawFaces();
  uimat_.setPosition(0, ofGetHeight(), 0);
  shader_.begin();
  shader_.setUniform1f("time", ofGetElapsedTimef());
  shader_.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
  shader_.setUniform3f("color", ccolor_.r / 255.0, ccolor_.g / 255.0, ccolor_.b / 255.0);
  uimat_.drawFaces();

  shader_.setUniform3f("color", 232.0 / 255.0, 60.0 / 255.0, 55.0 / 255.0);
  uibar_r_.drawFaces();
  shader_.setUniform3f("color", 72.0 / 255.0, 232.0 / 255.0, 124.0 / 255.0);
  uibar_g_.drawFaces();
  shader_.setUniform3f("color", 53.0 / 255.0, 61.0 / 255.0, 255.0 / 255.0);
  uibar_b_.drawFaces();
  shader_.end();
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

void GameUI::SetPlayerHP(float _hp) {
  playerhp_ = _hp;
}

void GameUI::SetBossHP(float _hp) {
  bosshp_ = _hp;
}
