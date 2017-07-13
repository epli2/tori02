#pragma once

#include "ofxAssimpModelLoader.h"
#include "Bullet.h"
#include "ColliderObject.h"
#include "Common.h"
#include "EnemyCloud.h"

class Boss : public ColliderObject {
private:
  std::string modelpath_body_ = "models2/robot_body.obj";
  std::string modelpath_light_ = "models2/robot_light.obj";
  ofxAssimpModelLoader body_;
  ofxAssimpModelLoader light_;
  std::string shaderpath_ = "shader/shader_sin.frag";
  ofShader shader_;
  static const int NUM = 20;
  float freq_[NUM];
  float starttime_;
  std::vector<Bullet> bullets_;
  std::vector<EnemyCloud> enemyclouds_;

public:
  Boss();
  Boss(ofVec3f _position, Color _color, float _radius);
  void Update();
  void UpdateBullets();
  void UpdateChildren();
  void Draw();
  void DrawBullet();
  void DrawChildren();
  void ChangeColor();
  void Fire();
  std::vector<ColliderObject*> Boss::GetBulletsPtr();
  ~Boss();
};