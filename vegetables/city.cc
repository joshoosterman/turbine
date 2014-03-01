#include "vegetables/vegetables.h"

City::City(turbine::geom::Size size) : Level(size) {}

City::~City() {}

void City::init() {
  Player *player = new Player();
  getView(0)
      .setMovementStrategy(new turbine::extras::ObjectTrackingMovementStrategy(
          *player, turbine::geom::Vector(-400, -300)));
  addObject(new Car());
  addObject(player);
}
