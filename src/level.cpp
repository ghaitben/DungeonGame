#include "level.h"
#include "graphics.h"
#include "tinyxml2.h"
#include "tile.h"
#include<sstream>
#include<cmath>
#include<algorithm>


using namespace tinyxml2;

Level::Level() {};

Level::Level(std::string mapName, Vec2 spawnPoint, Graphics& graphics) :
      _mapName(mapName),
      _spawnPoint(spawnPoint),
      _size(Vec2(0,0))
{
  loadMap(mapName, graphics);
}

Level::~Level() {}

void Level::loadMap(std::string mapName, Graphics& graphics) {
  //parsing the map.tmx file
  XMLDocument doc;
  std::stringstream path;
  path << "../Media/maps/" << mapName << ".tmx";
  doc.LoadFile(path.str().c_str());

  XMLElement* mapNode = doc.FirstChildElement("map");

  //get the width and height of the map
  int width, height;
	mapNode->QueryIntAttribute("width", &width);
	mapNode->QueryIntAttribute("height", &height);

  _size = Vec2(width,height);

  //get the width and height of the tileset
  int tileWidth, tileHeight;
  mapNode->QueryIntAttribute("tilewidth",&tileWidth);
  mapNode->QueryIntAttribute("tileheight",&tileHeight);

  _tileSize = Vec2(tileWidth,tileHeight);

  //load the tilesets
  XMLElement* ts = mapNode->FirstChildElement("tileset");

  if(ts != NULL) {
    while (ts) {

      int firstgid;
      const char* path = ts->FirstChildElement("image")->Attribute("source"); //get source of the image from the map_1.tmx
      std::stringstream ssPath;
      ssPath << path;

      ts->QueryIntAttribute("firstgid",&firstgid);

      SDL_Texture* tex = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(ssPath.str()));   //create the text

      _tilesets.emplace_back(Tileset(tex, firstgid));

      ts = ts->NextSiblingElement("tileset");

    }
  }
  //All tilesets are loaded, tilesets are the bag of different tiles
  //now we need to draw the tiles based on the map.tmx file
  XMLElement* xlayer = mapNode->FirstChildElement("layer");
  //looping through the layers
  if(xlayer != NULL) {
    while(xlayer) {
      //looping through the data
      XMLElement* xdata = xlayer->FirstChildElement("data");

      if(xdata != NULL) {
        while(xdata) {
          //looping through the tiles
          XMLElement* xtile = xdata->FirstChildElement("tile");
          if(xtile != NULL) {
            int tileCounter = 0;
            while(xtile) {
              //draw the tiles on the map
              //if gid == 0, no tiles should be drawn
              if(xtile->IntAttribute("gid") == 0) {
                tileCounter++;
                if(xtile->NextSiblingElement("tile")) {             //if there are still tiles with gid 0 after this one
                  xtile = xtile->NextSiblingElement("tile");        //go to the next tiles and reset the loop
                  continue;
                }
                else {
                  break;
                }
              }

              int gid = xtile->IntAttribute("gid");
              Tileset tls;

              for(unsigned long int i = 0; i < _tilesets.size(); ++i) {
                if(_tilesets[i].FirstGid <= gid) {                //what we did here is collect the tileset associated with that
                  tls = _tilesets[i];                              //specific tile with that specific gid
                  break;
                }
              }

              if(tls.FirstGid == -1) {
                tileCounter++;
                if(xtile->NextSiblingElement("tile")) {
                  xtile = xtile->NextSiblingElement("tile");
                  continue;
                }
                else {
                  break;
                }
              }

              //get the position of the tile in the map
              int xx = 0;
							int yy = 0;
							xx = tileCounter % width;
							xx *= tileWidth;
							yy += tileHeight * (tileCounter / width);
							Vec2 finalTilePosition = Vec2(xx, yy);


              //get the position of the tile in the tileset
              int tilesetWidth, tilesetHeight;
              SDL_QueryTexture(tls.Texture, NULL, NULL, &tilesetWidth, &tilesetHeight);

              int tsxx = gid % (tilesetWidth / tileWidth) - 1;
              tsxx *= tileWidth;
              int tsyy = 0;
              int amt = ((gid - tls.FirstGid) / (tilesetWidth / tileWidth));
              tsyy = tileHeight * amt;
              Vec2 finalTilesetPosition = Vec2(tsxx, tsyy);
              Tile tile(tls.Texture, Vec2(tileWidth, tileHeight), finalTilesetPosition, finalTilePosition);
              _tileList.emplace_back(tile);
              tileCounter++;

              xtile = xtile->NextSiblingElement("tile");
            }
          }
          xdata = xdata->NextSiblingElement("data");
        }
      }
      xlayer = xlayer->NextSiblingElement("layer");
    }
  }
}

void Level::draw(Graphics& graphics) {
  for(unsigned long int i = 0; i < _tileList.size(); ++i) {
    _tileList.at(i).draw(graphics);
  }
}


void Level::update(float elapsedTime) {}
