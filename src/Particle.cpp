#include "Particle.h"

Particle::Particle()
    : radius_(5.0), friction_(0.01), mass_(1.0), bFixed_(false) {}

void Particle::Setup(ofVec3f _position, ofVec3f _velocity) {
  position_ = _position;
  velocity_ = _velocity;
}

void Particle::Setup(float _positionX, float _positionY, float _positionZ,
                     float _velocityX, float _velocityY, float _velocityZ) {
  position_ = ofVec3f(_positionX, _positionY, _positionZ);
  velocity_ = ofVec3f(_velocityX, _velocityY, _velocityZ);
}

void Particle::ResetForce() { force_.set(0, 0, 0); }

void Particle::AddForce(ofVec3f _force) { force_ += _force / mass_; }

void Particle::AddForce(float _forceX, float _forceY, float _forceZ) {
  force_ += ofVec3f(_forceX, _forceY, _forceZ);
}

void Particle::UpdateForce() { force_ -= velocity_ * friction_; }

void Particle::UpdatePos(ofVec3f _velocity) {
  if (!bFixed_) {
    velocity_ += force_;
    position_ += _velocity +  velocity_;
  }
}

void Particle::Update(ofVec3f _velocity) {
  UpdateForce();
  UpdatePos(_velocity);
}

void Particle::Draw() { ofCircle(position_, radius_); }

void Particle::AddRepulsionForce(float _x, float _y, float _z, float _radius,
                                 float _scale) {
  ofVec3f posOfForce;
  posOfForce.set(_x, _y, _z);
  ofVec3f diff = position_ - posOfForce;
  float length = diff.length();
  bool bAmCloseEnough = true;
  if (_radius > 0) {
    if (length > _radius) {
      bAmCloseEnough = false;
    }
  }
  if (bAmCloseEnough) {
    float pct = 1 - (length / _radius);
    diff.normalize();
    force_ = force_ - diff * _scale * pct;
  }
}

void Particle::AddAttractionForce(float _x, float _y, float _z, float _radius,
                                  float _scale) {
  ofVec3f posOfForce;
  posOfForce.set(_x, _y, _z);
  ofVec3f diff = position_ - posOfForce;
  float length = diff.length();
  bool bAmCloseEnough = true;
  // if (_radius > 0 && length > _radius) {
  //   bAmCloseEnough = false;
  // }
  if (bAmCloseEnough) {
    float pct = 1 - (length / _radius);
    diff.normalize();
    force_.x = force_.x - diff.x * _scale * pct;
    force_.y = force_.y - diff.y * _scale * pct;
  }
}

Particle::~Particle() {}