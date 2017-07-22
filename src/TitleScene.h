#pragma once

#include "ofMain.h"
#include "ofxLeapMotion2.h"
#include "Collision.h"
#include "MenuButton.h"
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
  ofSoundPlayer bgm_;
  std::string shaderpath_background_ = "shader/shader_background_title.frag";
  std::string bgmpath_ = "music/op01.mp3";
  std::string modelpath_startpanel_ = "models/START.obj";
  std::string modelpath_exitpanel_ = "models/EXIT.obj";
  Weapon weapon_;
  Color color_ = GREEN;
  MenuButton startbutton_;
  MenuButton exitbutton_;
  float prevfiretime_;
  int i = 0;

  void ChangeColor();

public:
  TitleScene();
  void Update();
  void Draw();
  void KeyPressed(int _key);
  void KeyReleased(int _key) {};
  ~TitleScene() {
    bgm_.unload();
    leap_.close();
  };
};