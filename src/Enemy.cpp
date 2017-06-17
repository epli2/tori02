#include "Enemy.h"

Enemy::Enemy()
  : position_(ofVec3f(0, 0, 0)), hp_(100), attack_(50), color_(RED) {
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
  shader.load("", "shader/shader_sin.frag");
}

Enemy::Enemy(ofVec3f _position, float _hp, float _attack, Color _color)
    : position_(_position), hp_(_hp), attack_(_attack), color_(_color) {
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
  shader.load("", "shader/shader_sin.frag");
}
void Enemy::Update() {}
void Enemy::SetPosition(ofVec3f _position) {
  position_ = _position;
}
void Enemy::Draw() {
  body_.setPosition(position_.x, position_.y, position_.z);
  light_.setPosition(position_.x, position_.y, position_.z);
  shader.begin();
  shader.setUniform1f("u_time", ofGetElapsedTimef());
  shader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
  shader.setUniform3f("u_color", 0.2, 0.5, 1.0);
  shader.setUniform1fv("freq", freq, NUM);
  light_.drawFaces();
  shader.end();
  body_.drawFaces();
}
Enemy::~Enemy() {}