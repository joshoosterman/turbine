#include "Vegetables.h"
#include <sstream>

#define MIN(X,Y) ((X) < (Y) ? : (X) : (Y))

TileControl::TileControl(Level& level, int tilesX, int tilesY, int tileSize, std::string contentDir, int* tiles) 
: GameObject(level)
{
	this->tilesX = tilesX;
	this->tilesY = tilesY;
	this->tileSize = tileSize;

	this->tiles = new int[tilesX * tilesY];

	for(int i = 0; i < tilesX * tilesY; i++)
	{
		int t = tiles[i];
		this->tiles[i] = t;

		if(t < 0) {
			continue;
		}

		t %= 100;
		if(images.find(t) == images.end()){
			std::string s;
			std::stringstream out;
			out << contentDir << "/" << t << ".png";
			s = out.str();

			Image* image = ResourceManager::getInstance()->Use<Image>(s);
			images[t] = image;
		}
	}

	registerDrawEvent(level, &TileControl::draw, 0);
}

TileControl::~TileControl()
{
	delete tiles;
}

int TileControl::getTile(int pX, int pY)
{
	int x = pX;
	x = x > 0 ? x : 0;
	x = x < tilesX ? x : tilesX - 1;
    int y = pY;
	y = y > 0 ? y : 0;
	y = y < tilesY ? y : tilesY - 1;

	int ind = y * tilesX + x;
	return tiles[ind];
}

int TileControl::getTilePosition(Point p)
{
	int x2 = p.x / tileSize, y2 = p.y / tileSize;
	return getTile(x2, y2);
}

void TileControl::draw(Object *_me, View *view)
{
	TileControl *me = (TileControl*) _me;
	Point p1 = Point(0, 0) + view->getWorldOffset();
	Point p2 = p1 + view->getSize();

	int leftX = (int) (p1.x / me->tileSize);
    int rightX = (int) (p2.x / me->tileSize + 1);
    int topY = (int) (p1.y / me->tileSize);
    int bottomY = (int) (p2.y / me->tileSize + 1);

    for (int i = leftX; i < rightX; i++)
    {
		for (int j = topY; j < bottomY; j++)
        {
			int t = me->getTile(i, j);
			if(t >= 0) {
				int rot = t / 100;
				t = t % 100;
				Image* image = me->images[t];
				view->drawRotated(image, Point(i * me->tileSize, j * me->tileSize), Point(me->tileSize / 2, me->tileSize / 2), rot * 90, 1);
				//view->draw(image, Point(i * me->tileSize, j * me->tileSize));
			}
		}
    }
}

TerrainControl::TerrainControl(Level& level, int tilesX, int tilesY, int tileSize, std::string contentDir, int* tiles) 
: GameObject(level)
{
	this->tilesX = tilesX;
	this->tilesY = tilesY;
	this->tileSize = tileSize;

	int size = tilesX * tilesY;
	this->tiles = new int[size];

	for(int i = 0; i < size; i++)
	{
		int t = tiles[i];
		this->tiles[i] = t;

		if(tileControls.find(t) == tileControls.end()){
			std::string tcdir;
			std::stringstream out;
			out << contentDir << "/" << t;
			tcdir = out.str();

			int *tls = new int[size];
			for(int j = 0; j < size; j++)
			{
				if(tiles[j] == t) {
					tls[j] = 0;
				} else if(tiles[j] < t) {
					tls[j] = -2;
				} else {
					tls[j] = -1;
				}
			}
			for(int j = 0; j < size; j++)
			{
				if(tls[j] == -2) {
					int x = j % tilesX;
					int y = j / tilesY;
					tls[j] = calculateTile(tls, x, y);
				}
			}

			TileControl* tc = new TileControl(level, tilesX, tilesY, tileSize, tcdir, tls);
			tileControls[t] = tc;
			delete tls;
		}
	}

	registerDrawEvent(level, &TerrainControl::draw, 0);
}

int TerrainControl::calculateTile(int* arr, int pX, int pY)
{
	int surrounding[8];
	surrounding[0] = getAt(arr, pX, pY - 1);
	surrounding[1] = getAt(arr, pX + 1, pY - 1);
	surrounding[2] = getAt(arr, pX + 1, pY);
	surrounding[3] = getAt(arr, pX + 1, pY + 1);
	surrounding[4] = getAt(arr, pX, pY + 1);
	surrounding[5] = getAt(arr, pX - 1, pY + 1);
	surrounding[6] = getAt(arr, pX - 1, pY);
	surrounding[7] = getAt(arr, pX - 1, pY - 1);

	std::map<char*,int> matches;
	matches["00000100"] = 1;
	matches["00000001"] = 201;
	matches["01000000"] = 301;
	matches["00010000"] = 401;
	matches["00000010"] = 5;
	matches["10000000"] = 105;
	matches["00100000"] = 205;
	matches["00001000"] = 305;
	

	std::map<char*,int>::iterator it;
	for(it = matches.begin(); it != matches.end(); ++it)
	{
		bool match = true;
		for(int i = 0; i < 8; i++)
		{
			int actual = (surrounding[i] != 0) ? 0 : 1;
			int mV = (*it).first[i] - 48;
			if(actual != mV){
				match = false;
				break;
			}
		}
		if(match) {
			return (*it).second;
		}
	}

	return -1;
}

TerrainControl::~TerrainControl()
{
	delete tiles;
}

int TerrainControl::getAt(int* tiles, int pX, int pY)
{
	int x = pX;
	x = x > 0 ? x : 0;
	x = x < tilesX ? x : tilesX - 1;
    int y = pY;
	y = y > 0 ? y : 0;
	y = y < tilesY ? y : tilesY - 1;

	int ind = y * tilesX + x;
	return tiles[ind];
}

int TerrainControl::getTerrain(int pX, int pY)
{
	return getAt(tiles, pX, pY);
}

int TerrainControl::getTerrainPosition(Point p)
{
	int x2 = p.x / tileSize, y2 = p.y / tileSize;
	return getTerrain(x2, y2);
}

void TerrainControl::draw(Object *_me, View *view)
{
	TerrainControl *self = (TerrainControl*) _me;
	std::map<int, TileControl*>::iterator it;
	for(it = self->tileControls.begin(); it != self->tileControls.end(); ++it)
    {
		TileControl::draw((Object*) it->second, view);
	}
}