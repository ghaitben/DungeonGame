#include "input.h"
#include<SDL2/SDL.h>


void Input::beginNewFrame() {
  _pressedKeys.clear();
  _releasedKeys.clear();
}

void Input::keyDownEvent(const SDL_Event& event) {
  _pressedKeys[event.key.keysym.scancode] = true;
  _heldKeys[event.key.keysym.scancode] = true;
}

void Input::keyUpEvent(const SDL_Event& event) {
  _releasedKeys[event.key.keysym.scancode] = true;
  _heldKeys[event.key.keysym.scancode] = false;
}

bool Input::wasKeyHeld(SDL_Scancode key) {
  return _heldKeys[key];
}

bool Input::wasKeyPressed(SDL_Scancode key) {
  return _pressedKeys[key];
}

bool Input::wasKeyReleased(SDL_Scancode key) {
  return _releasedKeys[key];
}
