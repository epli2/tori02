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
  bgm_.loadSound(bgmpath_);
  bgm_.setVolume(0.5f);
  bgm_.play();
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
  fingerType fingerTypes[] = { THUMB, INDEX, MIDDLE, RING, PINKY };
  fingersFound.clear();
  simpleHands = leap.getSimpleHands();
  double middleDistanceX0;
  double middleDistanceY0;
  double middleDistanceZ0;
  double middleDistanceX1;
  double middleDistanceY1;
  double middleDistanceZ1;
  double middleDistanceSum0 = 20000;
  double middleDistanceSum1 = 20000;

  if (leap.isFrameNew() && simpleHands.size()) {
    leap.setMappingX(-230, 230, -ofGetWidth() / 2, ofGetWidth() / 2);
    leap.setMappingY(90, 490, -ofGetHeight() / 2, ofGetHeight() / 2);
    leap.setMappingZ(-150, 150, -200, 200);
    middleDistanceX0 =
      simpleHands[0].fingers[MIDDLE].tip.x - simpleHands[0].handPos.x;
    middleDistanceY0 =
      simpleHands[0].fingers[MIDDLE].tip.y - simpleHands[0].handPos.y;
    middleDistanceZ0 =
      simpleHands[0].fingers[MIDDLE].tip.z - simpleHands[0].handPos.z;
    middleDistanceSum0 = middleDistanceX0 * middleDistanceX0 +
      middleDistanceY0 * middleDistanceY0 +
      middleDistanceZ0 * middleDistanceZ0;
    // printf("%d", simpleHands.size());
    if (simpleHands.size() == 2) {
      // printf("!!\n");
      middleDistanceX1 =
        simpleHands[1].fingers[MIDDLE].tip.x - simpleHands[1].handPos.x;
      middleDistanceY1 =
        simpleHands[1].fingers[MIDDLE].tip.y - simpleHands[1].handPos.y;
      middleDistanceZ1 =
        simpleHands[1].fingers[MIDDLE].tip.z - simpleHands[1].handPos.z;
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
  leap.markFrameAsOld();
  collision_bullets_and_enemys.Update(weapon.GetObjectsPtr(), enemycloud.GetObjectsPtr());
  player.SetColor(color);
  collision_bullets_and_player.Update(enemycloud.GetAllBulletsPtr(), pv);
  collision_enemys_and_player.Update(enemycloud.GetObjectsPtr(), pv);
  enemycloud.Update();
  weapon.Update();
  gameui.Update();
  if (/*middleDistanceSum0 < 10000 && */
      simpleHands.size() &&
      ofGetElapsedTimef() - prevfiretime_ > 0.1) {
    weapon.SetColor(color);
    WeaponFire();
    prevfiretime_ = ofGetElapsedTimef();
    // printf("fire\n");
  }
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

  for (auto&& simpleHand : simpleHands) {
    ofPoint handPos = simpleHand.handPos;
    weapon.SetPosition(simpleHands[0].handPos);
    // weapon.SetRotation(0, 45, 0, 1, 0);
    double citay = atan((simpleHands[0].handPos.x -
                         simpleHands[0].fingers[THUMB].tip.x) /
                        (simpleHands[0].handPos.y -
                         simpleHands[0].fingers[THUMB].tip.y));
    double citaz = atan((simpleHands[0].fingers[INDEX].mcp.z -
                         simpleHands[0].fingers[INDEX].tip.z) /
                        (simpleHands[0].fingers[INDEX].tip.x -
                         simpleHands[0].fingers[INDEX].mcp.x));
    // printf("mcp:%f\n", simpleHands[0].fingers[INDEX].tip.x);
    // printf("tip:%f\n", simpleHands[0].fingers[INDEX].tip.x -
    // simpleHands[0].fingers[INDEX].mcp.x);
    // printf("%f\n", citay * 100);
    // printf("%f\n", citaz * 100);
    // weapon.SetRotation(0, 180, 1, -(citay * 100) / 180, 0);
    weapon.SetRotation(0, 180, 1, 0, (citaz * 100) / 180);
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
    WeaponFire();
  }
  if (_key == 'c') {
    ChangeColor();
    printf("%d\n", color);
  }
}

void ButtleScene::ChangeColor() {
  color = Color((color + 1) % 3);
}

void ButtleScene::WeaponFire() {
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