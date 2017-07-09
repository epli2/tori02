#pragma once

#include "ofMain.h"
// #define USE_DIMENCO_OPENGL_INTERFACE

#ifdef USE_DIMENCO_OPENGL_INTERFACE
  #include "dimenco.h"
#endif
#include "Scene.h"
#include "StartScene.h"
#include "TitleScene.h"
#include "ButtleScene.h"
#include "EndScene.h"

class ofApp : public ofBaseApp {
private:
  Scene* nowscene;

  void nextScene();

public:
  void setup();
  void update();
  void draw();
  void keyPressed(int key);
  void keyReleased(int key);
  void exit();
};