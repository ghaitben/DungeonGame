#ifndef INTERFACE_H
#define INTERFACE_H
#include "sprite.h"
#include "player.h"

class Interface {

public:
  Interface();
  Interface(Graphics& graphics, Player& player);

  void update(float elapsedTime, Player& player);
  void draw(Graphics& graphics);

private:
  Player _player;
  Sprite _healthBarSprite;
  Sprite _healthNumber1;
  Sprite _currentHealthBar; //I've put it here to prevent that weird bug (check hud.h)
  Sprite _lvlWord;
  Sprite _lvlNumber;
  Sprite _expBar;
  Sprite _slash;
  Sprite _dashes;
  // Sprite _currentHealthBar; When I declare it here I get a weird bug which leads to quote running super fast
  //if I declare any ariable here I get that bug I don't undrestand why ??!?
  // Sprite _lvlWord;
};


#endif
