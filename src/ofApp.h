#pragma once

#include "ofMain.h"
// #define USE_DIMENCO_OPENGL_INTERFACE

#ifdef USE_DIMENCO_OPENGL_INTERFACE
  #include "dimenco.h"
#endif
#include "TitleScene.h"
#include "ButtleScene.h"

class ofApp : public ofBaseApp {
private:
  enum Scene { TITLE = 0, BUTTLE = 1 };
  Scene scene;
  TitleScene titlescene;
  ButtleScene buttlescene;

  void nextScene();

public:
  void setup();
  void update();
  void draw();
  void keyPressed(int key);
  void exit();
};