#include "EndScene.h"

EndScene::EndScene() {
  name_ = "end";
  isend_ = false;
  isgameover_ = false;
  isgameclear_ = false;
  ofTrueTypeFont::setGlobalDpi(72);
  font_.load("Verdana.ttf", 30);
  font_.setLineHeight(24);
  font_.setLetterSpacing(1.0);
  xml_names_.load("names.xml");

  img_tori_.load(imgpath_tori_);
  img_title_.load(imgpath_title_);
  img_title_.resize(img_title_.getWidth() / 2.5, img_title_.getHeight() / 2.5);
  ofBackground(0, 0, 0);
  starttime_ = ofGetElapsedTimef();
  speed_ = 1;
  bgm_.loadSound(bgmpath_);
  bgm_.setVolume(0.5f);
  bgm_.play();
#ifdef USE_DIMENCO_OPENGL_INTERFACE
  x = -1930; y = -810;
#endif
}

void EndScene::Update() {}

void EndScene::Draw() {
  float etime = ofGetElapsedTimef() - starttime_;
  float posY = ofGetHeight() - etime * 120 * speed_;
  int count = 0;
  if (etime > 70) {
    isend_ = true;
  }
  xml_names_.setTo("names");
  for (int i = 0; i < xml_names_.getNumChildren(); i++) {
    std::string staffname = xml_names_.getValue<std::string>("name[" + std::to_string(i) + "]");
    ofPushStyle();
    ofSetColor(255, 255, 255);
    font_.drawString(staffname, ofGetWidth() / 2 - font_.getSpaceSize() + x, posY + ofGetHeight() * count++ + y);
    ofPopStyle();
  }
  img_tori_.draw(ofGetWidth() / 2 - img_tori_.getWidth() / 2 + x, posY + ofGetHeight() * ++count + y);
  img_title_.draw(ofGetWidth() / 2 - img_title_.getWidth() / 2 + x, posY + img_tori_.getHeight() + ofGetHeight() * ++count + y);
}

void EndScene::KeyPressed(int _key) {
  if (_key == 'f') {
    speed_ = 2;
  }
}

void EndScene::KeyReleased(int _key) {
}

EndScene::~EndScene() {
  bgm_.unload();
};