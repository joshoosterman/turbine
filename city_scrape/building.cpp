#include "building.h"

Building::Building(CityLevel &level, int x) : SimpleGameObject(level, 10) {
    sprite = Graphics::Sprite("skyscrape/images/Building4.png", geom::Vector(0, 0), 1);
    location = geom::Point(x, 400);
    level.addLine(new HorizontalLine(geom::Point(location.x, location.y), 128));
}

void Building::Draw() {
    sprite.draw(location);
}
