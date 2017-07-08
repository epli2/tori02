#pragma once

#include "ofMain.h"
// #define USE_DIMENCO_OPENGL_INTERFACE

#ifdef USE_DIMENCO_OPENGL_INTERFACE
  #include "dimenco.h"
#endif
#include "ButtleScene.h"

class ofApp : public ofBaseApp {
private:
  ButtleScene buttlescene;

public:
  void setup();
  void update();
  void draw();
  void keyPressed(int key);
  void exit();
};