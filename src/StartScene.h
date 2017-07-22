#pragma once

#include "ofMain.h"
#include "ofApp.h"
#include "Scene.h"

class StartScene : public Scene {
private:
  std::string imgpath_tori_ = "images/logo_tori.png";
  std::string imgpath_title_ = "images/logo_title.png";
  ofImage img_tori_;
  ofImage img_title_;
  float starttime;
  int x = 0, y = 0;

public:
  StartScene();
  void Update();
  void Draw();
  void KeyPressed(int _key);
  void KeyReleased(int _key) {};
  ~StartScene() {};
};