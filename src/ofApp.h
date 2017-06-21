#pragma once

#include "ofMain.h"
// #define USE_DIMENCO_OPENGL_INTERFACE

#ifdef USE_DIMENCO_OPENGL_INTERFACE
  #include "dimenco.h"
#endif
#include "ofxLeapMotion2.h"
#include "Weapon.h"
#include "EnemyCloud.h"
#include "Common.h"

class ofApp : public ofBaseApp {
private:
  ofxLeapMotion leap;
  ofLight light;
  vector<ofxLeapMotionSimpleHand> simpleHands;
  Weapon weapon;
  vector<int> fingersFound;
  ofEasyCam cam;
  Color color = GREEN;
  EnemyCloud enemycloud;

  void ChangeColor();

public:
  void setup();
  void update();
  void draw();
  void keyPressed(int key);
  void exit();
};