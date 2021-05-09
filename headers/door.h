#ifndef DOOR_H
#define DOOR_H

#include "rectangle.h"
#include "globals.h"
#include<string>

class Door : public Rectangle {
public:
  Door() {}
  Door(Rectangle rect, std::string destination) : Rectangle(rect.getLeft() * globals::SPRITE_SCALE,
   rect.getTop() * globals::SPRITE_SCALE, rect.getWidth() * globals::SPRITE_SCALE, rect.getHeight() * globals::SPRITE_SCALE),
   _destination(destination) {}

  const inline Rectangle getRectangle() const { return getRect(); }
  const inline std::string getDestination() const { return _destination; }
private:
  std::string _destination;
};

#endif
