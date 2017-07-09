#pragma once

#include "ofMain.h"
#include "Scene.h"

class EndScene : public Scene {
private:
  ofTrueTypeFont font_;
  ofXml xml_names_;
  std::string imgpath_tori_ = "images/logo_tori.png";
  std::string imgpath_title_ = "images/logo_title.png";
  ofImage img_tori_;
  ofImage img_title_;
  float starttime_;
  float speed_;

public:
  EndScene();
  void Update();
  void Draw();
  void KeyPressed(int _key);
  void KeyReleased(int _key);
  ~EndScene();
};