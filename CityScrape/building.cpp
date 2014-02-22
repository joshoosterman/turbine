#include "building.h"

Building::Building(CityLevel &level, int x) : SimpleGameObject(level, 10) {
    sprite = Graphics::Sprite("skyscrape/images/Building4.png", Geom::Vector(0, 0), 1);
    location = Geom::Point(x, 400);
    level.addLine(new HorizontalLine(Geom::Point(location.x, location.y), 128));
}

void Building::Draw() {
    sprite.draw(location);
}
