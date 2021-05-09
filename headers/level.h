#ifndef LEVEL_H
#define LEVEL_H
#include "globals.h"
#include "tile.h"
#include "rectangle.h"
#include "animatedtile.h"
#include "door.h"
#include<string>
#include<vector>

class Graphics;
struct SDL_Texture;
struct Tileset;

class Level {
public:
  Level(std::string mapName, Graphics& graphics);
  Level();
  ~Level();

  void update(float elapsedTime);
  void draw(Graphics& graphics);
  std::vector<Rectangle> checkTileCollisions(const Rectangle& other);
  std::vector<Door> checkDoorCollision(const Rectangle& other);
  const Vec2 getPlayerSpawnPoint() const;

protected:
  std::string _mapName;
  Vec2 _spawnPoint;
  Vec2 _size;
  Vec2 _tileSize;
  std::vector<Tile> _tileList;
  std::vector<Tileset> _tilesets;
  std::vector<Rectangle> _collisionRects;
  std::vector<AnimatedTile> _animatedTileList;
  std::vector<AnimatedTileInfo> _animatedTileInfos;
  std::vector<Door> _doorList;
  SDL_Texture* _backgroundTexture;



  // load a map
  void loadMap(std::string mapName, Graphics& graphics);
  Vec2 getTilesetPosition(Tileset tls, int gid, int tileWidth, int tileHeight);
};

struct Tileset {
  SDL_Texture* Texture;
  int FirstGid;

  Tileset() {
    FirstGid = -1;
  }
  Tileset(SDL_Texture* texture, int firstGid) {
    Texture = texture;
    FirstGid = firstGid;
  }
};


#endif
