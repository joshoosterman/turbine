#include "Vegetables.h"

#include <string>
#include <sstream>
#include <cstdio>
#include <math.h>
#include <typeinfo>

int main(int argc, char* args[])
{
	Window window("Planet of the Vegetables", Geom::Size(800, 600));
	Game game(window);
	game.setBaseResourcePath("potv");

	City *city = LevelLoader::load("citybeta");
    game.run(*city);

    return 0;
}

