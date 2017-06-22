#pragma once

#include "Bullet.h"
#include "ofxAssimpModelLoader.h"
#include "Common.h"

class Weapon {
private:
  float power_;
  ofVec3f position_;
  Color color_;
  ofColor rgbcolor_;
  const std::string modelpath_gun_ = "models/hontai.lwo";
  const std::string modelpath_light_ = "models/light.lwo";
  ofxAssimpModelLoader gun_;
  ofxAssimpModelLoader light_;
  std::vector<Bullet> bullets;
  const std::string shaderpath_light_ = "shader/shader_sin.frag";
  ofShader shader;
  static const int NUM = 20;
  float freq[NUM];

public:
  Weapon();
  void Update();
  void SetPosition(ofVec3f _position);
  void SetColor(Color _color);
  void DrawGun();
  void DrawBullet();
  void Fire();
  std::vector<ColliderObject*> GetObjectsPtr();
  ~Weapon();
};