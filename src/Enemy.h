#pragma once

#include "Bullet.h"
#include "Common.h"
#include "ColliderObject.h"
#include "ofxAssimpModelLoader.h"

class Enemy : public ColliderObject {
private:
  float hp_;
  float attack_;
  EnemyType type_;
  array<std::string, 5> modelpath_body_{ "models2/mob1_body.obj",
                                         "models2/mob2_body.obj",
                                         "models2/box.obj",
                                         "models2/box2.obj",
                                         "models2/box3.obj" };
  array<std::string, 2> modelpath_light_{ "models2/mob1_light.obj",
                                          "models2/mob2_light.obj" };
  ofxAssimpModelLoader body_;
  ofxAssimpModelLoader light_;
  std::string shaderpath_ = "shader/shader_sin.frag";
  ofShader shader;
  static const int NUM = 20;
  float freq[NUM];
  std::vector<Bullet> bullets_;

public:
  Enemy();
  Enemy(ofVec3f _position, float _hp, float _attack, Color _color, EnemyType _type);
  void Update();
  void SetPosition(ofVec3f _position);
  void Draw();
  bool IsArmed();
  void DrawBullet();
  void Fire();
  void Hit();
  ofVec3f GetPosition();
  std::vector<ColliderObject*> Enemy::GetObjectsPtr();
  ~Enemy();
};