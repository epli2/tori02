#pragma once

#include "ofMain.h"
#include "Common.h"
#include "ColliderObject.h"

class Player : public ColliderObject {
public:
  Player()
    : Player(ofVec3f(-ofGetWidth() / 2, ofGetHeight() / 2, 0), GREEN) {};
  Player(ofVec3f _position, Color _color)
    : ColliderObject(_position, true, _color, BOX, ofGetWidth(), ofGetHeight()) {};
};