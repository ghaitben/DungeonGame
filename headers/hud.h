#ifndef HUD_H
#define HUD_H

#include "sprite.h"
#include "player.h"

class HUD {

public:
  HUD();
  HUD(Graphics& graphics, Player& player);

  void update(float elapsedTime);
  void draw(Graphics& graphics);

private:
  Player _player;
  Sprite _healthBarSprite;
  Sprite _healthNumber1;
};


#endif
