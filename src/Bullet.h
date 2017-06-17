#pragma once

#include "ofMain.h"
#include "Particle.h"
#include "Common.h"

class Bullet {
  private:
    const float lifetime_;
    float lifecount_;
    ofVec3f position_;
    float radius_;
    ofVec3f acceleration_;
    ofVec3f velocity_;
    ofVboMesh mesh_;
    std::vector<Particle> particles;
    Color color_;

  public:
    Bullet(ofVec3f _position, float _radius, Color _color);
    void Update();
    void Draw();
    bool IsDie() const;
    ~Bullet();
};
