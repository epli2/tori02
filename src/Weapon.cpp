#include "Weapon.h"

Weapon::Weapon() : power_(5) {
  gun_.loadModel(modelpath_);
  gun_.setScale(0.5, 0.5, 0.5);
  gun_.setRotation(0, 180, 1, 0, 0);
  gun_.enableColors();
  gun_.enableMaterials(); 
}

void Weapon::Update() {
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

void Weapon::DrawGun() {
  gun_.setPosition(position_.x, position_.y, position_.z);
  gun_.drawFaces();
  // gun_.drawWireframe();
}

void Weapon::DrawBullet() {
  for (auto bullet : bullets) {
    bullet.Draw();
  }
}

void Weapon::Fire(Color _color) { bullets.push_back(Bullet(position_ + ofVec3f(0, 190, -130), 100000, _color)); }

Weapon::~Weapon() {}