#pragma once

#include "ofMain.h"
#include "Scene.h"

class DeadScene : public Scene {
public:
  DeadScene();
  ~DeadScene();
  void Draw();
  void Update();
  void KeyPressed(int _key);
  void KeyReleased(int _key){};

private:
  ofTrueTypeFont verdana;
};