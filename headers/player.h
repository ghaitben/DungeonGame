#ifndef PLAYER_H
#define PLAYER_H

#include "animatedSprite.h"
#include "level.h"
#include "graphics.h"
#include "enemy.h"

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
  void handleDoorCollision(std::vector<Door>& others, Level& level, Graphics& graphics);
  void handlePerkCollision(std::vector<Perk>& others, Level& level, Graphics& graphics, float elapsedTime);
  void handleEnemyCollision(std::vector<Enemy*>& others);

  const inline int getMaxHealth() const { return _maxHealth; }
  const inline int getCurrentHealth() const { return _currentHealth; }
  void gainHealth(int amount);

private:
  float _dx, _dy;
  Direction _facing;
  bool _grounded;
  bool _lookingUp = false;
  bool _lookingDown = false;

  int _maxHealth;
  int _currentHealth;
};

#endif
