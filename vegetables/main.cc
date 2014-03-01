#include <string>
#include <sstream>
#include <cstdio>
#include <math.h>
#include <typeinfo>

#include "vegetables/vegetables.h"

int main(int argc, char* args[]) {
  turbine::Window window("Planet of the Vegetables",
                         turbine::geom::Size(800, 600));
  turbine::Game game(window);
  game.setBaseResourcePath("potv");

  City* city = LevelLoader::load("citybeta");
  game.run(city);
  delete city;

  return 0;
}
