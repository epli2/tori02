#include "MenuButton.h"

MenuButton::MenuButton(ofVec3f _position, Color _color, float _width, float _height, std::string _modelpath)
    : ColliderObject(_position, true, _color, BOX, _width, _height) {
  panel_.loadModel(_modelpath);
  panel_.setScaleNormalization(false);
  panel_.setScale(220, 220, 1);
  panel_.enableMaterials();
}

void MenuButton::Draw() {
  panel_.setPosition(position_.x, position_.y, position_.z);
  panel_.drawFaces();
}

MenuButton::~MenuButton() {}