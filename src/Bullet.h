#pragma once

#include "ofMain.h"
#include "Particle.h"
#include "Common.h"
#include "ColliderObject.h"

class Bullet : public ColliderObject {
  private:
    float lifetime_;
    float lifecount_;
    float radius_;
    ofVec3f acceleration_;
    ofVec3f velocity_;
    ofVboMesh mesh_;
    std::vector<Particle> particles;

  public:
    Bullet(ofVec3f _position, float _radius, Color _color);
    void Update();
    void Draw();
    bool IsDie() const;
    ~Bullet();
};
