#include "Weapon.h"

Weapon::Weapon() : power_(5) {
  gun_.loadModel(modelpath_gun_);
  light_.loadModel(modelpath_light_);
  gun_.setScale(0.5, 0.5, 0.5);
  light_.setScale(0.4, 0.4, 0.4);
  gun_.setRotation(0, 180, 1, 0, 0);
  light_.setRotation(0, 180, 1, 0, 0);
  gun_.enableColors();
  gun_.enableMaterials();
  for (int i = 0; i < NUM; i++) {
    freq[i] = ofRandom(4.0, 10.0);
  }
  shader.load("", shaderpath_light_);
}

void Weapon::Update() {
  auto itr = bullets.begin();
  while (itr != bullets.end()) {
    if (!(*itr).isalive_) {
      itr = bullets.erase(itr);
      printf("kill enemy\n");
    }
    else {
      itr++;
    }
  }
  for (auto& bullet : bullets) {
    if (bullet.IsDie()) {
      bullets.pop_back();
      printf("die\n");
    }
    bullet.Update();
  }
}

void Weapon::SetPosition(ofVec3f _position) {
  position_ = _position;
}

void Weapon::SetColor(Color _color) {
  color_ = _color;
  switch (color_) {
  case RED:
    rgbcolor_ = ofColor(232, 60, 55);
    break;
  case GREEN:
    rgbcolor_ = ofColor(72, 232, 124);
    break;
  case BLUE:
    rgbcolor_ = ofColor(53, 61, 255);
    break;
  }
}

void Weapon::DrawGun() {
  gun_.setPosition(position_.x, position_.y, position_.z);
  light_.setPosition(position_.x, position_.y, position_.z);
  gun_.drawFaces();
  shader.begin();
  shader.setUniform1f("u_time", ofGetElapsedTimef());
  shader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
  shader.setUniform3f("u_color", rgbcolor_.r / 255.0, rgbcolor_.g / 255.0, rgbcolor_.b / 255.0);
  shader.setUniform1fv("freq", freq, NUM);
  light_.drawFaces();
  shader.end();
  // gun_.drawWireframe();
}

void Weapon::DrawBullet() {
  for (auto bullet : bullets) {
    bullet.Draw();
  }
}

void Weapon::Fire() {
  bullets.push_back(Bullet(position_ + ofVec3f(0, 190, -130), 100000, color_));
}

std::vector<ColliderObject*> Weapon::GetObjectsPtr() {
  std::vector<ColliderObject*> bulletrefs;
  for (auto&& bullet : bullets) {
    bulletrefs.push_back(&bullet);
  }
  return bulletrefs;
}

Weapon::~Weapon() {}