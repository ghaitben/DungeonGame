#include "animatedtile.h"
#include "graphics.h"

AnimatedTile::AnimatedTile(std::vector<Vec2> tilesetPositions, int duration,
		SDL_Texture* tileset, Vec2 size, Vec2 position) :
		Tile(tileset, size, tilesetPositions.at(0), position),
		_tilesetPositions(tilesetPositions),
    _tileToDraw(0),
		_duration(duration)
{}

void AnimatedTile::update(int elapsedTime) {
	//Timer code
	if (_amountOfTime <= 0) {
    _tileToDraw = (_tileToDraw + 1) % _tilesetPositions.size(); 
		_amountOfTime = _duration;
	}
	else {
		_amountOfTime -= elapsedTime;
	}

	Tile::update(elapsedTime);
}

void AnimatedTile::draw(Graphics &graphics) {
	SDL_Rect destRect = { _mapPosition.x, _mapPosition.y,
			_size.x * globals::SPRITE_SCALE, _size.y * globals::SPRITE_SCALE };
	SDL_Rect sourceRect = { _tilesetPositions.at(_tileToDraw).x, _tilesetPositions.at(_tileToDraw).y,
			_size.x, _size.y };
	graphics.blitSurface(_tileset, &sourceRect, &destRect);
}
