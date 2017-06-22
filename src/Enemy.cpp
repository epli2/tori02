#include "Enemy.h"

Enemy::Enemy() : Enemy(ofVec3f(0, 0, 0), 100, 50, RED) {}

Enemy::Enemy(ofVec3f _position, float _hp, float _attack, Color _color)
    : ColliderObject(_position, true, _color), hp_(_hp), attack_(_attack) {
  body_.loadModel(modelpath_body_);
  light_.loadModel(modelpath_light_);
  body_.setScale(0.5, 0.5, 0.5);
  light_.setScale(0.5, 0.5, 0.5);
  body_.setRotation(0, 180, 1, 0, 0);
  light_.setRotation(0, 180, 1, 0, 0);
  body_.enableMaterials();
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
  body_.setPosition(position_.x, position_.y, position_.z);
  light_.setPosition(position_.x, position_.y, position_.z);
  shader.begin();
  shader.setUniform1f("u_time", ofGetElapsedTimef());
  shader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
  shader.setUniform3f("u_color", rgbcolor.r / 255.0, rgbcolor.g / 255.0, rgbcolor.b / 255.0);
  shader.setUniform1fv("freq", freq, NUM);
  light_.drawFaces();
  shader.end();
  body_.drawFaces();
}

Enemy::~Enemy() {}