#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ColliderObject.h"
#include "Common.h"

class MenuButton : public ColliderObject {
private:
  ofxAssimpModelLoader panel_;

public:
  MenuButton(ofVec3f _position, Color _color, float _width, float _heigt, std::string _modelpath);
  ~MenuButton();
  void Update() {};
  void Draw();
};