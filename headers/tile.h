#ifndef TILE_H
#define TILE_H

#include "globals.h"
class Graphics;
class SDL_Texture;


class Tile {

public:
  Tile();
  Tile(SDL_Texture* _tileset, Vec2 _size, Vec2 _tilesetPosition, Vec2 _mapPosition);
  void update(float elapsedTime);
  void draw(Graphics& graphics);
protected:
  SDL_Texture* _tileset;
  Vec2 _size;
  Vec2 _tilesetPosition;
  Vec2 _mapPosition;
};


#endif
