#ifndef GLOBALS_H
#define GLOBALS_H

namespace globals {
  const int SCREEN_WIDTH = 640;
  const int SCREEN_HEIGHT = 480;
  const int SPRITE_SCALE = 2;
}

namespace sides {
  enum Side {
    TOP,
    BOTTOM,
    LEFT,
    RIGHT,
    NONE
  };
  inline Side getOppositeSide(Side side) {
		return
				side == TOP ? BOTTOM :
				side == BOTTOM ? TOP :
				side == LEFT ? RIGHT :
				side == RIGHT ? LEFT :
				NONE;
	}
}

enum Direction {            // enum is a type that can only take a range of values here (UP , DOWN , LEFT , RIGHT)
  Left,
  Right,
  Up,
  Down
};


struct Vec2 {
  int x,y;
  Vec2() : x(0), y(0) {};
  Vec2(int x, int y) : x(x), y(y) {};
};


#endif
