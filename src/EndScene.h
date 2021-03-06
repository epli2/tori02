#pragma once

#include "ofMain.h"
#include "ofApp.h"
#include "Scene.h"

class EndScene : public Scene {
private:
  ofTrueTypeFont font_;
  ofXml xml_names_;
  std::string imgpath_tori_ = "images/logo_tori.png";
  std::string imgpath_title_ = "images/logo_title.png";
  std::string bgmpath_ = "music/ed.wav";
  ofImage img_tori_;
  ofImage img_title_;
  ofSoundPlayer bgm_;
  float starttime_;
  float speed_;
  int x = 0, y = 0;

public:
  EndScene();
  void Update();
  void Draw();
  void KeyPressed(int _key);
  void KeyReleased(int _key);
  ~EndScene();
};