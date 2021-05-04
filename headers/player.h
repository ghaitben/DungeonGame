#ifndef PLAYER_H
#define PLAYER_H
#include "globals.h"
#include "animatedSprite.h"

class Graphics;

class Player : public AnimatedSprite {
public:
  Player();
  Player(Graphics& graphics, float x, float y);

  void goLeft();        //moves my main character to the left by dx (protected variable)
  void goRight();
  void stop();                              //stop the player mouvement

  void draw(Graphics& graphics);
  void update(float elapsedTime);

  virtual void animationDone(std::string currentAnimation);
  virtual void setupAnimations();

protected:
  float _dx, _dy;
  Direction _facing;

};

#endif