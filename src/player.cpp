#include "player.h"
#include "graphics.h"

namespace physics {
  const float VELOCITY = 0.15;
  const float MAX_ACCELERATION = 0.8;
  const float ACCELERATION = 0.02;
}

Player::Player() {}

Player::Player(Graphics& graphics, float x, float y): AnimatedSprite(graphics, "../Media/sprites/MyChar.png", 0, 0, 16, 16, x, y, 100){

  graphics.loadImage("../Media/sprites/MyChar.png");
  setupAnimations();
  playAnimation("GoRight");
}

void Player::setupAnimations() {
  addAnimation(1, 0, 0, "FaceLeft", 16, 16, Vec2(0,0));         //stay still facing left
  addAnimation(1, 0, 16, "FaceRight", 16, 16, Vec2(0,0));       //stay still facing right
  addAnimation(3, 0, 0, "GoLeft", 16, 16, Vec2(0,0));           //run left
  addAnimation(3, 0, 16, "GoRight", 16, 16, Vec2(0,0));          //run right
}

void Player::animationDone(std::string currentAnimation) {}


void Player::draw(Graphics& graphics) {
  AnimatedSprite::draw(graphics, _x, _y);
}

void Player::goLeft() {

  _dx = -physics::VELOCITY;
  playAnimation("GoLeft");
  _facing = Left;
}

void Player::goRight() {

  _dx = physics::VELOCITY;
  playAnimation("GoRight");         // play the animation once to just change direction
  _facing = Right;
}

void Player::stop(){
  _dx = 0;
  playAnimation(_facing == Right ? "FaceRight" : "FaceLeft");
}

void Player::update(float elapsedTime) {
  //x is the player position and we increment it with dx whether we move right or left
  if(_dy <= physics::MAX_ACCELERATION) {
    _dy += physics::ACCELERATION * elapsedTime;
  }
  _x += _dx * elapsedTime;       //to adjust the speed with the frame rate
  _y += _dy * elapsedTime;
  AnimatedSprite::update(elapsedTime);
}
