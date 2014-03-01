#ifndef _BUILDING_H_
#define _BUILDING_H_

#include "turbine/turbine.h"
#include "turbine/level.h"

class Building : public Turbine::SimpleGameObject {
 private:
  turbine::graphics::Sprite sprite;

 public:
  Building(CityLevel &level, int x);
  void Draw();
};

#endif
