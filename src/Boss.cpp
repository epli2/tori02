#include "Boss.h"

Boss::Boss() : Boss(ofVec3f(0, -500, -1500), GREEN, 500) {}

Boss::Boss(ofVec3f _position, Color _color, float _radius)
  : ColliderObject(_position, true, _color, CIRCLE, _radius) {
  body_ = ModelInit(modelpath_body_);
  body_.playAllAnimations();
  body_atk1_ = ModelInit(modelpath_body_atk1_);
  body_atk2_ = ModelInit(modelpath_body_atk2_);
  body_damage_ = ModelInit(modelpath_body_damage_);
  bossstatus_ = NORMAL;
  bodyptr_ = &body_;

  for (int i = 0; i < NUM; i++) {
    freq_[i] = ofRandom(4.0, 10.0);
  }
  shader_.load("", shaderpath_);
  starttime_ = ofGetElapsedTimef();
}

void Boss::Update() {
  if (bodyptr_->getAnimation(0).isFinished()) {
    int rnd = int(ofRandom(40, 100));
    printf("rnd = %d\n", rnd);
    if (rnd < 50) {
      bossstatus_ = NORMAL;
      bodyptr_ = &body_;
      bodyptr_->resetAllAnimations();
      bodyptr_->playAllAnimations();
    }
    else if (rnd >= 50 && rnd < 70) {
      bossstatus_ = FIRE;
      bodyptr_ = &body_atk2_;
      bodyptr_->resetAllAnimations();
      bodyptr_->playAllAnimations();
      firetime_ = ofGetElapsedTimef();
    }
    else if (rnd >= 70 && rnd < 80) {
      bossstatus_ = NORMAL;
      bodyptr_ = &body_;
      bodyptr_->resetAllAnimations();
      bodyptr_->playAllAnimations();
      ChangeColor();
      printf("Boss: change color\n");
    }
    else if (rnd >= 80 && rnd < 90) {
      bossstatus_ = PUT;
      bodyptr_ = &body_atk2_;
      bodyptr_->resetAllAnimations();
      bodyptr_->playAllAnimations();
      firetime_ = ofGetElapsedTimef();
    }
    else if (rnd >= 90) {
      bossstatus_ = PUNCH;
      bodyptr_ = &body_atk1_;
      bodyptr_->resetAllAnimations();
      bodyptr_->playAllAnimations();
      printf("Boss: punch\n");
    }
    printf("Boss: animationcount = %d\n", bodyptr_->getAnimationCount());
  }
  UpdateBullets();
  UpdateChildren();

  float nowtime = ofGetElapsedTimef();
  if (bossstatus_ == FIRE && nowtime - firetime_ > 1) {
    Fire();
    printf("Boss: fire\n");
    firetime_ = nowtime;
  }
  if (bossstatus_ == PUT && nowtime - firetime_ > 1 && enemyclouds_.size() * 2 < NCHILDREN) {
    enemyclouds_.push_back(EnemyCloud(2, false, false, ofVec3f(position_.x + ofGetWidth(), position_.y + ofGetHeight(), -position_.z - 100),
      ofVec3f(position_.x + ofGetWidth(), position_.y + ofGetHeight(), -position_.z + 100)));
    printf("Boss: put children\n");
    firetime_ = nowtime;
  }

  bodyptr_->update();
  wingmesh_ = bodyptr_->getCurrentAnimatedMesh(1);
}

void Boss::UpdateBullets() {
  auto itr = bullets_.begin();
  while (itr != bullets_.end()) {
    if (!(*itr).isalive_ || (*itr).IsDie()) {
      itr = bullets_.erase(itr);
      printf("BossBullet: die\n");
    }
    else {
      itr++;
    }
  }
  for (auto&& bullet : bullets_) {
    bullet.Update();
  }
}

void Boss::UpdateChildren() {
  for (auto&& enemycloud : enemyclouds_) {
    enemycloud.Update();
  }
}

void Boss::Draw() {
  ofColor rgbcolor;
  switch (color_) {
  case RED:
    rgbcolor = ofColor(232, 60, 55);
    break;
  case GREEN:
    rgbcolor = ofColor(72, 232, 124);
    break;
  case BLUE:
    rgbcolor = ofColor(53, 61, 255);
    break;
  }
  shader_.begin();
  shader_.setUniform1f("u_time", ofGetElapsedTimef());
  shader_.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
  shader_.setUniform3f("u_color", rgbcolor.r / 255.0, rgbcolor.g / 255.0, rgbcolor.b / 255.0);
  shader_.setUniform1fv("freq", freq_, NUM);
  ofPushMatrix();
  ofTranslate(bodyptr_->getPosition().x, bodyptr_->getPosition().y, bodyptr_->getPosition().z);
  ofTranslate(-bodyptr_->getPosition().x, -bodyptr_->getPosition().y, -bodyptr_->getPosition().z);
  ofxAssimpMeshHelper & meshHelper = bodyptr_->getMeshHelper(1);
  ofMultMatrix(bodyptr_->getModelMatrix());
  ofMultMatrix(meshHelper.matrix);
  wingmesh_.drawFaces();
  ofPopMatrix();
  shader_.end();
  bodyptr_->setPosition(position_.x, position_.y, position_.z);
  bodyptr_->drawFaces();
  DrawBullet();
  DrawChildren();
}

void Boss::DrawBullet() {
  for (auto&& bullet : bullets_) {
    bullet.Draw();
  }
}

void Boss::DrawChildren() {
  for (auto&& enemycloud : enemyclouds_) {
    enemycloud.Draw();
  }
}

void Boss::ChangeColor() {
  color_ = Color((color_ + 1) % 3);
}

void Boss::Fire() {
  bullets_.push_back(Bullet(position_ + ofVec3f(0, 50 * ofGetHeight() / 90, 0) + ofRandom(-100, 100), 100000, color_, ofVec3f(0, 0, 10)));
  bullets_.push_back(Bullet(position_ + ofVec3f(0, 50 * ofGetHeight() / 90, 0) + ofRandom(-100, 100), 100000, color_, ofVec3f(0, 0, 10)));
  bullets_.push_back(Bullet(position_ + ofVec3f(0, 50 * ofGetHeight() / 90, 0) + ofRandom(-100, 100), 100000, color_, ofVec3f(0, 0, 10)));
}

void Boss::Hit() {
  printf("Boss: Hit!\n");
}

ofxAssimpModelLoader Boss::ModelInit(std::string modelpath) {
  ofxAssimpModelLoader body;
  body.loadModel(modelpath);
  body.setScaleNormalization(false);
  body.setScale(radius_ * 20, radius_ * 20, radius_ * 20);
  body.setRotation(2, 180, 0, 0, 1);
  return body;
}

std::vector<ColliderObject*> Boss::GetBulletsPtr() {
  std::vector<ColliderObject*> enemybulletrefs;
  for (auto&& bullet : bullets_) {
    enemybulletrefs.push_back(&bullet);
  }
  for (auto&& enemycloud : enemyclouds_) {
    for (auto&& bullet : enemycloud.GetAllBulletsPtr()) {
      enemybulletrefs.push_back(bullet);
    }
  }
  return enemybulletrefs;
}

std::vector<ColliderObject*> Boss::GetEnemysPtr() {
  std::vector<ColliderObject*> enemyrefs;
  for (auto&& enemycloud : enemyclouds_) {
    for (auto&& enemy : enemycloud.GetObjectsPtr()) {
      enemyrefs.push_back(enemy);
    }
  }
  return enemyrefs;
}

Boss::~Boss() {}