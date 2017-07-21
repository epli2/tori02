#pragma once

#include "ofMain.h"
#include "ofxLeapMotion2.h"
#include "Collision.h"
#include "Common.h"
#include "EnemyCloud.h"
#include "GameUI.h"
#include "Player.h"
#include "Scene.h"
#include "Weapon.h"

class ButtleScene : public Scene {
private:
  ofxLeapMotion leap;
  ofLight light;
  vector<ofxLeapMotionSimpleHand> simpleHands;
  Weapon weapon;
  vector<int> fingersFound;
  ofEasyCam cam;
  Color color = GREEN;
  EnemyCloud enemycloud;
  Collision collision_bullets_and_enemys;
  Collision collision_bullets_and_player;
  Collision collision_enemys_and_player;
  GameUI gameui;
  ofShader backgroundshader;
  Player player;
  std::vector<ColliderObject*> pv;
  std::string bgmpath_ = "music/battle01.mp3";
  ofSoundPlayer bgm_;
  float starttime_;
  float prevfiretime_;

  void ChangeColor();
  void WeaponFire();

public:
  ButtleScene();
  void Update();
  void Draw();
  void KeyPressed(int _key);
  void KeyReleased(int _key) {};
  ~ButtleScene() {
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_NORMALIZE);
    glDisable(GL_LIGHTING);
    bgm_.loadSound(bgmpath_);
    bgm_.setVolume(0.5f);
    bgm_.play();
    leap.close();
  };
};