#include "player.h"
#include "graphics.h"
#include<iostream>

namespace physics {
  const float VELOCITY = 0.15;
  const float MAX_ACCELERATION = 0.8;
  const float ACCELERATION = 0.002;
  const float JUMP_ACCELERATION = 0.7;
}

Player::Player() {}

Player::Player(Graphics& graphics, Vec2 spawnPoint):
  AnimatedSprite(graphics, "../Media/sprites/MyChar.png", 0, 0, 16, 16, spawnPoint.x, spawnPoint.y, 100),
  _dx(0),
  _dy(0),
  _grounded(false),
  _maxHealth(3),
  _currentHealth(3)
{
  graphics.loadImage("../Media/sprites/MyChar.png");
  setupAnimations();
  playAnimation("GoRight");
}

void Player::setupAnimations() {
  addAnimation(1, 3, 0, "LookUpLeft", 16, 16, Vec2(0,0));
  addAnimation(1, 3, 16, "LookUpRight", 16, 16, Vec2(0,0));
  addAnimation(1, 0, 0, "FaceLeft", 16, 16, Vec2(0,0));         //stay still facing left
  addAnimation(1, 0, 16, "FaceRight", 16, 16, Vec2(0,0));       //stay still facing right
  addAnimation(3, 0, 0, "GoLeft", 16, 16, Vec2(0,0));           //run left
  addAnimation(3, 0, 16, "GoRight", 16, 16, Vec2(0,0));          //run right
  addAnimation(3, 3, 0, "GoLeftUp", 16, 16, Vec2(0,0));
  addAnimation(3, 3, 16, "GoRightUp", 16, 16, Vec2(0,0));
  addAnimation(1, 6, 0, "LookDownLeft", 16, 16, Vec2(0,0));
  addAnimation(1, 6, 16, "LookDownRight", 16, 16, Vec2(0,0));
  addAnimation(1, 7, 0, "LookBackwardsLeft", 16, 16, Vec2(0,0));
  addAnimation(1, 7, 16, "LookBackwardsRight", 16, 16, Vec2(0,0));
}

void Player::animationDone(std::string currentAnimation) {}


void Player::draw(Graphics& graphics) {
  AnimatedSprite::draw(graphics, _x, _y);
}

void Player::goLeft() {
  if(_lookingDown && _grounded) {
    return;
  }
  _dx = -physics::VELOCITY;
  playAnimation(_lookingUp == true ? "GoLeftUp" : "GoLeft");
  _facing = Left;
}

void Player::goRight() {
  if(_lookingDown && _grounded) {
    return;
  }
  _dx = physics::VELOCITY;
  playAnimation(_lookingUp == true ? "GoRightUp" : "GoRight");         // play the animation once to just change direction
  _facing = Right;
}

void Player::stop(){
  _dx = 0;
  if(_lookingUp) {
    playAnimation(_facing == Right ? "LookUpRight" : "LookUpLeft");
  }
  else if(!_lookingUp && !_lookingDown) {
    playAnimation(_facing == Right ? "FaceRight" : "FaceLeft");
  }


}

void Player::lookUp() {
  _lookingUp = true;

  if(_dx == 0) {
    playAnimation(_facing == Right ? "LookUpRight" : "LookUpLeft");
  }
  else {
    playAnimation(_facing == Right ? "GoRightUp" : "GoLeftUp");
  }
}
//problem when I'm holding a key say Right and I press the jump for example the key I had pressed is not working anymore
void Player::stopLookingUp() {
  _lookingUp = false;
}

void Player::lookDown() {
  _lookingDown = true;
  if(_grounded) {       //need to interact
    playAnimation(_facing == Right ? "LookBackwardsRight" : "LookBackwardsLeft");
  }
  else {
    playAnimation(_facing == Right ? "LookDownRight" : "LookDownLeft");
  }
}

void Player::stopLookingDown() {
  _lookingDown = false;
}

void Player::jump() {
  if(_grounded && !_lookingDown) {
    _dy = 0;
    _dy -= physics::JUMP_ACCELERATION;
    _grounded = false;
  }
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
