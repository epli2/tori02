#pragma once

#include "ofMain.h"
#include "ofxLeapMotion2.h"
#include "Scene.h"
#include "Weapon.h"

class TitleScene : public Scene {
private:
  ofLight light_;
  ofEasyCam cam_;
  ofxLeapMotion leap_;
  vector<ofxLeapMotionSimpleHand> simpleHands_;
  vector<int> fingersFound_;
  ofShader backgroundshader_;
  std::string shaderpath_background_ = "shader/shader_background_title.frag";
  Weapon weapon_;
  Color color_ = GREEN;
  float prevfiretime_;

  void ChangeColor();

public:
  TitleScene();
  void Update();
  void Draw();
  void KeyPressed(int _key);
  void KeyReleased(int _key) {};
  ~TitleScene() { leap_.close(); };
};