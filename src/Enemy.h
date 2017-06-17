#pragma once

#include "Common.h"
#include "ofxAssimpModelLoader.h"

class Enemy {
private:
  ofVec3f position_;
  float hp_;
  const float attack_;
  const Color color_;
  const std::string modelpath_body_ = "models/robot_body.obj";
  const std::string modelpath_light_ = "models/robot_light.obj";
  ofxAssimpModelLoader body_;
  ofxAssimpModelLoader light_;
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