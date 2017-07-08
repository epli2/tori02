#include "EnemyCloud.h"

EnemyCloud::EnemyCloud() : EnemyCloud(10) {}

EnemyCloud::EnemyCloud(int _number) : number_(_number) {
  Init(_number);
}

void EnemyCloud::Init(int _number) {
  number_ = _number;
  int posrange = 100;
  for (int i = 0; i < number_; i++) {
    ofVec3f pos = ofVec3f(ofRandom(-posrange * 30, posrange * 30),
                          ofRandom(-posrange * 10, posrange * 10),
                          ofRandom(-posrange * 100, -posrange * 10));
    float hp = ofRandom(100, 500);
    float attack = ofRandom(100, 300);
    Color color = Color(static_cast<int>(ofRandom(0, 3)));
    EnemyType type = EnemyType(static_cast<int>(ofRandom(0, 5)));
    enemys_.push_back(Enemy(pos, hp, attack, color, type));
  }
}

void EnemyCloud::Update() {
  auto itr = enemys_.begin();
  while (itr != enemys_.end()) {
    if (!(*itr).isalive_) {
      itr = enemys_.erase(itr);
      number_ -= 1;
      printf("kill enemy\n");
      Init(1);
    } else {
      itr++;
    }
  }
  for (auto&& enemy : enemys_) {
    enemy.SetPosition(enemy.GetPosition() + ofVec3f(0, 0, 50));
    enemy.Update();
  }
}

void EnemyCloud::Draw() {
  for (auto&& enemy : enemys_) {
    enemy.Draw();
  }
}

std::vector<ColliderObject*> EnemyCloud::GetObjectsPtr() {
  std::vector<ColliderObject*> enemyrefs;
  for (auto&& enemy : enemys_) {
    enemyrefs.push_back(&enemy);
  }
  return enemyrefs;
}

std::vector<ColliderObject*> EnemyCloud::GetAllBulletsPtr() {
  std::vector<ColliderObject*> bulletrefs;
  for (auto&& enemy : enemys_) {
    for (auto&& bullet : enemy.GetObjectsPtr()) {
      bulletrefs.push_back(bullet);
    }
  }
  return bulletrefs;
}

EnemyCloud::~EnemyCloud() {}