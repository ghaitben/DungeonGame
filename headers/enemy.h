#ifndef ENEMY_H
#define ENEMY_H
#include "animatedSprite.h"

class Player;
#include<string>

class Enemy : public AnimatedSprite {

public:
  Enemy();
  Enemy(Graphics& graphics, std::string filePath, int sourceX, int sourceY, int width, int height,Vec2 spawnPoint,float timeToupdate);
  virtual void update(float elapsedTime, Player& player);
  virtual void draw(Graphics& graphics);
  virtual void touchPlayer(Player* player) = 0;

  const inline int getCurrentHealth() { return _currentHealth; }
  const inline int getMaxHealth() { return _maxHealth; }

protected:

  Direction _direction;
  int _maxHealth;
  int _currentHealth;

};

class Bat : public Enemy {
public:
  Bat();
  Bat(Graphics& graphics, Vec2 spawnPoint);

  void update(float elapsedTime, Player& player);
  void draw(Graphics& graphics);
  void touchPlayer(Player* player);
  void animationDone(std::string currentAnimation);
  void setupAnimations();
private:
  float _startingX, _startingY;
  bool _shouldMoveUp = false;
};

#endif
