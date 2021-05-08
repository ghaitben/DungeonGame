#ifndef PLAYER_H
#define PLAYER_H
#include "globals.h"
#include "animatedSprite.h"

class Graphics;

class Player : public AnimatedSprite {
public:
  Player();
  Player(Graphics& graphics, Vec2 spawnPoint);

  void goLeft();        //moves my main character to the left by dx (protected variable)
  void goRight();
  void lookUp();
  void stopLookingUp();
  void lookDown();
  void stopLookingDown();
  void jump();
  void stop();                              //stop the player mouvement

  void draw(Graphics& graphics);
  void update(float elapsedTime);

  virtual void animationDone(std::string currentAnimation);
  virtual void setupAnimations();

  const float getX() const;
  const float getY() const;

  void handleTileCollisions(std::vector<Rectangle>& others);

protected:
  float _dx, _dy;
  Direction _facing;
  bool _grounded;
  bool _lookingUp = false;
  bool _lookingDown = false;
};

#endif
