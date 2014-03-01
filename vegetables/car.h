#ifndef _CAR_H
#define _CAR_H

#include "turbine/turbine.h"

class Car : public turbine::SimpleGameObject {
 public:
  Car();

  void setup();
  void step();
  void drive();
  void draw();

 private:
  turbine::geom::Vector motion;
  turbine::graphics::Sprite sprite;
};

#endif
