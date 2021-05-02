// this is where I code the methods of the class
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "graphics.h"

Graphics::Graphics() {
  SDL_CreateWindowAndRenderer(640, 480, 0, &_window, &_renderer);
  SDL_SetWindowTitle(_window, "adventure_game");
}

Graphics::~Graphics() {
  SDL_DestroyWindow(_window);
}

SDL_Surface* Graphics::loadImage(const std::string& filepath) {

  if(_spriteSheets.count(filepath) == 0) {
    _spriteSheets[filepath] = IMG_Load(filepath.c_str());
  }
  return _spriteSheets[filepath];

}

void Graphics::blitSurface(SDL_Texture* texture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle) {

  SDL_RenderCopy(_renderer, texture, sourceRectangle, destinationRectangle);
}

void Graphics::render() {
  SDL_RenderPresent(_renderer);
}

void Graphics::clear() {
  SDL_RenderClear(_renderer);
}

SDL_Renderer* Graphics::getRenderer() const {
  return _renderer;
}
