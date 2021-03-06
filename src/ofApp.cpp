#include "ofApp.h"

void ofApp::setup() {
#ifdef USE_DIMENCO_OPENGL_INTERFACE
  dimencoInit();
  dimencoInitState();
#endif
  ofSetWindowTitle("Kalaster");
  ofSetFrameRate(60);
  ofSetVerticalSync(true);
  // ofSetLogLevel(OF_LOG_VERBOSE);
  nowscene = new StartScene();
}

void ofApp::update() {
  nowscene->Update();
  if (nowscene->isgameover_) {
    delete nowscene;
    nowscene = new DeadScene();
  }
  if (nowscene->isgameclear_) {
    delete nowscene;
    nowscene = new EndScene();
  }
  if (nowscene->isend_) {
    nextScene();
  }
}

void ofApp::draw() {
#ifdef USE_DIMENCO_OPENGL_INTERFACE
  dimencoSetBackgroundState();
#endif
  nowscene->Draw();
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
  nowscene->KeyPressed(key);
}

void ofApp::keyReleased(int key){
  nowscene->KeyReleased(key);
}

void ofApp::exit() {}

void ofApp::nextScene() {
  if (nowscene->GetName() == "start") {
    delete nowscene;
    nowscene = new TitleScene();
  }
  else if (nowscene->GetName() == "title") {
    delete nowscene;
    nowscene = new ButtleScene();
  }
  else if (nowscene->GetName() == "buttle") {
    delete nowscene;
    nowscene = new BossScene();
  }
  else if (nowscene->GetName() == "boss") {
    delete nowscene;
    nowscene = new EndScene();
  }
  else if (nowscene->GetName() == "end") {
    delete nowscene;
    nowscene = new StartScene();
  }
  else if (nowscene->GetName() == "dead") {
    delete nowscene;
    nowscene = new StartScene();
  }
}