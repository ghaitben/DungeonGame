#include "enemy.h"
#include "player.h"

//enemy class

Enemy::Enemy() {}

Enemy::Enemy(Graphics& graphics, std::string filePath, int sourceX, int sourceY, int width, int height, Vec2 spawnPoint,
            float timeToupdate) :
            AnimatedSprite(graphics, filePath, sourceX, sourceY, width, height, spawnPoint.x, spawnPoint.y, timeToupdate),
            _direction(Left),
            _maxHealth(0),
            _currentHealth(0)

{}

void Enemy::update(float elapsedTime, Player& player) {
  AnimatedSprite::update(elapsedTime);
}

void Enemy::draw(Graphics& graphics) {
  AnimatedSprite::draw(graphics, _x, _y);
}

//bat class

Bat::Bat() {}

Bat::Bat(Graphics& graphics, Vec2 spawnPoint) : Enemy(graphics, "../Media/sprites/NpcCemet.png", 32, 32, 16, 16, spawnPoint, 100) {
  setupAnimations();
  playAnimation("FlyLeft");
}

void Bat::update(float elapsedTime, Player& player) {
  _direction = player.getX() > _x ? Right : Left;
  playAnimation(_direction == Right ? "FlyRight" : "FlyLeft");
  Enemy::update(elapsedTime,player);
}

void Bat::draw(Graphics& graphics) {
  Enemy::draw(graphics);
}

void Bat::animationDone(std::string currentAnimation) {}

void Bat::setupAnimations() {
  addAnimation(3, 2, 32, "FlyLeft", 16, 16, Vec2(0,0));
  addAnimation(3, 2, 48, "FlyRight", 16, 16, Vec2(0,0));
}
