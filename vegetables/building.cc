#include "Vegetables.h"

Building::Building(Point pos) : SimpleGameObject(10)
{
	location = pos;
}

void Building::setup()
{
	std::string path = "images/buildings/building_blue.png";
	std::string maskPath = "images/buildings/mask_256128.png";
	/*std::stringstream out;
	out << resourcePath << "/" << path;
	return out.str();*/

	sprite = Sprite(path, Point(256, 256), 1);
	mask = Image(maskPath);
	mask.setOrigin(Point(256, 128));
	createCollisionMask(mask);
}

void Building::draw() {
	sprite.draw(location);
#ifdef SHOW_MASKS
	drawDebugInfo(true);
#endif
}
