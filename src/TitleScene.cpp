#include "TitleScene.h"

TitleScene::TitleScene() {
  name_ = "title";
  isend_ = false;
  isgameover_ = false;
  isgameclear_ = false;
  leap_.open();
  leap_.setReceiveBackgroundFrames(true);
  backgroundshader_.load("", shaderpath_background_);
  cam_.setOrientation(ofPoint(0, 0, 0));
  light_.setPosition(1000, 1000, 2000);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glEnable(GL_LIGHTING);
  light_.enable();
  weapon_.SetColor(color_);
  bgm_.loadSound(bgmpath_);
  bgm_.setVolume(0.5f);
  bgm_.play();
}

void TitleScene::Update() {
  fingerType fingerTypes[] = { THUMB, INDEX, MIDDLE, RING, PINKY };
  fingersFound_.clear();
  simpleHands_ = leap_.getSimpleHands();
  double middleDistanceX0;
  double middleDistanceY0;
  double middleDistanceZ0;
  double middleDistanceX1;
  double middleDistanceY1;
  double middleDistanceZ1;
  double middleDistanceSum0 = 20000;
  double middleDistanceSum1 = 20000;

  if (leap_.isFrameNew() && simpleHands_.size()) {
    leap_.setMappingX(-230, 230, -ofGetWidth() / 2, ofGetWidth() / 2);
    leap_.setMappingY(90, 490, -ofGetHeight() / 2, ofGetHeight() / 2);
    leap_.setMappingZ(-150, 150, -200, 200);
    middleDistanceX0 =
      simpleHands_[0].fingers[MIDDLE].tip.x - simpleHands_[0].handPos.x;
    middleDistanceY0 =
      simpleHands_[0].fingers[MIDDLE].tip.y - simpleHands_[0].handPos.y;
    middleDistanceZ0 =
      simpleHands_[0].fingers[MIDDLE].tip.z - simpleHands_[0].handPos.z;
    middleDistanceSum0 = middleDistanceX0 * middleDistanceX0 +
      middleDistanceY0 * middleDistanceY0 +
      middleDistanceZ0 * middleDistanceZ0;
    // printf("%d", simpleHands.size());
    if (simpleHands_.size() == 2) {
      // printf("!!\n");
      middleDistanceX1 =
        simpleHands_[1].fingers[MIDDLE].tip.x - simpleHands_[1].handPos.x;
      middleDistanceY1 =
        simpleHands_[1].fingers[MIDDLE].tip.y - simpleHands_[1].handPos.y;
      middleDistanceZ1 =
        simpleHands_[1].fingers[MIDDLE].tip.z - simpleHands_[1].handPos.z;
      middleDistanceSum1 = middleDistanceX1 * middleDistanceX1 +
        middleDistanceY1 * middleDistanceY1 +
        middleDistanceZ1 * middleDistanceZ1;
      if (middleDistanceSum1 > 10000) {
        // printf("middleDistance1\n");
        ChangeColor();
        // printf("%d\n", color);
      }
    }
  }
  leap_.markFrameAsOld();
  weapon_.Update();
  if (/*middleDistanceSum0 < 10000 && */
      simpleHands_.size() &&
      ofGetElapsedTimef() - prevfiretime_ > 0.1) {
    weapon_.SetColor(color_);
    weapon_.Fire();
    prevfiretime_ = ofGetElapsedTimef();
    // printf("fire\n");
  }
}

void TitleScene::Draw() {
  backgroundshader_.begin();
  backgroundshader_.setUniform1f("time", ofGetElapsedTimef());
  backgroundshader_.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
  ofDrawPlane(0, 0, 0, ofGetWidth() * 100, ofGetHeight() * 100);
  backgroundshader_.end();
  glClear(GL_DEPTH_BUFFER_BIT);

  cam_.begin(ofRectangle(0, 0, ofGetWidth(), ofGetHeight()));
  for (auto&& simpleHand : simpleHands_) {
    ofPoint handPos = simpleHand.handPos;
    weapon_.SetPosition(simpleHands_[0].handPos);
    // weapon.SetRotation(0, 45, 0, 1, 0);
    double citay = atan((simpleHands_[0].handPos.x -
                         simpleHands_[0].fingers[THUMB].tip.x) /
                        (simpleHands_[0].handPos.y -
                         simpleHands_[0].fingers[THUMB].tip.y));
    double citaz = atan((simpleHands_[0].fingers[INDEX].mcp.z -
                         simpleHands_[0].fingers[INDEX].tip.z) /
                        (simpleHands_[0].fingers[INDEX].tip.x -
                         simpleHands_[0].fingers[INDEX].mcp.x));
    // printf("mcp:%f\n", simpleHands[0].fingers[INDEX].tip.x);
    // printf("tip:%f\n", simpleHands[0].fingers[INDEX].tip.x -
    // simpleHands[0].fingers[INDEX].mcp.x);
    // printf("%f\n", citay * 100);
    // printf("%f\n", citaz * 100);
    // weapon.SetRotation(0, 180, 1, -(citay * 100) / 180, 0);
    weapon_.SetRotation(0, 180, 1, 0, (citaz * 100) / 180);
    weapon_.SetColor(color_);
    weapon_.DrawGun();
  }
  weapon_.DrawBullet();
  cam_.end();
}

void TitleScene::KeyPressed(int _key) {
  if (_key == 'f' && simpleHands_.size()) {
    weapon_.Fire();
  }
  if (_key == 'c') {
    ChangeColor();
  }
}

void TitleScene::ChangeColor() {
  if (++i % 50 == 0) {
    color_ = Color((color_ + 1) % 3);
  }
}