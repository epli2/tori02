#include "BossScene.h"

BossScene::BossScene() {
  name_ = "boss";
  isend_ = false;
  isgameover_ = false;
  isgameclear_ = false;
  leap_.open();
  leap_.setReceiveBackgroundFrames(true);
  cam_.setOrientation(ofPoint(0, 0, 0));
  light_.setPosition(1000, 1000, 2000);
  gameui_.Setup();
  backgroundshader_.load("", "shader/shader_background_boss.frag");
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
  boss_.GetHPPtr(&player_.hp_);
}

void BossScene::Update() {
  if (player_.hp_ <= 0) {
    isend_ = true;
  }
  if (boss_.hp_ <= 0) {
    isgameclear_ = true;
  }
  fingerType fingerTypes[] = { THUMB, INDEX, MIDDLE, RING, PINKY };
  fingersFound_.clear();
  simpleHands_ = leap_.getSimpleHands();
  double middleDistanceX0;
  double middleDistanceY0;
  double middleDistanceZ0;
  double middleDistanceX1;
  double middleDistanceY1;
  double middleDistanceZ1;
  double middleDistanceSum0 = 20000;
  double middleDistanceSum1 = 20000;

  if (leap_.isFrameNew() && simpleHands_.size()) {
    leap_.setMappingX(-230, 230, -ofGetWidth() / 2, ofGetWidth() / 2);
    leap_.setMappingY(90, 490, -ofGetHeight() / 2, ofGetHeight() / 2);
    leap_.setMappingZ(-150, 150, -200, 200);
    middleDistanceX0 =
      simpleHands_[0].fingers[MIDDLE].tip.x - simpleHands_[0].handPos.x;
    middleDistanceY0 =
      simpleHands_[0].fingers[MIDDLE].tip.y - simpleHands_[0].handPos.y;
    middleDistanceZ0 =
      simpleHands_[0].fingers[MIDDLE].tip.z - simpleHands_[0].handPos.z;
    middleDistanceSum0 = middleDistanceX0 * middleDistanceX0 +
      middleDistanceY0 * middleDistanceY0 +
      middleDistanceZ0 * middleDistanceZ0;
    // printf("%d", simpleHands.size());
    if (simpleHands_.size() == 2) {
      // printf("!!\n");
      middleDistanceX1 =
        simpleHands_[1].fingers[MIDDLE].tip.x - simpleHands_[1].handPos.x;
      middleDistanceY1 =
        simpleHands_[1].fingers[MIDDLE].tip.y - simpleHands_[1].handPos.y;
      middleDistanceZ1 =
        simpleHands_[1].fingers[MIDDLE].tip.z - simpleHands_[1].handPos.z;
      middleDistanceSum1 = middleDistanceX1 * middleDistanceX1 +
        middleDistanceY1 * middleDistanceY1 +
        middleDistanceZ1 * middleDistanceZ1;
      if (middleDistanceSum1 > 10000) {
        // printf("middleDistance1\n");
        ChangeColor();
        // printf("%d\n", color);
      }
    }
  }
  leap_.markFrameAsOld();
  collision_bullets_and_boss_.Update(weapon_.GetObjectsPtr(), bv);
  collision_bullets_and_enemys_.Update(weapon_.GetObjectsPtr(), boss_.GetEnemysPtr());
  collision_bullets_and_player_.Update(boss_.GetBulletsPtr(), pv);
  boss_.Update();
  weapon_.Update();
  gameui_.Update();
  if (/*middleDistanceSum0 < 10000 && */
    simpleHands_.size() &&
    ofGetElapsedTimef() - prevfiretime_ > 0.1) {
    weapon_.SetColor(color_);
    WeaponFire();
    prevfiretime_ = ofGetElapsedTimef();
    // printf("fire\n");
  }
}

void BossScene::Draw() {
  backgroundshader_.begin();
  backgroundshader_.setUniform1f("time", ofGetElapsedTimef());
  backgroundshader_.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
  ofDrawPlane(0, 0, 0, ofGetWidth() * 100, ofGetHeight() * 100);
  backgroundshader_.end();
  glClear(GL_DEPTH_BUFFER_BIT);

  cam_.begin(ofRectangle(0, 0, ofGetWidth(), ofGetHeight()));
  boss_.Draw();
  for (auto&& simpleHand : simpleHands_) {
    ofPoint handPos = simpleHand.handPos;
    weapon_.SetPosition(simpleHands_[0].handPos);
    // weapon.SetRotation(0, 45, 0, 1, 0);
    double citay = atan((simpleHands_[0].handPos.x -
      simpleHands_[0].fingers[THUMB].tip.x) /
      (simpleHands_[0].handPos.y -
        simpleHands_[0].fingers[THUMB].tip.y));
    double citaz = atan((simpleHands_[0].fingers[INDEX].mcp.z -
      simpleHands_[0].fingers[INDEX].tip.z) /
      (simpleHands_[0].fingers[INDEX].tip.x -
        simpleHands_[0].fingers[INDEX].mcp.x));
    // printf("mcp:%f\n", simpleHands[0].fingers[INDEX].tip.x);
    // printf("tip:%f\n", simpleHands[0].fingers[INDEX].tip.x -
    // simpleHands[0].fingers[INDEX].mcp.x);
    // printf("%f\n", citay * 100);
    // printf("%f\n", citaz * 100);
    // weapon.SetRotation(0, 180, 1, -(citay * 100) / 180, 0);
    weapon_.SetRotation(0, 180, 1, 0, (citaz * 100) / 180);
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
    WeaponFire();
  }
  if (_key == 'c') {
    ChangeColor();
  }
}

void BossScene::KeyReleased(int _key) {}

void BossScene::ChangeColor() {
  color_ = Color((color_ + 1) % 3);
}

void BossScene::WeaponFire() {
  switch (color_)
  {
  case RED:
    if (20 - gameui_.uibar_decr_.x > 0) {
      weapon_.Fire();
      gameui_.uibar_decr_.x += 1;
      printf("fire\n");
    }
    break;
  case GREEN:
    if (20 - gameui_.uibar_decr_.y > 0) {
      weapon_.Fire();
      gameui_.uibar_decr_.y += 1;
      printf("fire\n");
    }
    break;
  case BLUE:
    if (20 - gameui_.uibar_decr_.z > 0) {
      weapon_.Fire();
      gameui_.uibar_decr_.z += 1;
      printf("fire\n");
    }
    break;
  default:
    break;
  }
}

BossScene::~BossScene() {
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_NORMALIZE);
  glDisable(GL_LIGHTING);
  leap_.close();
};