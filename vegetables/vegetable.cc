#include <typeinfo>

#include "vegetables/vegetables.h"

Vegetable::Vegetable(turbine::geom::Point location) : SimpleGameObject(10) {
  this->location = location;
}

void Vegetable::setup() {
  dead = false;
  sprite1 = turbine::graphics::Sprite("images/gunBanana.png",
                                      turbine::geom::Point(16, 42), 1);
  sprite2 = turbine::graphics::Sprite("images/splatterBanana.png",
                                      turbine::geom::Point(10, 30), 1);
  death = turbine::audio::Sound("sounds/wa.wav");

  registerCollisionEvent(&Vegetable::collide);

  bbox = turbine::geom::BoundingBox(-16, 16, -42, 0);
}

void Vegetable::step(turbine::Object *me) {}

void Vegetable::draw() {
  (dead ? sprite2 : sprite1).draw(location);
#ifdef SHOW_MASKS
  drawDebugInfo(true);
#endif
}

void Vegetable::collide(turbine::GameObject *me, turbine::GameObject *other,
                        turbine::geom::Vector normal) {
  Vegetable *self = (Vegetable *)me;
  if (!self->dead) {
    self->death.play();
    printf("Collision succeeded between %s and %s\n", typeid(*me).name(),
           typeid(*other).name());
  }
  self->dead = true;
}
