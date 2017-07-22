#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "Common.h"

class GameUI {
private:
  float playerhp_;
  float bosshp_;
  Color color_;
  ofColor ccolor_;
  ofTrueTypeFont verdana;
  std::string modelpath_uipanel_ = "models/UI1.obj";
  std::string modelpath_uimat_ = "models/UI1_light.obj";
  array<std::string, 3> modelpath_uibar_{ "models/UI1_red.obj",
                                          "models/UI1_green.obj",
                                          "models/UI1_blue.obj" };
  std::string shaderpath_uimat_ = "shader/shader_ball.frag";
  ofxAssimpModelLoader uipanel_;
  ofxAssimpModelLoader uimat_;
  ofxAssimpModelLoader uibar_r_;
  ofxAssimpModelLoader uibar_g_;
  ofxAssimpModelLoader uibar_b_;
  ofShader shader_;

public:
  static int score_;
  ofVec3f uibar_decr_;
  GameUI();
  ~GameUI();

  void Setup();
  void Update();
  void Draw();
  void SetColor(Color _color);
  void SetPlayerHP(float _hp);
  void SetBossHP(float _hp);
};