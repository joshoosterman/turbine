#ifndef _PLAYER_H
#define _PLAYER_H

#include "turbine/turbine.h"
#include "vegetables/car.h"

class Player : public turbine::SimpleGameObject {
 public:
  Player();

  void setup();
  void step();
  void draw();
  static void _collide(turbine::GameObject *me, turbine::GameObject *other,
                       turbine::geom::Vector normal);

 private:
  void collide(turbine::GameObject *other, turbine::geom::Vector normal);

  void footMovement();
  void carMovement();

  bool inCar;
  Car *car;

  turbine::geom::Vector motion;
  turbine::graphics::Sprite current;
  turbine::graphics::Sprite up, down, left, right;
};

#endif
