#include<SDL2/SDL.h>
#include "game.h"
#include "graphics.h"
#include "input.h"
#include "sprite.h"

const int MAX_FPS = 50;
const int MAX_FRAME_TIME = (5*1000)/MAX_FPS;



Game::Game() {
    SDL_Init(SDL_INIT_EVERYTHING);
    gameLoop();
}

Game::~Game() {

}

void Game::gameLoop() {
  Graphics graphics;
  Input input;
  SDL_Event event;
  _player = AnimatedSprite(graphics, "../Media/sprites/MyChar.png", 0, 0, 16, 16, 0, 0, 100);
  _player.setupAnimations();
  _player.playAnimation("GoLeft");

  int START_TIME = SDL_GetTicks();

  //start of the gameloop
  while(true) {

    input.beginNewFrame();          //reset the pressed/released keys
    if(SDL_PollEvent(&event)) {
      if(event.type == SDL_KEYDOWN) {         //SDL_KEYDOWN/KEYUP shows whether a key is pressed/released
        input.keyDownEvent(event);          //updates the variables _pressedKeys/_releasedKeys
      }
      else if(event.type == SDL_KEYUP) {
        input.keyUpEvent(event);
      }
      else if(event.type == SDL_QUIT) {
        return;
      }
    }
    if(input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true) {
      return;
    }

    int CURRENT_TIME = SDL_GetTicks();
    int ElapsedTime = CURRENT_TIME - START_TIME;
    update(std::min(MAX_FRAME_TIME,ElapsedTime));         //Limiting the FPS the elapsed time should be less than the max_time_frame
    START_TIME = CURRENT_TIME;                              // other wise the frame will update at max_frame_time

    draw(graphics);

  }

}

void Game::draw(Graphics &graphics) {

  graphics.clear();
  _player.draw(graphics, 300, 100);
  graphics.render();
}

void Game::update(float elapsedTime) {
  _player.update(elapsedTime);
}
