#pragma once

#include <vector>
#include "ColliderObject.h"

class Collision {
private:
  std::vector<ColliderObject*> objcts1_, objcts2_;
  float Distance(ofVec3f a, ofVec3f b);
  bool IsCollide(ColliderObject* obj1, ColliderObject* obj2);

public:
  Collision();
  void Init(std::vector<ColliderObject*> _objcts1, std::vector<ColliderObject*> _objcts2);
  void Update(std::vector<ColliderObject*> _objcts1, std::vector<ColliderObject*> _objcts2);
  void DestroyObject();
  ~Collision();
};