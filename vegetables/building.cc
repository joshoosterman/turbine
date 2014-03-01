#include "vegetables/vegetables.h"

Building::Building(turbine::geom::Point pos) : SimpleGameObject(10) {
  location = pos;
}

void Building::setup() {
  std::string path = "images/buildings/building_blue.png";
  std::string maskPath = "images/buildings/mask_256128.png";
  /*std::stringstream out;
 	out << resourcePath << "/" << path;
 	return out.str();*/

  sprite = turbine::graphics::Sprite(path, turbine::geom::Point(256, 256), 1);
  mask = turbine::graphics::Image(maskPath);
  mask.setOrigin(turbine::geom::Point(256, 128));
  createCollisionMask(mask);
}

void Building::draw() {
  sprite.draw(location);
#ifdef SHOW_MASKS
  drawDebugInfo(true);
#endif
}
