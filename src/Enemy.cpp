#include "Enemy.h"

Enemy::Enemy() : Enemy(ofVec3f(0, 0, 0), 100, 50, RED, MOB1) {}

Enemy::Enemy(ofVec3f _position, float _hp, float _attack, Color _color, EnemyType _type)
    : ColliderObject(_position, true, _color), hp_(_hp), attack_(_attack), type_(_type) {
  body_.loadModel(modelpath_body_[type_]);
  body_.setScaleNormalization(false);
  if (isArmed()) {
    body_.setScale(100, 100, 100);
  }
  else {
    body_.setScale(50, 50, 50);
  }
  body_.setRotation(0, 180, 0, 0, 1);
  body_.enableMaterials();
  body_.disableColors();
  if (isArmed()) {
    light_.loadModel(modelpath_light_[type_]);
    light_.setScaleNormalization(false);
    light_.setScale(100, 100, 100);
    light_.setRotation(0, 180, 0, 0, 1);
  }
  for (int i = 0; i < NUM; i++) {
    freq[i] = ofRandom(4.0, 10.0);
  }
  shader.load("", shaderpath_);
}

void Enemy::Update() {}

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
  if (isArmed()) {
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
}

bool Enemy::isArmed() {
  return (type_ == MOB1 || type_ == MOB2);
}

Enemy::~Enemy() {}