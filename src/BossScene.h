#pragma once

#include "ofMain.h"
#include "ofxLeapMotion2.h"
#include "Common.h"
#include "GameUI.h"
#include "Scene.h"
#include "Weapon.h"

class BossScene : public Scene {
private:
  ofLight light_;
  ofEasyCam cam_;
  ofxLeapMotion leap_;
  vector<ofxLeapMotionSimpleHand> simpleHands_;
  vector<int> fingersFound_;
  Weapon weapon_;
  Color color_ = GREEN;
  GameUI gameui_;

public:
  BossScene();
  void Update();
  void Draw();
  void KeyPressed(int _key);
  void KeyReleased(int _key);
  ~BossScene();
};