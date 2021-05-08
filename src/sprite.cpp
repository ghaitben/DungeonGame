#include "sprite.h"
#include "globals.h"
#include<string>
#include<iostream>


Sprite::Sprite() {};

Sprite::Sprite(Graphics& graphics, const std::string& filepath, int sourceX, int sourceY, int width, int height,
   float posX, float posY) : _x(posX), _y(posY) {

    _sourceRect.x = sourceX;              //these are the positions of my sprite in the sprite sheet png picture
    _sourceRect.y = sourceY;               // and width and height are the width of the sprite in the sprite sheet
    _sourceRect.w = width;
    _sourceRect.h = height;

    _spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filepath));

    if(_spriteSheet == NULL) {
      std::cout << "filepath unknown" << std::endl;
    }

    _boundingBox = Rectangle(_x, _y, width * globals::SPRITE_SCALE, height * globals::SPRITE_SCALE);
}

Sprite::~Sprite() {}

void Sprite::draw(Graphics& graphics, int x, int y) {
  SDL_Rect destinationRectangle = {x, y, _sourceRect.w * globals::SPRITE_SCALE, _sourceRect.h * globals::SPRITE_SCALE};
  graphics.blitSurface(_spriteSheet, &_sourceRect, &destinationRectangle);

}

void Sprite::update() {
  _boundingBox = Rectangle(_x,_y,_sourceRect.w * globals::SPRITE_SCALE, _sourceRect.h * globals::SPRITE_SCALE);
};

const Rectangle Sprite::getBoundingBox() const {
  return _boundingBox;
}

const sides::Side Sprite::getCollisionSide(Rectangle& other) const {
	int amtRight, amtLeft, amtTop, amtBottom;
	amtRight = getBoundingBox().getRight() - other.getLeft();
	amtLeft = other.getRight() - getBoundingBox().getLeft();
	amtTop = other.getBottom() - getBoundingBox().getTop();
	amtBottom = getBoundingBox().getBottom() - other.getTop();

	int vals[4] = { abs(amtRight), abs(amtLeft), abs(amtTop), abs(amtBottom) };
	int lowest = vals[0];
	for (int i = 0; i < 4; i++) {
		if (vals[i] < lowest) {
			lowest = vals[i];
		}
	}

	return
			lowest == abs(amtRight) ? sides::RIGHT :
			lowest == abs(amtLeft) ? sides::LEFT :
			lowest == abs(amtTop) ? sides::TOP :
			lowest == abs(amtBottom) ? sides::BOTTOM :
			sides::NONE;

}

void Sprite::setSourceRectX(int value) {
  _sourceRect.x = value;
}

void Sprite::setSourceRectY(int value) {
  _sourceRect.y = value;
}

void Sprite::setSourceRectW(int value) {
  _sourceRect.w = value;
}

void Sprite::setSourceRectH(int value) {
  _sourceRect.h = value;
}
