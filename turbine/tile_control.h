#ifndef _TILECONTROL_H_
#define _TILECONTROL_H_

#include "classes.h"
#include "turbine/object.h"

namespace Turbine {
namespace Extras {

class Tile {
public:
	Tile() : id(-1) {};
	Tile(int id, int rotation) : id(id), rotation(rotation), key(id + rotation * 100) {};
	Tile(int v) : id(v % 100), rotation(v / 100), key(v) {};
	int id, rotation, key;
};

class TileControl : public SimpleGameObject {
public:
	TileControl(int tilesX, int tilesY, int tileSize, std::string contentDir, Tile *tiles);
	~TileControl();

	Tile getTile(int xIndex, int yIndex);
	Tile getTilePosition(Geom::Point p);
	void setup();
	void draw();

	int tilesX, tilesY, tileSize;
	std::map<int, Turbine::Graphics::Image *> images;
	Tile* tiles;
};

class TerrainControl : public SimpleGameObject {
public:
	TerrainControl(int terrainX, int terrainY, int terrainSize, std::string contentDir, int* terrain);
	~TerrainControl();

	int getTerrain(int xIndex, int yIndex);
	int getTerrainPosition(Geom::Point p);

	void draw();

protected:
	Tile getAt(Tile *tiles, int pX, int pY);
	Tile calculateTile(Tile *tiles, int pX, int pY);

	std::map<int, TileControl*> tileControls;
	int terrainX, terrainY, terrainSize;
	int *terrain;
};

}
}

#endif