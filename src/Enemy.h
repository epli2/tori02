#pragma once

#include "Common.h"
#include "ColliderObject.h"
#include "ofxAssimpModelLoader.h"

class Enemy : public ColliderObject {
private:
  float hp_;
  float attack_;
  std::string modelpath_body_ = "models/robot_body.obj";
  std::string modelpath_light_ = "models/robot_light.obj";
  ofxAssimpModelLoader body_;
  ofxAssimpModelLoader light_;
  std::string shaderpath_ = "shader/shader_sin.frag";
  ofShader shader;
  static const int NUM = 20;
  float freq[NUM];

public:
  Enemy();
  Enemy(ofVec3f _position, float _hp, float _attack, Color _color);
  void Update();
  void SetPosition(ofVec3f _position);
  void Draw();
  ~Enemy();
};