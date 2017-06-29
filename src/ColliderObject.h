#pragma once

#include "ofMain.h"
#include "Common.h"

class ColliderObject {
protected:
  ofVec3f position_;
  Collider collider_;
  Color color_;
  float radius_;
  float width_;
  float height_;

  ColliderObject(ofVec3f _position, bool _isalive, Color _color, Collider _collider, float _radius)
    : ColliderObject(_position, _isalive, _color, _collider, _radius, -1, -1) {};
  ColliderObject(ofVec3f _position, bool _isalive, Color _color, Collider _collider, float _width, float _height)
    : ColliderObject(_position, _isalive, _color, _collider, -1, _width, _height) {};
  ColliderObject(ofVec3f _position, bool _isalive, Color _color, Collider _collider, float _radius, float _width, float _height)
    : position_(_position), isalive_(_isalive), color_(_color), collider_(_collider), radius_(_radius), width_(_width), height_(_height) {};

public:
  ofVec3f GetPosition() { return position_; };
  Color GetColor() { return color_; };
  Collider GetCollider() { return collider_; };
  float GetRadius() { return radius_; };
  ofVec2f GetRect() { return ofVec2f(width_, height_); };
  bool isalive_;
};