#pragma once

#include "ofMain.h"

class Particle {
private:
  ofVec3f velocity_;
  ofVec3f force_;
  float friction_;
  float radius_;
  bool bFixed_;
  float mass_;

public:
  ofVec3f position_;

  Particle();
  void Setup(ofVec3f _position, ofVec3f _velocity);
  void Setup(float _positionX, float _positionY, float _positionZ,
             float _velocityX, float _velocityY, float _velocityZ);
  void ResetForce();
  void AddForce(ofVec3f _force);
  void AddForce(float _forceX, float _forceY, float _forceZ);
  void UpdateForce();
  void UpdatePos(ofVec3f _velocity);
  void Update(ofVec3f _velocity);
  void Draw();
  void AddRepulsionForce(float _x, float _y, float _z, float _radius,
                         float _scale);
  void AddAttractionForce(float _x, float _y, float _z, float _radius,
                          float _scale);
  ~Particle();
};