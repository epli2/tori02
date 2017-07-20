#pragma once

#include "ofxAssimpModelLoader.h"
#include "Bullet.h"
#include "ColliderObject.h"
#include "Common.h"
#include "EnemyCloud.h"

class Boss : public ColliderObject {
private:
  std::string modelpath_body_ = "models2/robot_nomal.dae";
  ofxAssimpModelLoader body_;
  std::string shaderpath_ = "shader/shader_sin.frag";
  ofShader shader_;
  static const int NUM = 20;
  float freq_[NUM];
  float starttime_;
  std::vector<Bullet> bullets_;
  std::vector<EnemyCloud> enemyclouds_;
  ofMesh wingmesh_;

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