#ifndef LEVEL_H
#define LEVEL_H
#include "globals.h"
#include "tile.h"
#include<string>
#include<vector>

class Graphics;
struct SDL_Texture;
struct Tileset;

class Level {
public:
  Level(std::string mapName, Vec2 spawnPoint, Graphics& graphics);
  Level();
  ~Level();

  void update(float elapsedTime);
  void draw(Graphics& graphics);
protected:
  std::string _mapName;
  Vec2 _spawnPoint;
  Vec2 _size;
  Vec2 _tileSize;
  std::vector<Tile> _tileList;
  std::vector<Tileset> _tilesets;

  SDL_Texture* _backgroundTexture;


  // load a map
  void loadMap(std::string mapName, Graphics& graphics);
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
