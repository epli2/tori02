#pragma once

#include "Bullet.h"
#include "ofxAssimpModelLoader.h"
#include "Common.h"

class Weapon {
private:
  float power_;
  ofVec3f position_;
  const std::string modelpath_ = "models/gun.obj";
  ofxAssimpModelLoader gun_;
  std::vector<Bullet> bullets;

public:
  Weapon();
  void Update();
  void SetPosition(ofVec3f _position);
  void DrawGun();
  void DrawBullet();
  void Fire(Color _color);
  ~Weapon();
};