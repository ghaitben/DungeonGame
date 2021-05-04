#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include "sprite.h"
#include "globals.h"
#include<map>
#include<string>
#include<vector>


class AnimatedSprite : public Sprite {
public:
  AnimatedSprite();
  AnimatedSprite(Graphics& graphics, std::string filepath, int sourceX, int sourceY, int width, int height,float posX,
       float posY, float timeToUpdate);

  void playAnimation(std::string animation, bool once = false);

  void update(float elapsedTime);

  void draw(Graphics& graphics, int x, int y);

  virtual void animationDone(std::string currentAnimation) = 0;
  virtual void setupAnimations() = 0;

protected:
  std::map<std::string, std::vector<SDL_Rect> > _animations;
  std::map<std::string, Vec2> _offsets;
  int _frameIndex;
  double _timeToUpdate;
  bool _visible;
  double _timeElapsed;
  bool _currentAnimationOnce;
  std::string _currentAnimation;

  void addAnimation(int frames, int x, int y, std::string name, int width, int height, Vec2 offset);

  void resetAnimation();
  void stopAnimation();
  void setVisible(bool visible);


};



#endif
