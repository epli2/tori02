#include "Collision.h"

Collision::Collision() {}

void Collision::Init(std::vector<ColliderObject*> _objcts1, std::vector<ColliderObject*> _objcts2) {
  objcts1_ = _objcts1;
  objcts2_ = _objcts2;
}

float Collision::Distance(ofVec3f a, ofVec3f b) {
  float dist;
  ofVec3f d = b - a;
  dist = sqrt(d.x * d.x + d.y * d.y + d.z * d.z);
  return dist;
}

void Collision::Update(std::vector<ColliderObject*> _objcts1, std::vector<ColliderObject*> _objcts2) {
  objcts1_ = _objcts1;
  objcts2_ = _objcts2;
  for (auto&& obj1 : objcts1_) {
    for (auto&& obj2 : objcts2_) {
      if (Distance(obj1->GetPosition(), obj2->GetPosition()) < 1000 && (obj1->GetColor() == obj2->GetColor())) {
        // printf("color = %d %d\n", obj1->GetColor(), obj2->GetColor());
        // printf("distance = %f\n", Distance(obj1->GetPosition(), obj2->GetPosition()));
        obj1->isalive_ = false;
        obj2->isalive_ = false;
      }
    }
  }
}

Collision::~Collision() {}