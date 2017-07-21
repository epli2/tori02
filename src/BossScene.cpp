#include "BossScene.h"

BossScene::BossScene() {
  name_ = "boss";
  isend_ = false;
  isgameover_ = false;
  leap_.open();
  leap_.setReceiveBackgroundFrames(true);
  cam_.setOrientation(ofPoint(0, 0, 0));
  light_.setPosition(1000, 1000, 2000);
  gameui_.Setup();
  bv.push_back(&boss_);
  pv.push_back(&player_);
  collision_bullets_and_boss_.Init(weapon_.GetObjectsPtr(), bv);
  collision_bullets_and_enemys_.Init(weapon_.GetObjectsPtr(), boss_.GetEnemysPtr());
  collision_bullets_and_player_.Init(boss_.GetBulletsPtr(), pv);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glEnable(GL_LIGHTING);
  light_.enable();
  weapon_.SetColor(color_);
}

void BossScene::Update() {
  if (player_.hp_ <= 0) {
    isend_ = true;
  }
  fingersFound_.clear();
  simpleHands_ = leap_.getSimpleHands();

  if (leap_.isFrameNew() && simpleHands_.size()) {
    leap_.setMappingX(-230, 230, -ofGetWidth() / 2, ofGetWidth() / 2);
    leap_.setMappingY(90, 490, -ofGetHeight() / 2, ofGetHeight() / 2);
    leap_.setMappingZ(-150, 150, -200, 200);
  }
  leap_.markFrameAsOld();
  collision_bullets_and_boss_.Update(weapon_.GetObjectsPtr(), bv);
  collision_bullets_and_enemys_.Update(weapon_.GetObjectsPtr(), boss_.GetEnemysPtr());
  collision_bullets_and_player_.Update(boss_.GetBulletsPtr(), pv);
  boss_.Update();
  weapon_.Update();
  gameui_.Update();
}

void BossScene::Draw() {
  cam_.begin(ofRectangle(0, 0, ofGetWidth(), ofGetHeight()));
  boss_.Draw();
  for (auto simpleHand : simpleHands_) {
    ofPoint handPos = simpleHand.handPos;
    weapon_.SetPosition(handPos);
    weapon_.SetColor(color_);
    weapon_.DrawGun();
  }
  weapon_.DrawBullet();
  cam_.end();
  gameui_.SetPlayerHP(player_.hp_);
  gameui_.SetColor(color_);
  gameui_.Draw();
}

void BossScene::KeyPressed(int _key) {
  if (_key == 'f' && simpleHands_.size()) {
    weapon_.Fire();
  }
  if (_key == 'c') {
    ChangeColor();
  }
}

void BossScene::KeyReleased(int _key) {}

void BossScene::ChangeColor() {
  color_ = Color((color_ + 1) % 3);
}

BossScene::~BossScene() {
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_NORMALIZE);
  glDisable(GL_LIGHTING);
  leap_.close();
};