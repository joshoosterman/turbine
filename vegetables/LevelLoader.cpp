#include "Vegetables.h"
#include <fstream>
#include <vector>
#include <sstream>

std::vector<std::string> split(std::string line, char delimeter) {
	std::vector<std::string> result;

	std::stringstream lineStream(line);
    std::string token;
    while(std::getline(lineStream, token, delimeter)) {
		result.push_back(token);
    }
	return result;
}

int toInt(std::string token) {
	std::istringstream stream(token);
	int val;
	stream >> val;
	return val;
}

City *LevelLoader_create(std::string dir, int& width, int& height) {
	std::string metaPath = dir + "meta.dat";
	std::ifstream metaFile(metaPath.c_str());
	if(!metaFile.is_open()) {
		throw Exception("Corrupt or missing level files");
	}

	std::string line;
	getline(metaFile, line);
	width = toInt(split(line, ',')[0]);
	height = toInt(split(line, ',')[1]);
    
	return new City(Turbine::Geom::Size(width * 128, height * 128));
}

void LevelLoader_loadTerrain(std::string dir, City *city, int width, int height) {
	std::string terrainPath = dir + "terrain.dat";
	std::ifstream terrainFile(terrainPath.c_str());
	if(!terrainFile.is_open()) {
		throw Exception("Corrupt or missing level files");
	}

	int* terrain = new int[width * height];

	for(int y = 0; y < height; y++) {
		std::string line;
		getline(terrainFile, line);
		std::vector<std::string> tokens = split(line, ',');
		for(int x = 0; x < width; x++) {
			terrain[x + y * height] = toInt(tokens[x]);
		}
	}
	city->addObject(new TerrainControl(width, height, 128, "images/terrain", terrain));
	delete terrain;
}

void LevelLoader_loadObjects(std::string dir, City *city)
{
	std::string objectsPath = dir + "objects.dat";
	std::ifstream objectsFile(objectsPath.c_str());
	if(!objectsFile.is_open()) {
		throw Exception("Corrupt or missing level files");
	}

	std::string line;
	while(!objectsFile.eof()) {
		getline(objectsFile, line);
		std::vector<std::string> tokens = split(line, ',');
		int x = toInt(split(line, ',')[1]);
		int y = toInt(split(line, ',')[2]);
		city->addObject(new Building(Point(x, y)));
	}

	/*for(int a = 1; a < 7; a++)
    {
        city->addObject(new Vegetable(Point(a * 100, a * 100)));
    }*/
}

City *LevelLoader::load(std::string name) {
	std::string dir = Game::getInstance().getResourcePath("levels") + "/" + name + "/";

	int width, height;
	City *city = LevelLoader_create(dir, width, height);
	LevelLoader_loadTerrain(dir, city, width, height);
	LevelLoader_loadObjects(dir, city);
	city->init();
	return city;
}