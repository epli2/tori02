#include "EnemyCloud.h"

EnemyCloud::EnemyCloud() : EnemyCloud(10) {}

EnemyCloud::EnemyCloud(int _number) : number_(_number) {
  int posrange = number_ * 10;
  for (int i = 0; i < number_; i++) {
    ofVec3f pos = ofVec3f(ofRandom(-posrange * 5, posrange * 5),
                          ofRandom(-posrange * 5, posrange * 5),
                          ofRandom(-posrange * 100, -posrange * 10));
    float hp = ofRandom(100, 500);
    float attack = ofRandom(100, 300);
    Color color = Color(static_cast<int>(ofRandom(0, 3)));
    enemys_.push_back(Enemy(pos, hp, attack, color));
  }
}

void EnemyCloud::Update() {

}

void EnemyCloud::Draw() {
  for (auto enemy : enemys_) {
    enemy.Draw();
  }
}

EnemyCloud::~EnemyCloud() {}