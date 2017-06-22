#pragma once

#include "ofMain.h"
#include "Common.h"

class ColliderObject {
protected:
  ofVec3f position_;
  Collider collider_;
  Color color_;

  ColliderObject() : ColliderObject(ofVec3f(0, 0, 0), true, RED) {};
  ColliderObject(ofVec3f _position, bool _isalive, Color _color) : position_(_position), isalive_(_isalive), color_(_color) {};

public:
  ofVec3f GetPosition() { return position_; };
  Color GetColor() { return color_; };
  bool isalive_;
};