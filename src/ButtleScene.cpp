#include "ButtleScene.h"

ButtleScene::ButtleScene() {
  name_ = "buttle";
  isend_ = false;
  isgameover_ = false;
  isgameclear_ = false;
  leap.open();
  leap.setReceiveBackgroundFrames(true);
  cam.setOrientation(ofPoint(0, 0, 0));
  light.setPosition(1000, 1000, 2000);

  backgroundshader.load("", "shader/shader_background.frag");
  collision_bullets_and_enemys.Init(weapon.GetObjectsPtr(), enemycloud.GetObjectsPtr());
  pv.push_back(&player);
  collision_bullets_and_player.Init(enemycloud.GetAllBulletsPtr(), pv);
  collision_enemys_and_player.Init(enemycloud.GetObjectsPtr(), pv);
  gameui.Setup();

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glEnable(GL_LIGHTING);
  light.enable();
  starttime_ = ofGetElapsedTimef();
}

void ButtleScene::Update() {
  float etime = ofGetElapsedTimef() - starttime_;
  if (player.hp_ <= 0) {
    isgameover_ = true;
  }
  if (etime > 120) {
    isend_ = true;
  }
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
  collision_enemys_and_player.Update(enemycloud.GetObjectsPtr(), pv);
  enemycloud.Update();
  weapon.Update();
  gameui.Update();
}

void ButtleScene::Draw() {
  backgroundshader.begin();
  backgroundshader.setUniform1f("time", ofGetElapsedTimef());
  backgroundshader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
  ofDrawPlane(0, 0, 0, ofGetWidth() * 100, ofGetHeight() * 100);
  backgroundshader.end();
  glClear(GL_DEPTH_BUFFER_BIT);

  cam.begin(ofRectangle(0, 0, ofGetWidth(), ofGetHeight()));
  ofPushStyle();
  ofSetColor(200, 0, 0);
  ofDrawBitmapString("Leap Connected? " + ofToString(leap.isConnected()),
                     -ofGetWidth() / 2 - 200, -ofGetHeight() / 2);
  ofDrawBitmapString(ofToString(ofGetFrameRate()), ofGetWidth() / 2 + 100,
                     -ofGetHeight() / 2);
  ofPopStyle();

  for (auto simpleHand : simpleHands) {
    ofPoint handPos = simpleHand.handPos;
    weapon.SetPosition(handPos);
    weapon.SetColor(color);
    weapon.DrawGun();
  }
  weapon.DrawBullet();
  enemycloud.Draw();
  cam.end();
  gameui.SetPlayerHP(player.hp_);
  gameui.SetColor(color);
  gameui.Draw();
}

void ButtleScene::KeyPressed(int _key) {
  if (_key == 'f' && simpleHands.size()) {
    weapon.SetColor(color);
    switch (color)
    {
    case RED:
      if (20 - gameui.uibar_decr_.x > 0) {
        weapon.Fire();
        gameui.uibar_decr_.x += 1;
        printf("fire\n");
      }
      break;
    case GREEN:
      if (20 - gameui.uibar_decr_.y > 0) {
        weapon.Fire();
        gameui.uibar_decr_.y += 1;
        printf("fire\n");
      }
      break;
    case BLUE:
      if (20 - gameui.uibar_decr_.z > 0) {
        weapon.Fire();
        gameui.uibar_decr_.z += 1;
        printf("fire\n");
      }
      break;
    default:
      break;
    }
  }
  if (_key == 'c') {
    ChangeColor();
    printf("%d\n", color);
  }
}

void ButtleScene::ChangeColor() {
  color = Color((color + 1) % 3);
}