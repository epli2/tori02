#include "ofApp.h"

void ofApp::setup() {
#ifdef USE_DIMENCO_OPENGL_INTERFACE
  dimencoInit();
  dimencoInitState();
#endif

  ofSetFrameRate(60);
  ofSetVerticalSync(true);
  // ofSetLogLevel(OF_LOG_VERBOSE);
  scene = TITLE;
}

void ofApp::update() {
  switch (scene)
  {
  case TITLE:
    titlescene.Update();
    break;
  case BUTTLE:
    buttlescene.Update();
    break;
  default:
    break;
  }
}

void ofApp::draw() {
#ifdef USE_DIMENCO_OPENGL_INTERFACE
  dimencoSetBackgroundState();
#endif
  switch (scene)
  {
  case TITLE:
    titlescene.Draw();
    break;
  case BUTTLE:
    buttlescene.Draw();
    break;
  default:
    break;
  }
#ifdef USE_DIMENCO_OPENGL_INTERFACE
  dimencoSetZBufState();
#endif
}

void ofApp::keyPressed(int key) {
  if (key == 'q') {
    OF_EXIT_APP(0);
  }
  if (key == 's') {
    nextScene();
  }
  switch (scene)
  {
  case TITLE:
    titlescene.KeyPressed(key);
    break;
  case BUTTLE:
    buttlescene.KeyPressed(key);
    break;
  default:
    break;
  }
}

void ofApp::exit() {}

void ofApp::nextScene() {
  scene = BUTTLE;
}