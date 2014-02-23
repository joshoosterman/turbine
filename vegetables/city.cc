#include "Vegetables.h"

City::City(Turbine::Geom::Size size) : Level(size) {
}

City::~City() 
{
}

void City::init()
{
	Player *player = new Player();
	getView(0).setMovementStrategy(new Extras::ObjectTrackingMovementStrategy(*player, Geom::Vector(-400, -300)));
	addObject(new Car());
	addObject(player);
}

