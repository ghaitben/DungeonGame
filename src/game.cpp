#include<SDL2/SDL.h>
#include "game.h"
#include "graphics.h"
#include "input.h"
#include "player.h"

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

  _player = Player(graphics, 300, 200);
  _level = Level("map_1", Vec2(100,200),graphics);


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
      if(input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true) {
        return;
      }
      else if(input.wasKeyPressed(SDL_SCANCODE_LEFT) == true) {
        _player.goLeft();
      }
      else if(input.wasKeyPressed(SDL_SCANCODE_RIGHT) == true) {
        _player.goRight();
      }
      else if(!input.wasKeyPressed(SDL_SCANCODE_LEFT) && !input.wasKeyPressed(SDL_SCANCODE_RIGHT)) {
        _player.stop();
      }
    }

    int CURRENT_TIME = SDL_GetTicks();
    int ElapsedTime = CURRENT_TIME - START_TIME;
    update(std::min(MAX_FRAME_TIME,ElapsedTime));         //Limiting the FPS the elapsed time should be less than the max_time_frame
    START_TIME = CURRENT_TIME;                              // other wise the frame will update at max_frame_time

    draw(graphics);

  }

}

void Game::draw(Graphics &graphics) {

  graphics.clear();                 //clear everything that's on screen
  _level.draw(graphics);            //draw the map of the level
  _player.draw(graphics);
  
  graphics.render();
}

void Game::update(float elapsedTime) {
  _player.update(elapsedTime);
  _level.update(elapsedTime);
}
