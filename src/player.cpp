#include "player.h"
#include "graphics.h"

namespace physics {
  const float VELOCITY = 0.15;
  const float MAX_ACCELERATION = 0.8;
  const float ACCELERATION = 0.002;
}

Player::Player() {}

Player::Player(Graphics& graphics, Vec2 spawnPoint):
  AnimatedSprite(graphics, "../Media/sprites/MyChar.png", 0, 0, 16, 16, spawnPoint.x, spawnPoint.y, 100),
  _dx(0),
  _dy(0),
  _grounded(false)
{
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

const float Player::getX() const {
  return _x;
}
const float Player::getY() const {
  return _y;
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


void Player::handleTileCollisions(std::vector<Rectangle> &others) {
	//Figure out what side the collision happened on and move the player accordingly
	for (unsigned long   int i = 0; i < others.size(); i++) {
		sides::Side collisionSide = Sprite::getCollisionSide(others.at(i));
		if (collisionSide != sides::NONE) {
			switch (collisionSide) {
      case sides::NONE:
        break;
			case sides::TOP:
				_dy = 0;
				_y = others.at(i).getBottom() + 1;
				if (_grounded) {
					_dx = 0;
					_x -= _facing == Right ? 1.0f : -1.0f;
				}
				break;
			case sides::BOTTOM:
				_y = others.at(i).getTop() - _boundingBox.getHeight() - 1;
				_dy = 0;
				_grounded = true;
				break;
			case sides::LEFT:
				_x = others.at(i).getRight() + 1;
				break;
			case sides::RIGHT:
				_x = others.at(i).getLeft() - _boundingBox.getWidth() - 1;
				break;
			}

		}
	}
}
