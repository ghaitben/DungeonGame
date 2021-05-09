#ifndef PERK_H
#define PERK_H

class Perk : public Rectangle {
public:

  Perk() {}
  Perk(Rectangle rect, int duration) : Rectangle(rect.getLeft() * globals::SPRITE_SCALE,
    rect.getTop() * globals::SPRITE_SCALE, rect.getWidth() * globals::SPRITE_SCALE, rect.getHeight() * globals::SPRITE_SCALE),

    _xDuration(duration) {}

  int _xDuration;
};




#endif
