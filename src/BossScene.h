#pragma once

#include "ofMain.h"
#include "ofxLeapMotion2.h"
#include "Boss.h"
#include "Collision.h"
#include "Common.h"
#include "GameUI.h"
#include "Player.h"
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
  Boss boss_;
  Player player_;
  std::vector<ColliderObject*> bv;
  std::vector<ColliderObject*> pv;
  Collision collision_bullets_and_boss_;
  Collision collision_bullets_and_enemys_;
  Collision collision_bullets_and_player_;
  ofShader backgroundshader_;
  std::string bgmpath_ = "music/boss.mp3";
  ofSoundPlayer bgm_;
  float prevfiretime_;
  int i = 0;

  void ChangeColor();
  void WeaponFire();

public:
  BossScene();
  void Update();
  void Draw();
  void KeyPressed(int _key);
  void KeyReleased(int _key);
  ~BossScene();
};