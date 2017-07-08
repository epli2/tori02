#pragma once

#include "ofMain.h"
#include "ofxLeapMotion2.h"
#include "Weapon.h"

class TitleScene {
private:
  ofLight light_;
  ofEasyCam cam_;
  ofxLeapMotion leap_;
  vector<ofxLeapMotionSimpleHand> simpleHands_;
  vector<int> fingersFound_;
  ofShader backgroundshader_;
  std::string shaderpath_background_ = "shader/shader_background_title.frag";
  Weapon weapon_;

public:
  TitleScene();
  void Update();
  void Draw();
  void KeyPressed(int _key);
  ~TitleScene() { leap_.close(); };
};