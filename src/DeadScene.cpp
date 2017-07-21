#include "DeadScene.h"

DeadScene::DeadScene() {
  name_ = "dead";
  isend_ = false;
  isgameover_ = false;
  isgameclear_ = false;
  img_gameover_.load(imgpath_gameover_);
  ofBackground(0, 0, 0);
}

void DeadScene::Update() {}

void DeadScene::Draw() {
  img_gameover_.draw(ofGetWidth() / 2 - img_gameover_.getWidth() / 2, ofGetHeight() / 2 - img_gameover_.getHeight() / 2);
}

void DeadScene::KeyPressed(int key) {}

DeadScene::~DeadScene() {}