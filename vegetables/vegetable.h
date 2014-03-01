#ifndef _VEGETABLE_H
#define _VEGETABLE_H

#include "turbine/turbine.h"

class Vegetable : public turbine::SimpleGameObject {
 public:
  Vegetable(turbine::geom::Point location);

  void setup();
  void step(turbine::Object *me);
  void draw();

  static void collide(turbine::GameObject *me, turbine::GameObject *other,
                      turbine::geom::Vector normal);

 private:
  turbine::graphics::Sprite sprite1, sprite2;
  bool dead;
  turbine::audio::Sound death;
};

#endif
