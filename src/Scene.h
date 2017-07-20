#pragma once

#include "ofMain.h"

class Scene {
protected:
  string name_;

public:
  bool isend_;
  Scene() {};
  virtual void Update() = 0;
  virtual void Draw() = 0;
  virtual void KeyPressed(int _key) = 0;
  virtual void KeyReleased(int _key) = 0;
  string GetName() { return name_; };
  virtual ~Scene() {};
};