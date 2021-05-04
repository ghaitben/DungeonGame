// header used to initialize a class without having to code its methods
// graphics header is responsible for the drawings on the screen
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include<string>
#include<map>
#include<SDL2/SDL.h>

struct SDL_Window;
struct SDL_Renderer;


class Graphics {

public:
  Graphics();
  ~Graphics();

  SDL_Surface* loadImage(const std::string& filePath);        // make sure the image is loaded just once and load it if it inexistant

  void blitSurface(SDL_Texture* source, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle); //draws in a specific screen part

  void render();              //renderes everything to the screen

  void clear();               // clears everything in the screen


  SDL_Renderer* getRenderer() const;



private:
  SDL_Renderer* _renderer;
  SDL_Window* _window;
  std::map<std::string, SDL_Surface*> _spriteSheets;
};


#endif
