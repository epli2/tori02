#pragma once

#include "ofMain.h"
#include "Common.h"
#include "ColliderObject.h"

class Player : public ColliderObject {
public:
  float hp_;
  Player()
    : Player(ofVec3f(-ofGetWidth() / 2, ofGetHeight() / 2, 0), GREEN, 1000) {};
  Player(ofVec3f _position, Color _color, float _hp)
    : ColliderObject(_position, true, _color, BOX, ofGetWidth(), ofGetHeight()), hp_(_hp) {};
  void Hit() {
    hp_ -= 5;
    printf("Player hit!\n");
  };
};