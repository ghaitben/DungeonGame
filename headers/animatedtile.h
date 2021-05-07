#ifndef ANIMATED_TILE_H
#define ANIMATED_TILE_H

#include <vector>

#include "tile.h"
#include "globals.h"

class AnimatedTile : public Tile {
public:
	AnimatedTile(std::vector<Vec2> tilesetPositions, int duration, SDL_Texture* tileset, Vec2 size, Vec2 position);
	void update(int elapsedTime);
	void draw(Graphics &graphics);
protected:
	int _amountOfTime = 0;
	bool _notDone = false;
private:
	std::vector<Vec2> _tilesetPositions;
	int _tileToDraw;
	int _duration;
};

struct AnimatedTileInfo {
public:
	int TilesetsFirstGid;
	int StartTileId;
	std::vector<int> TileIds;
	int Duration;
};


#endif
