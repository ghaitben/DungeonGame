#include "hud.h"
#include "graphics.h"

Sprite _currentHealthBar; //I've put it here to prevent that weird bug (check hud.h)
Sprite _lvlWord;
Sprite _lvlNumber;
Sprite _expBar;
Sprite _slash;
Sprite _dashes;

HUD::HUD() {}

HUD::HUD(Graphics& graphics, Player& player) {
  _player = player;                                                                           //where to put it on the screen (35,70)
  _healthBarSprite = Sprite(graphics, "../Media/sprites/TextBox.png", 0, 40, 64, 8, 35, 60);  //x,y(in the sprite sheet),width,height
  _healthNumber1 = Sprite(graphics, "../Media/sprites/TextBox.png",0 , 56, 8, 8, 66, 60);
  _currentHealthBar = Sprite(graphics, "../Media/sprites/TextBox.png", 0, 25, 39, 5, 83, 62);
  _lvlWord = Sprite(graphics, "../Media/sprites/TextBox.png", 81, 81, 11, 7, 38,45);
  _lvlNumber = Sprite(graphics, "../Media/sprites/TextBox.png", 0, 56, 8, 8, 66, 42);
  _expBar = Sprite(graphics, "../Media/sprites/TextBox.png", 0, 72, 40, 8, 83, 42);
  _slash = Sprite(graphics, "../Media/sprites/TextBox.png", 72, 48, 8, 8, 100, 26);
  _dashes = Sprite(graphics, "../Media/sprites/TextBox.png", 81, 51, 15, 11, 132, 16);
}


void HUD::update(float elapsedTime) {
  _healthNumber1.setSourceRectX(8 * _player.getCurrentHealth());

  float num = (float) _player.getCurrentHealth() / _player.getMaxHealth();
  _currentHealthBar.setSourceRectW(num * 39);

}


void HUD::draw(Graphics& graphics) {
  _healthBarSprite.draw(graphics, _healthBarSprite.getX(), _healthBarSprite.getY());
  _healthNumber1.draw(graphics, _healthNumber1.getX(), _healthNumber1.getY());
  _currentHealthBar.draw(graphics, _currentHealthBar.getX(), _currentHealthBar.getY());
  _lvlWord.draw(graphics, _lvlWord.getX(), _lvlWord.getY());
  _lvlNumber.draw(graphics, _lvlNumber.getX(), _lvlNumber.getY());
  _expBar.draw(graphics, _expBar.getX(), _expBar.getY());
  _slash.draw(graphics, _slash.getX(), _slash.getY());
  _dashes.draw(graphics, _dashes.getX(), _dashes.getY());
}
