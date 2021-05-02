#include "sprite.h"
#include<string>
#include<iostream>


Sprite::Sprite() {};

Sprite::Sprite(Graphics& graphics, const std::string& filepath, int SourceX, int SourceY, int width, int height,
   float posX, float posY) : _x(posX), _y(posY) {

    _sourceRect.x = SourceX;              //these are the positions of my sprite in the sprite sheet png picture
    _sourceRect.y = SourceY;               // and width and height are the width of the sprite in the sprite sheet
    _sourceRect.w = width;
    _sourceRect.h = height;

    _spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filepath));

    if(_spriteSheet == NULL) {
      std::cout << "filepath unknown" << std::endl;
    }
}

Sprite::~Sprite() {}

void Sprite::draw(Graphics& graphics, int x, int y) {
  SDL_Rect destinationRectangle = {x, y, _sourceRect.w, _sourceRect.h};
  graphics.blitSurface(_spriteSheet, &_sourceRect, &destinationRectangle);

}

void Sprite::update() {};
