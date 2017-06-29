#pragma once

#include "ofMain.h"
#include "Common.h"
// #include "ofxGui.h"


class GameUI {
private:
  int sp_;
  Color color_;
  ofColor ccolor_;
  ofTrueTypeFont verdana;

public:
  GameUI();
  ~GameUI();

  void Setup();
  void Update();
  void Draw();
  void SetColor(Color _color);

  // gui
  /*
  ofxPanel gui1;
  ofxIntSlider hpbar;
  ofxVec2Slider position;
  ofxColorSlider barcolor;
  */
};