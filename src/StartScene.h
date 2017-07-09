#pragma once

#include "ofMain.h"
#include "Scene.h"

class StartScene : public Scene {
private:
  std::string imgpath_tori_ = "images/logo_tori.png";
  std::string imgpath_title_ = "images/logo_title.png";
  ofImage img_tori_;
  ofImage img_title_;
  float starttime;

public:
  StartScene();
  void Update();
  void Draw();
  void KeyPressed(int _key);
};