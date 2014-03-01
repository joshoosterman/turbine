#ifndef _BUILDING_H
#define _BUILDING_H

#include "turbine/turbine.h"

class Building : public turbine::SimpleGameObject {
 public:
  Building(turbine::geom::Point pos);

  void setup();
  void draw();

 private:
  turbine::graphics::Sprite sprite;
  turbine::graphics::Image mask;
};

#endif
