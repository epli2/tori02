#include "Bullet.h"

Bullet::Bullet(ofVec3f _position, float _radius, Color _color) :
  ColliderObject(_position, true, _color),
  lifetime_(600),
  lifecount_(0),
  radius_(_radius)
{
  acceleration_.set(0, 0, 1.2);
  velocity_.set(0, 0, -50);
  mesh_.setMode(OF_PRIMITIVE_POINTS);
  for (int i = 0; i < 1000; i++) {
    Particle p;
    p.Setup(ofVec3f(position_.x + ofNoise(5), position_.y + ofNoise(5), position_.z), ofVec3f(0, 0, 0));
    particles.push_back(p);
  }
}

void Bullet::Update() {
  // velocity_ *= acceleration_;
  position_ += velocity_;
  lifecount_ += 1;
  for (auto& particle : particles) {
    // particle.ResetForce();
    particle.AddAttractionForce(position_.x + ofRandom(-200, 200), position_.y + ofRandom(-200, 200), position_.z, radius_, 0.1);
    particle.Update(velocity_);
  }
}

void Bullet::Draw() {
  mesh_.clear();
  switch (color_) {
  case RED:
    ofSetColor(232, 60, 55);
    break;
  case GREEN:
    ofSetColor(72, 232, 124);
    break;
  case BLUE:
    ofSetColor(53, 61, 255);
    break;
  }
  for (auto& particle : particles) {
    mesh_.addVertex(particle.position_);
  }
  mesh_.draw();
  ofCircle(position_, 4);
}

bool Bullet::IsDie() const {
  return (lifetime_ - lifecount_ < 0);
}

Bullet::~Bullet() {}