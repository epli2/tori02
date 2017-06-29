#include "ofApp.h"

void ofApp::setup() {
#ifdef USE_DIMENCO_OPENGL_INTERFACE
  dimencoInit();
  dimencoInitState();
#endif

  ofSetFrameRate(60);
  ofSetVerticalSync(true);
  // ofSetLogLevel(OF_LOG_VERBOSE);

  leap.open();
  leap.setReceiveBackgroundFrames(true);
  cam.setOrientation(ofPoint(0, 0, 0));
  light.setPosition(1000, 1000, 2000);

  backgroundshader.load("", "shader/shader_background.frag");
  collision_bullets_and_enemys.Init(weapon.GetObjectsPtr(), enemycloud.GetObjectsPtr());
  pv.push_back(&player);
  collision_bullets_and_player.Init(enemycloud.GetAllBulletsPtr(), pv);
  gameui.Setup();

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glEnable(GL_LIGHTING);
  light.enable();
}

void ofApp::update() {
  fingersFound.clear();
  simpleHands = leap.getSimpleHands();

  if (leap.isFrameNew() && simpleHands.size()) {
    leap.setMappingX(-230, 230, -ofGetWidth() / 2, ofGetWidth() / 2);
    leap.setMappingY(90, 490, -ofGetHeight() / 2, ofGetHeight() / 2);
    leap.setMappingZ(-150, 150, -200, 200);
  }
  leap.markFrameAsOld();
  collision_bullets_and_enemys.Update(weapon.GetObjectsPtr(), enemycloud.GetObjectsPtr());
  player.SetColor(color);
  collision_bullets_and_player.Update(enemycloud.GetAllBulletsPtr(), pv);
  enemycloud.Update();
  weapon.Update();
}

void ofApp::draw() {
  // ofBackgroundGradient(ofColor(90, 90, 90), ofColor(30, 30, 30),
  //                      OF_GRADIENT_BAR);
  // glPushAttrib(GL_ENABLE_BIT);
#ifdef USE_DIMENCO_OPENGL_INTERFACE
  dimencoSetBackgroundState();
#endif
  cam.begin(ofRectangle(0, 0, ofGetWidth(), ofGetHeight()));
  ofSetColor(200, 0, 0);
  ofDrawBitmapString("Leap Connected? " + ofToString(leap.isConnected()),
                     -ofGetWidth() / 2 - 200, -ofGetHeight() / 2);
  ofDrawBitmapString(ofToString(ofGetFrameRate()), ofGetWidth() / 2 + 100,
                     -ofGetHeight() / 2);

  // ofPushMatrix();
  // ofRotate(90, 0, 0, 1);
  // ofSetColor(20);
  // ofDrawGridPlane(800, 20, false);
  // ofPopMatrix();

  backgroundshader.begin();
  backgroundshader.setUniform1f("time", ofGetElapsedTimef());
  backgroundshader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
  ofDrawPlane(0, 0, -5000, ofGetWidth() * 100, ofGetHeight() * 100);
  backgroundshader.end();

  for (auto simpleHand : simpleHands) {
    ofPoint handPos = simpleHand.handPos;
    weapon.SetPosition(handPos);
    weapon.SetColor(color);
    weapon.DrawGun();
  }
  weapon.DrawBullet();
  enemycloud.Draw();
  glPopAttrib();
  cam.end();
  gameui.SetColor(color);
  gameui.Draw();
#ifdef USE_DIMENCO_OPENGL_INTERFACE
  dimencoSetZBufState();
#endif
}

void ofApp::keyPressed(int key) {
  if (key == 'q') {
    OF_EXIT_APP(0);
  }
  if (key == 'f' && simpleHands.size()) {
    weapon.SetColor(color);
    weapon.Fire();
    printf("fire\n");
  }
  if (key == 'c') {
    ChangeColor();
    printf("%d\n", color);
  }
}

void ofApp::exit() {
  leap.close();
}

void ofApp::ChangeColor() {
  color = Color((color + 1) % 3);
}