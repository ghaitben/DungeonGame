#include "hud.h"
#include "graphics.h"


HUD::HUD() {}

HUD::HUD(Graphics& graphics, Player& player) {
  _player = player;                                                                           //where to put it on the screen (35,70)
  _healthBarSprite = Sprite(graphics, "../Media/sprites/TextBox.png", 0, 40, 64, 8, 35, 30);  //x,y(in the sprite sheet),width,height
  _healthNumber1 = Sprite(graphics, "../Media/sprites/TextBox.png",0 , 56, 8, 8, 66, 30);

}


void HUD::update(float elapsedTime) {
  _healthNumber1.setSourceRectX(8 * _player.getCurrentHealth());

}


void HUD::draw(Graphics& graphics) {
  _healthBarSprite.draw(graphics, _healthBarSprite.getX(), _healthBarSprite.getY());
  _healthNumber1.draw(graphics, _healthNumber1.getX(), _healthNumber1.getY());
}
