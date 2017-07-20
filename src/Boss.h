#pragma once

#include "ofxAssimpModelLoader.h"
#include "Bullet.h"
#include "ColliderObject.h"
#include "Common.h"
#include "EnemyCloud.h"

class Boss : public ColliderObject {
private:
  std::string modelpath_body_ = "models2/robot_nomal.dae";
  std::string modelpath_body_atk1_ = "models2/robot_atk1.dae";
  std::string modelpath_body_atk2_ = "models2/robot_atk2.dae";
  std::string modelpath_body_damage_ = "models2/robot_dam.dae";
  ofxAssimpModelLoader body_;
  ofxAssimpModelLoader body_atk1_;
  ofxAssimpModelLoader body_atk2_;
  ofxAssimpModelLoader body_damage_;
  std::string shaderpath_ = "shader/shader_sin.frag";
  ofShader shader_;
  static const int NUM = 20;
  float freq_[NUM];
  float starttime_;
  std::vector<Bullet> bullets_;
  std::vector<EnemyCloud> enemyclouds_;
  ofMesh wingmesh_;
  enum Status { NORMAL, PUNCH, FIRE, PUT, DAMAGE };
  Status bossstatus_;
  ofxAssimpModelLoader* bodyptr_;
  float firetime_;
  static const int NCHILDREN = 20;

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
  void Hit();
  ofxAssimpModelLoader ModelInit(std::string modelpath);
  std::vector<ColliderObject*> GetBulletsPtr();
  std::vector<ColliderObject*> GetEnemysPtr();
  ~Boss();
};