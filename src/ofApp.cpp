#include "ofApp.h"

void ofApp::setup() {
#ifdef USE_DIMENCO_OPENGL_INTERFACE
  dimencoInit();
  dimencoInitState();
#endif

  ofSetFrameRate(60);
  ofSetVerticalSync(true);
  // ofSetLogLevel(OF_LOG_VERBOSE);
}

void ofApp::update() {
  buttlescene.Update();
}

void ofApp::draw() {
#ifdef USE_DIMENCO_OPENGL_INTERFACE
  dimencoSetBackgroundState();
#endif
  buttlescene.Draw();
#ifdef USE_DIMENCO_OPENGL_INTERFACE
  dimencoSetZBufState();
#endif
}

void ofApp::keyPressed(int key) {
  if (key == 'q') {
    OF_EXIT_APP(0);
  }
  buttlescene.KeyPressed(key);
}

void ofApp::exit() {}
