#include "animatedSprite.h"
#include "graphics.h"
#include<iostream>

AnimatedSprite::AnimatedSprite() {};

AnimatedSprite::AnimatedSprite(Graphics& graphics, std::string filepath, int sourceX, int sourceY, int width, int height,float posX,
     float posY, float timeToUpdate) :

     Sprite(graphics, filepath, sourceX, sourceY, width , height, posX, posY),
     _frameIndex(0),
     _timeToUpdate(timeToUpdate),
     _visible(true),
     _currentAnimationOnce(false),
     _currentAnimation("") {}


void AnimatedSprite::addAnimation(int frames, int x, int y, std::string name, int width, int height, Vec2 offset) {
  std::vector<SDL_Rect> rectangles;
  for(int i = 0; i < frames; ++i) {
    SDL_Rect rect = { (i + x)*width, y, width, height };
    rectangles.emplace_back(rect);
  }
  _animations.insert(std::pair<std::string, std::vector<SDL_Rect>>(name,rectangles));
  _offsets.insert(std::pair<std::string, Vec2>(name, offset));

}

void AnimatedSprite::resetAnimation() {
  _animations.clear();
  _offsets.clear();
}

void AnimatedSprite::playAnimation(std::string animation, bool once) {
  _currentAnimationOnce = once;
  if(_currentAnimation != animation) {
    _currentAnimation = animation;
  }
  _frameIndex = 0;
}

void AnimatedSprite::setVisible(bool visible) {
  _visible = visible;
}


void AnimatedSprite::stopAnimation() {
  _frameIndex = 0;
  animationDone(_currentAnimation);
}


void AnimatedSprite::update(float elapsedTime) {
  Sprite::update();
  _timeElapsed += elapsedTime;

 if(_timeElapsed > _timeToUpdate) {
   _timeElapsed -= _timeToUpdate;
     _frameIndex = (_frameIndex + 1)%_animations[_currentAnimation].size();    // if we are on the last animation we would go to first
  }
}

void AnimatedSprite::draw(Graphics& graphics, int x, int y) {

  if(_visible) {
    SDL_Rect destRect;
    destRect.x = x + _offsets[_currentAnimation].x;
    destRect.y = y + _offsets[_currentAnimation].y;
    destRect.w = _sourceRect.w * globals::SPRITE_SCALE;
    destRect.h = _sourceRect.h * globals::SPRITE_SCALE;

    SDL_Rect _sourceRect = _animations[_currentAnimation][_frameIndex];
    graphics.blitSurface(_spriteSheet, &_sourceRect, &destRect);

  }
}
void AnimatedSprite::animationDone(std::string currentAnimation) {

}

void AnimatedSprite::setupAnimations() {
  addAnimation(3, 0, 0, "GoLeft", 16, 16, Vec2(0,0));
}
