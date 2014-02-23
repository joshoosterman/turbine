#include <sstream>

#include "turbine/exceptions.h"
#include "turbine/sprite.h"
#include "turbine/tile_control.h"
#include "turbine/view.h"

#define MIN(X,Y) ((X) < (Y) ? : (X) : (Y))

using namespace Turbine::Geom;
using namespace Turbine::Graphics;
using namespace Turbine::Internal;

namespace Turbine {
namespace Extras {

TileControl::TileControl(int tilesX, int tilesY, int tileSize, std::string contentDir, Tile *tiles) : SimpleGameObject(30)
{
	if(tilesX == 0 || tilesY == 0 || tileSize == 0) {
		throw Exception("Bad parameters to TileControl - tile size cannot be zero!");
	}

	this->tilesX = tilesX;
	this->tilesY = tilesY;
	this->tileSize = tileSize;

	int size = tilesX * tilesY;
	if(size < 0) {
		throw Exception("Bad parameters to TileControl - dimensions cause int overflow!");
	}
	this->tiles = new Tile[size];

	for(int i = 0; i < size; i++)
	{
		Tile t = tiles[i];
		this->tiles[i] = t;

		if(t.id < 0) {
			continue;
		}

		if(images.find(t.key) == images.end()){
			std::string s;
			std::stringstream out;
			out << contentDir << "/" << t.id << ".png";
			s = out.str();

			Image *image = new Image(s);
			image->setOrigin(Point(tileSize / 2, tileSize / 2));
			image->setRotation(-t.rotation * 90);

			images[t.key] = image;
		}
	}
}

void TileControl::setup()
{
}

TileControl::~TileControl()
{
	//TODO: DELETE EACH IMAGE (Pointer)
	delete tiles;
}

Tile TileControl::getTile(int xIndex, int yIndex)
{
	int x = xIndex % tilesX;
	while(x < 0) { x += tilesX; }
	int y = yIndex % tilesY;
	while(y < 0) { y += tilesY; }
	int ind = y * tilesX + x;
	return tiles[ind];
}

Tile TileControl::getTilePosition(Point p)
{
	int x2 = (int)(p.x / tileSize), y2 = (int)(p.y / tileSize);
	return getTile(x2, y2);
}

void TileControl::draw()
{
	View *view = View::getCurrentView();

	Point p1 = Point(0, 0) + view->getPosition();
	Point p2 = p1 + view->getSize();

	int leftX = (int) (p1.x / tileSize - 1);
	int rightX = (int) (p2.x / tileSize + 1);
	int topY = (int) (p1.y / tileSize - 1);
	int bottomY = (int) (p2.y / tileSize + 1);

	for (int i = leftX; i < rightX; i++)
	{
		for (int j = topY; j < bottomY; j++)
		{
			Tile t = getTile(i, j);
			if(t.id >= 0) {
				float xC = ((float)i + 0.5f) * (float)tileSize;
				float yC = ((float)j + 0.5f) * (float)tileSize;
				images[t.key]->draw(Point(xC, yC));
			}
		}
	}
}

#define TERRAIN_TO_CALCULATE -2
#define TERRAIN_NONE -1
#define TERRAIN_MATCH_WILDCARD 9 

TerrainControl::TerrainControl(int terrainX, int terrainY, int terrainSize, std::string contentDir, int* terrain) : SimpleGameObject(30)
{
	if(terrainX == 0 || terrainY == 0 || terrainSize == 0) {
		throw Exception("Bad parameters to TileControl - tile size cannot be zero!");
	}

	this->terrainX = terrainX;
	this->terrainY = terrainY;
	this->terrainSize = terrainSize;

	int size = terrainX * terrainY;
	this->terrain = new int[size];

	for(int i = 0; i < size; i++)
	{
		int t = terrain[i];
		this->terrain[i] = t;

		if(tileControls.find(t) == tileControls.end()){
			std::string tcdir;
			std::stringstream out;
			out << contentDir << "/" << t;
			tcdir = out.str();

			Tile *tls = new Tile[size];
			for(int j = 0; j < size; j++)
			{
				if(terrain[j] == t) {
					//This type of terrain
					tls[j] = Tile(0, 0);
				} else if(terrain[j] < t) {
					//Lower type of terrain, needs
					//to be calculated
					tls[j] = Tile(TERRAIN_TO_CALCULATE, 0);
				} else {
					//Higher type of terrain, will
					//be ocluded by another layer
					tls[j] = Tile(TERRAIN_NONE, 0);
				}
			}
			for(int j = 0; j < size; j++)
			{
				if(tls[j].id == TERRAIN_TO_CALCULATE) {
					int x = j % terrainX;
					int y = j / terrainX;
					tls[j] = calculateTile(tls, x, y);
				}
			}

			TileControl* tc = new TileControl(terrainX, terrainY, terrainSize, tcdir, tls);
			tileControls[t] = tc;
			delete tls;
		}
	}
}

int compare(int *surrounding, const char *test)
{
	for(int rot = 0; rot < 4; rot++)
	{
		bool match = true;
		for(int i = 0; i < 8; i++)
		{
			int actual = (surrounding[i] != 0) ? 0 : 1;
			int index = (i + 8 - rot * 2) % 8;
			int mV = test[index] - 48;
			if(mV != TERRAIN_MATCH_WILDCARD && actual != mV){
				match = false;
				break;
			}
		}
		if(match) {
			return (rot);
		}
	}

	return -1;
}

Tile TerrainControl::calculateTile(Tile *arr, int pX, int pY)
{
	int surrounding[8];
	surrounding[0] = getAt(arr, pX, pY - 1).id;
	surrounding[1] = getAt(arr, pX + 1, pY - 1).id;
	surrounding[2] = getAt(arr, pX + 1, pY).id;
	surrounding[3] = getAt(arr, pX + 1, pY + 1).id;
	surrounding[4] = getAt(arr, pX, pY + 1).id;
	surrounding[5] = getAt(arr, pX - 1, pY + 1).id;
	surrounding[6] = getAt(arr, pX - 1, pY).id;
	surrounding[7] = getAt(arr, pX - 1, pY - 1).id;

	std::map<const char*,int> matches;
	matches["00000100"] = 1;
	matches["00000101"] = 2;
	matches["01000101"] = 3;
	matches["01010101"] = 4;
	matches["00000919"] = 5;
	matches["01000919"] = 6;
	matches["00010919"] = 7;
	matches["10010919"] = 8;
	matches["09190919"] = 9;
	matches["00091919"] = 10;
	matches["01091919"] = 11;
	matches["09191919"] = 12;
	matches["19191919"] = 13;
	

	std::map<const char*,int>::iterator it;
	for(it = matches.begin(); it != matches.end(); ++it)
	{
		int match = compare(surrounding, (*it).first);
		if(match >= 0) {
			return Tile((*it).second, match);
		}
	}

	return Tile();
}

TerrainControl::~TerrainControl()
{
	delete terrain;

	std::map<int, TileControl*>::iterator it;
	for(it = tileControls.begin(); it != tileControls.end(); ++it)
	{
		TileControl *tileControl = (*it).second;
		delete tileControl;
	}
}

Tile TerrainControl::getAt(Tile *tiles, int xIndex, int yIndex)
{
	int x = xIndex;
	while(x < 0) { x += terrainX; }
	x = x % terrainX;
	int y = yIndex;
	while(y < 0) { y += terrainY; }
	y = y % terrainY;

	int ind = y * terrainX + x;
	return tiles[ind];
}

int TerrainControl::getTerrain(int pX, int pY)
{
	return 0;//getAt(terrain, pX, pY);
}

int TerrainControl::getTerrainPosition(Point p)
{
	int x2 = (int)(p.x / terrainSize), y2 = (int)(p.y / terrainSize);
	return getTerrain(x2, y2);
}

void TerrainControl::draw()
{
	std::map<int, TileControl*>::iterator it;
	for(it = tileControls.begin(); it != tileControls.end(); ++it)
	{
		(it->second)->draw();
	}
}
}
}
