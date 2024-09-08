#include "../headers/player.h"
#include "../headers/graphics.h"

namespace player_constants {
const float WALK_SPEED = 0.2f;
}

Player::Player() {}

Player::Player(Graphics &graphics, float x, float y)
    : AnimatedSprites(graphics, "../content/sprites/MyChar.png", 0, 0, 16, 16,
                      x, y, 100) {
  graphics.loadImage("../content/sprites/MyChar.png");

  this->setupAnimation();
  this->playAnimation("RunRight");
}

void Player::setupAnimation() {
  this->addAnimation(1, 0, 0, "IdleLeft", 16, 16, Vector2(0, 0));
  this->addAnimation(1, 0, 16, "IdleRight", 16, 16, Vector2(0, 0));
  this->addAnimation(3, 0, 0, "RunLeft", 16, 16, Vector2(0, 0));
  this->addAnimation(3, 0, 16, "RunRight", 16, 16, Vector2(0, 0));
}

void Player::moveLeft() {
  this->_dx = -player_constants::WALK_SPEED;
  this->playAnimation("RunLeft");
  this->_facing = LEFT;
}

void Player::moveRight() {
  this->_dx = player_constants::WALK_SPEED;
  this->playAnimation("RunRight");
  this->_facing = RIGHT;
}

void Player::stopMoving() {
  this->_dx = 0.0f;
  this->playAnimation(this->_facing == RIGHT ? "IdleRight" : "IdleLeft");
}

void Player::animationDone(std::string currentAnimation) {}

void Player::update(float elapsedTime) {
  this->_x += this->_dx * elapsedTime;
  AnimatedSprites::update(elapsedTime);
}

void Player::draw(Graphics &graphics) {
  AnimatedSprites::draw(graphics, this->_x, this->_y);
}
