#pragma once

#include "ofMain.h"
#include "Common.h"
#include "Enemy.h"
#include "ColliderObject.h"

class EnemyCloud {
private:
  int number_;
  bool isauto_;
  bool ismove_;
  ofVec3f range_p_;
  ofVec3f range_n_;
  std::vector<Enemy> enemys_;

public:
  EnemyCloud();
  EnemyCloud(int _number);
  EnemyCloud(int _number, bool _isauto, bool _ismove,
             ofVec3f _range_p, ofVec3f _range_n);
  void Init(int _number);
  void Update();
  void Draw();
  std::vector<ColliderObject*> GetObjectsPtr();
  std::vector<ColliderObject*> GetAllBulletsPtr();
  ~EnemyCloud();
};