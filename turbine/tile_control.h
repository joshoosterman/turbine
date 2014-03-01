// Copyright 2011

#ifndef TURBINE_TILE_CONTROL_H_
#define TURBINE_TILE_CONTROL_H_

#include <string>
#include <map>

#include "turbine/classes.h"
#include "turbine/object.h"

namespace turbine {
namespace extras {

class Tile {
 public:
  Tile() : id(-1) {}
  Tile(int id, int rotation)
      : id(id), rotation(rotation), key(id + rotation * 100) {}
  explicit Tile(int v) : id(v % 100), rotation(v / 100), key(v) {}
  int id, rotation, key;
};

class TileControl : public SimpleGameObject {
 public:
  TileControl(int tilesX, int tilesY, int tileSize, std::string contentDir,
              Tile *tiles);
  ~TileControl();

  Tile getTile(int xIndex, int yIndex);
  Tile getTilePosition(geom::Point p);
  void setup();
  void draw();

  int tilesX, tilesY, tileSize;
  std::map<int, turbine::graphics::Image *> images;
  Tile *tiles;
};

class TerrainControl : public SimpleGameObject {
 public:
  TerrainControl(int terrainX, int terrainY, int terrainSize,
                 std::string contentDir, int *terrain);
  ~TerrainControl();

  int getTerrain(int xIndex, int yIndex);
  int getTerrainPosition(geom::Point p);

  void draw();

 protected:
  Tile getAt(Tile *tiles, int pX, int pY);
  Tile calculateTile(Tile *tiles, int pX, int pY);

  std::map<int, TileControl *> tileControls;
  int terrainX, terrainY, terrainSize;
  int *terrain;
};

}  // namespace extras
}  // namespace turbine

#endif  // TURBINE_TILE_CONTROL_H_
