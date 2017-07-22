#include "Enemy.h"

Enemy::Enemy() : Enemy(ofVec3f(0, 0, 0), 100, 50, RED, MOB1) {}

Enemy::Enemy(ofVec3f _position, float _hp, float _attack, Color _color, EnemyType _type)
    : ColliderObject(_position, true, _color, CIRCLE, 100), hp_(_hp), attack_(_attack), type_(_type) {
  body_.loadModel(modelpath_body_[type_]);
  body_.setScaleNormalization(false);
  if (IsArmed()) {
    body_.setScale(100, 100, 100);
  }
  else {
    body_.setScale(100, 100, 100);
  }
  body_.setRotation(2, 180, 0, 0, 1);
  body_.enableMaterials();
  body_.disableColors();
  if (IsArmed()) {
    light_.loadModel(modelpath_light_[type_]);
    light_.setScaleNormalization(false);
    light_.setScale(100, 100, 100);
    light_.setRotation(2, 180, 0, 0, 1);
  }
  if (position_.x > 1000) {
    body_.setRotation(1, 45, 0, 1, 0);
    light_.setRotation(1, 45, 0, 1, 0);
  }
  else if (position_.x < -1000) {
    body_.setRotation(1, -45, 0, 1, 0);
    light_.setRotation(1, -45, 0, 1, 0);
  }
  for (int i = 0; i < NUM; i++) {
    freq[i] = ofRandom(4.0, 10.0);
  }
  shader.load("", shaderpath_);
}

void Enemy::Update() {
  auto itr = bullets_.begin();
  while (itr != bullets_.end()) {
    if (!(*itr).isalive_) {
      itr = bullets_.erase(itr);
      printf("hit player\n");
    }
    else {
      itr++;
    }
  }
  for (auto& bullet : bullets_) {
    if (bullet.IsDie()) {
      bullets_.pop_back();
      printf("die\n");
    }
    bullet.Update();
  }
  if (IsArmed() && (static_cast<int>(ofRandom(0, 100)) == 50)) {
    Fire();
  }
  if (position_.z > 50) {
    isalive_ = false;
  }
}

void Enemy::SetPosition(ofVec3f _position) {
  position_ = _position;
}

void Enemy::Draw() {
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
  shader.begin();
  shader.setUniform1f("u_time", ofGetElapsedTimef());
  shader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
  shader.setUniform3f("u_color", rgbcolor.r / 255.0, rgbcolor.g / 255.0, rgbcolor.b / 255.0);
  shader.setUniform1fv("freq", freq, NUM);
  if (IsArmed()) {
    light_.setPosition(position_.x, position_.y, position_.z);
    light_.drawFaces();
    shader.end();
    body_.setPosition(position_.x, position_.y, position_.z);
    body_.drawFaces();
  } else {
    body_.setPosition(position_.x, position_.y, position_.z);
    body_.drawFaces();
    shader.end();
  }
  DrawBullet();
}

bool Enemy::IsArmed() {
  return (type_ == MOB1 || type_ == MOB2);
}

void Enemy::DrawBullet() {
  for (auto&& bullet : bullets_) {
    bullet.Draw();
  }
}

void Enemy::Fire() {
  bullets_.push_back(Bullet(position_, 100000, color_, ofVec3f(0, 0, 50)));
}

void Enemy::Hit() {
  GameUI::score_ += 1;
  isalive_ = false;
}

ofVec3f Enemy::GetPosition() {
  return position_;
}

std::vector<ColliderObject*> Enemy::GetObjectsPtr() {
  std::vector<ColliderObject*> enemybulletrefs;
  for (auto&& bullet : bullets_) {
    enemybulletrefs.push_back(&bullet);
  }
  return enemybulletrefs;
}

Enemy::~Enemy() {}