#include<SDL2/SDL.h>
#include "globals.h"
#include "graphics.h"
#include "tile.h"


Tile::Tile() {}

Tile::Tile(SDL_Texture* tileset, Vec2 size, Vec2 tilesetPosition, Vec2 mapPosition) :
          _tileset(tileset),
          _size(size),
          _tilesetPosition(tilesetPosition),
          _mapPosition(Vec2(mapPosition.x * globals::SPRITE_SCALE, mapPosition.y * globals::SPRITE_SCALE)) {}



void Tile::update(float elapsedTime) {}

void Tile::draw(Graphics& graphics) {
  //destRect is where I am going to draw the tile in the map
  SDL_Rect destRect = {_mapPosition.x, _mapPosition.y, _size.x * globals::SPRITE_SCALE, _size.y * globals::SPRITE_SCALE};
  //sourceRect is from where I'm taking the tile that I'm going to draw.
  SDL_Rect sourceRect = {_tilesetPosition.x, _tilesetPosition.y, _size.x, _size.y};
  graphics.blitSurface(_tileset, &sourceRect, &destRect);
}
