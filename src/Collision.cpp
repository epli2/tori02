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

bool Collision::IsCollide(ColliderObject* obj1, ColliderObject* obj2) {
  if (obj1->GetCollider() == CIRCLE && obj2->GetCollider() == CIRCLE) {
    return (Distance(obj1->GetPosition(), obj2->GetPosition()) < (obj1->GetRadius() + obj2->GetRadius()));
  }
  else if (obj1->GetCollider() == CIRCLE && obj2->GetCollider() == BOX) {
    if ((obj2->GetPosition().z - obj1->GetPosition().z) < obj1->GetRadius()) {
      if (obj2->GetPosition().x < obj1->GetPosition().x && obj1->GetPosition().x < (obj2->GetPosition().x + obj2->GetRect().x) &&
          obj2->GetPosition().y < obj1->GetPosition().y && obj1->GetPosition().y < (obj2->GetPosition().y + obj2->GetRect().y)) {
        return true;
      }
    }
    return false;
  }
}

void Collision::Update(std::vector<ColliderObject*> _objcts1, std::vector<ColliderObject*> _objcts2) {
  objcts1_ = _objcts1;
  objcts2_ = _objcts2;
  for (auto&& obj1 : objcts1_) {
    for (auto&& obj2 : objcts2_) {
      if (IsCollide(obj1, obj2) && (obj1->GetColor() == obj2->GetColor())) {
        // printf("color = %d %d\n", obj1->GetColor(), obj2->GetColor());
        // printf("distance = %f\n", Distance(obj1->GetPosition(), obj2->GetPosition()));
        obj1->Hit();
        obj2->Hit();
      }
    }
  }
}

Collision::~Collision() {}