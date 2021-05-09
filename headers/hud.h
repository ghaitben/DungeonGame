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
  // Sprite _currentHealthBar; When I declare it here I get a weird bug which leads to quote running super fast
  //if I declare any ariable here I get that bug I don't undrestand why ??!?
  // Sprite _lvlWord;
};


#endif
