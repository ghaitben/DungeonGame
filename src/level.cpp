#include "level.h"
#include "graphics.h"
#include "tinyxml2.h"
#include "tile.h"
#include "enemy.h"
#include<sstream>
#include<cmath>
#include<iostream>
#include<algorithm>


using namespace tinyxml2;

Level::Level() {};

Level::Level(std::string mapName, Graphics& graphics) :
      _mapName(mapName),
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

      //animated tile parsing here
      //get all the animations
      XMLElement* aTile = ts->FirstChildElement("tile");
      for(XMLElement* animated_tile = aTile; animated_tile != NULL; animated_tile = animated_tile->NextSiblingElement("tile")) {
        AnimatedTileInfo ati;
        ati.StartTileId = animated_tile->IntAttribute("id") + firstgid;
        ati.TilesetsFirstGid = firstgid;

        XMLElement* xanimation = animated_tile->FirstChildElement("animation");
        for(XMLElement* animation = xanimation; animation != NULL; animation = animation->NextSiblingElement("animation")) {

          XMLElement* xframe = xanimation->FirstChildElement("frame");
          for(XMLElement* frame = xframe; frame != NULL; frame = frame->NextSiblingElement("frame")) {

            ati.TileIds.emplace_back(frame->IntAttribute("tileid") + firstgid);
            ati.Duration = frame->IntAttribute("duration");
          }
        }
        _animatedTileInfos.emplace_back(ati);
      }
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

              //get the tileset of this gid
              int gid = xtile->IntAttribute("gid");
              Tileset tls;
              int closest = 0;
              for(unsigned long int i = 0; i < _tilesets.size(); ++i) {
                if(_tilesets[i].FirstGid <= gid) {
                  if(_tilesets[i].FirstGid > closest) {
                    closest = _tilesets[i].FirstGid;
                    tls = _tilesets[i];                       //collect the tilesets
                  }
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
              Vec2 finalTilesetPosition = getTilesetPosition(tls, gid, tileWidth, tileHeight);

              bool isAnimatedTile = false;
              AnimatedTileInfo ati;
              for(unsigned long int i = 0; i < _animatedTileInfos.size(); ++i) {
                if(_animatedTileInfos.at(i).StartTileId == gid) {
                  ati = _animatedTileInfos.at(i);
                  isAnimatedTile = true;
                  break;
                }
              }
              if(isAnimatedTile == true) {
                std::vector<Vec2> tilesetPositions;
                for(unsigned long int i = 0; i < ati.TileIds.size(); ++i) {
                  tilesetPositions.emplace_back(getTilesetPosition(tls, ati.TileIds.at(i), tileWidth, tileHeight));
                }
                AnimatedTile tile(tilesetPositions, ati.Duration, tls.Texture, Vec2(tileWidth, tileHeight), finalTilePosition);
                _animatedTileList.emplace_back(tile);

              }
              else {
                Tile tile(tls.Texture, Vec2(tileWidth, tileHeight), finalTilesetPosition, finalTilePosition);
                _tileList.emplace_back(tile);
              }
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

  //get the collision rectangles
  XMLElement* xObjectGroup = mapNode->FirstChildElement("objectgroup");
  for(XMLElement* gobject = xObjectGroup; gobject != NULL; gobject = gobject->NextSiblingElement("objectgroup")) {

    const char* name = gobject->Attribute("name");
    std::stringstream c_name;
    c_name << name;

    if(c_name.str() == "collisions") {

      XMLElement* xobject = gobject->FirstChildElement("object");
      for(XMLElement* object = xobject; object != NULL; object = object->NextSiblingElement("object")) {

        float x = object->FloatAttribute("x");
        float y = object->FloatAttribute("y");
        float width = object->FloatAttribute("width");
        float height = object->FloatAttribute("height");
        _collisionRects.emplace_back(Rectangle(
          std::ceil(x) * globals::SPRITE_SCALE,
          std::ceil(y) * globals::SPRITE_SCALE,
          std::ceil(width) * globals::SPRITE_SCALE,
          std::ceil(height) * globals::SPRITE_SCALE
        ));
      }
    }
    else if(c_name.str() == "spawn points") {


      XMLElement* xobject = gobject->FirstChildElement("object");
      for(XMLElement* object = xobject; object != NULL; object = object->NextSiblingElement("object")) {
        float x = object->FloatAttribute("x");
        float y = object->FloatAttribute("y");
        const char*  name = object->Attribute("name");
        std::stringstream s_name;
        s_name << name;
        if(s_name.str() == "player") {
          _spawnPoint = Vec2(std::ceil(x) * globals::SPRITE_SCALE, std::ceil(y) * globals::SPRITE_SCALE);
        }
      }
    }
    //handling the door element /property
    else if(c_name.str() == "doors") {

      //loop through all objects in the object group doors
      XMLElement* xobject = gobject->FirstChildElement("object");
      for(XMLElement* object = xobject; object != NULL; object = object->NextSiblingElement("object")) {

        float x = object->FloatAttribute("x");
        float y = object->FloatAttribute("y");
        float w = object->FloatAttribute("width");
        float h = object->FloatAttribute("height");
        Rectangle rect = Rectangle(x, y, w, h);

        XMLElement* xproperties = object->FirstChildElement("properties");
        //loop through all the proerties section
        for(XMLElement* properties = xproperties; properties != NULL; properties = properties->NextSiblingElement("properties")) {
          XMLElement* xproperty = properties->FirstChildElement("property");

          //loop through all the properties inside the properties section
          for(XMLElement* property = xproperty; property != NULL; property = property->NextSiblingElement("property")) {

            const char* name = property->Attribute("name");
            std::stringstream ss_name;
            ss_name << name;
            if(ss_name.str() == "destination") {
              const char* name2 = property->Attribute("value");
              std::stringstream ss_name2;
              ss_name2 << name2;
              Door door = Door(rect, ss_name2.str());
              _doorList.emplace_back(door);
            }
          }
        }
      }
    }

    //handling the collision with life perks
    else if(c_name.str() == "perks") {

      XMLElement* xobject = gobject->FirstChildElement("object");
      for(XMLElement* object = xobject; object != NULL; object = object->NextSiblingElement("object")) {

        float x = object->FloatAttribute("x");
        float y = object->FloatAttribute("y");
        float width = object->FloatAttribute("width");
        float height = object->FloatAttribute("height");
        float xDuration = object->FloatAttribute("duration");
        Rectangle rect = Rectangle(x, y, width, height);

        _perkList.emplace_back(rect,xDuration);
      }
    }

    else if(c_name.str() == "enemies") {
      float x,y;
      XMLElement* xobject = gobject->FirstChildElement("object");
      for(XMLElement* object = xobject; object != NULL; object = object->NextSiblingElement("object")) {
        x = object->FloatAttribute("x");
        y = object->FloatAttribute("y");
        const char* name = object->Attribute("name");
        std::stringstream ss_name;
        ss_name << name;
        if(ss_name.str() == "bat") {
          _enemies.emplace_back(new Bat(graphics, Vec2(
            std::floor(x) * globals::SPRITE_SCALE,
            std::floor(y) * globals::SPRITE_SCALE
          )));
        }
      }
    }

  }
}

void Level::draw(Graphics& graphics) {
  for(unsigned long int i = 0; i < _tileList.size(); ++i) {
    _tileList.at(i).draw(graphics);
  }
  for(unsigned long int i = 0; i < _animatedTileList.size(); ++i) {
    _animatedTileList.at(i).draw(graphics);
  }
  for(unsigned long int i = 0; i < _enemies.size(); ++i) {
    _enemies.at(i)->draw(graphics);
  }
}

void Level::update(float elapsedTime, Player& player) {
  for(unsigned long int i = 0; i < _animatedTileList.size(); ++i) {
    _animatedTileList.at(i).update(elapsedTime);
  }
  for(unsigned long int i = 0; i < _enemies.size(); ++i) {
    _enemies.at(i)->update(elapsedTime, player);
  }
}

std::vector<Rectangle> Level::checkTileCollisions(const Rectangle& other) {

  std::vector<Rectangle> others;
  for(unsigned long int i = 0; i < _collisionRects.size(); ++i) {
    if(_collisionRects.at(i).collidesWith(other)) {
      others.emplace_back(_collisionRects.at(i));
    }
  }
  return others;
}

std::vector<Door> Level::checkDoorCollision(const Rectangle& other) {

  std::vector<Door> others;
  for(unsigned long int i = 0; i < _doorList.size(); ++i) {
    if(_doorList.at(i).collidesWith(other)) {
      others.emplace_back(_doorList.at(i));
    }
  }
  return others;
}

std::vector<Perk> Level::checkPerkCollision(const Rectangle& other) {

  std::vector<Perk> others;
  for(unsigned long int i = 0; i < _perkList.size(); ++i) {
    if(_perkList.at(i).collidesWith(other)) {
      others.emplace_back(_perkList.at(i));
    }
  }
  return others;
}


const Vec2 Level::getPlayerSpawnPoint() const {
  return _spawnPoint;
}

Vec2 Level::getTilesetPosition(Tileset tls, int gid, int tileWidth, int tileHeight) {

  int tilesetWidth, tilesetHeight;
  SDL_QueryTexture(tls.Texture, NULL, NULL, &tilesetWidth, &tilesetHeight);

  int tsxx = gid % (tilesetWidth / tileWidth) - 1;
  tsxx *= tileWidth;
  int tsyy = 0;
  int amt = ((gid - tls.FirstGid) / (tilesetWidth / tileWidth));
  tsyy = tileHeight * amt;
  Vec2 finalTilesetPosition = Vec2(tsxx, tsyy);

  return finalTilesetPosition;

}
