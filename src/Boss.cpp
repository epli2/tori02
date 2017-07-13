#include "Boss.h"

Boss::Boss() : Boss(ofVec3f(0, -500, -1500), GREEN, 100) {}

Boss::Boss(ofVec3f _position, Color _color, float _radius)
  : ColliderObject(_position, true, _color, CIRCLE, _radius) {
  body_.loadModel(modelpath_body_);
  body_.setScaleNormalization(false);
  light_.loadModel(modelpath_light_);
  light_.setScaleNormalization(false);
  body_.setScale(radius_, radius_, radius_);
  light_.setScale(radius_, radius_, radius_);
  body_.setRotation(2, 180, 0, 0, 1);
  light_.setRotation(2, 180, 0, 0, 1);
  for (int i = 0; i < NUM; i++) {
    freq_[i] = ofRandom(4.0, 10.0);
  }
  shader_.load("", shaderpath_);
  starttime_ = ofGetElapsedTimef();
}

void Boss::Update() {
  float nowtime = ofGetElapsedTimef();
  float difftime = nowtime - starttime_;
  if (int(ofRandom(0, 100)) == 50) {
    Fire();
    printf("Boss: fire\n");
  }
  if (int(ofRandom(0, 200)) == 50) {
    ChangeColor();
    printf("Boss: change color\n");
  }
  /*if (int(ofRandom(0, 200)) == 50) {
    enemyclouds_.push_back(EnemyCloud(5, false, false, ofVec3f(2000, 1000, 1000), ofVec3f(2000, 1000, position_.z)));
    printf("Boss: put children\n");
  }*/
  UpdateBullets();
  UpdateChildren();
}

void Boss::UpdateBullets() {
  auto itr = bullets_.begin();
  while (itr != bullets_.end()) {
    if (!(*itr).isalive_ || (*itr).IsDie()) {
      itr = bullets_.erase(itr);
      printf("BossBullet: die\n");
    }
    else {
      itr++;
    }
  }
  for (auto&& bullet : bullets_) {
    bullet.Update();
  }
}

void Boss::UpdateChildren() {
  for (auto&& enemycloud : enemyclouds_) {
    enemycloud.Update();
  }
}

void Boss::Draw() {
  ofColor rgbcolor;
  switch (color_) {
  case RED:
    rgbcolor = ofColor(232, 60, 55);
    break;
  case GREEN:
    rgbcolor = ofColor(72, 232, 124);
    break;
  case BLUE:
    rgbcolor = ofColor(53, 61, 255);
    break;
  }
  shader_.begin();
  shader_.setUniform1f("u_time", ofGetElapsedTimef());
  shader_.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
  shader_.setUniform3f("u_color", rgbcolor.r / 255.0, rgbcolor.g / 255.0, rgbcolor.b / 255.0);
  shader_.setUniform1fv("freq", freq_, NUM);
  light_.setPosition(position_.x, position_.y, position_.z);
  light_.drawFaces();
  shader_.end();
  body_.setPosition(position_.x, position_.y, position_.z);
  body_.drawFaces();
  DrawBullet();
  DrawChildren();
}

void Boss::DrawBullet() {
  for (auto&& bullet : bullets_) {
    bullet.Draw();
  }
}

void Boss::DrawChildren() {
  for (auto&& enemycloud : enemyclouds_) {
    enemycloud.Draw();
  }
}

void Boss::ChangeColor() {
  color_ = Color((color_ + 1) % 3);
}

void Boss::Fire() {
  bullets_.push_back(Bullet(position_ + ofVec3f(0, 50 * ofGetHeight() / 90, 0), 100000, color_, ofVec3f(0, 0, 50)));
}

std::vector<ColliderObject*> Boss::GetBulletsPtr() {
  std::vector<ColliderObject*> enemybulletrefs;
  for (auto&& bullet : bullets_) {
    enemybulletrefs.push_back(&bullet);
  }
  return enemybulletrefs;
}

Boss::~Boss() {}