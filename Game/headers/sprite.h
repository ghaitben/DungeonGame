#ifndef SPRITE_H
#define SPRITE_H

#include<SDL2/SDL.h>
#include<string>
#include "graphics.h"

//class Graphics here will work because I just use it as an identifier but in sprite.cpp I use one of its methods so I need to include
//the whole header file

class Sprite {
public:
  Sprite();
  Sprite(Graphics& graphics, const std::string& filepath, int SourceX, int SourceY, int width, int height, float posX, float posY);

  virtual ~Sprite();
  virtual void update();          //virtual because it is going to be overriden once we change sprites
  void draw(Graphics& graphics, int x, int y);

private:
  SDL_Rect _sourceRect;
  SDL_Texture* _spriteSheet;

  float _x, _y;
};



#endif
