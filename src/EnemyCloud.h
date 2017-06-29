#pragma once

#include "ofMain.h"
#include "Common.h"
#include "Enemy.h"
#include "ColliderObject.h"

class EnemyCloud {
private:
  int number_;
  std::vector<Enemy> enemys_;

public:
  EnemyCloud();
  EnemyCloud(int _number);
  void Update();
  void Draw();
  std::vector<ColliderObject*> GetObjectsPtr();
  std::vector<ColliderObject*> GetAllBulletsPtr();
  ~EnemyCloud();
};