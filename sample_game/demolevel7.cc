// Copyright 2011

#include "sample_game/sample.h"
#include "math.h"

class PhysicsBall : public PhysicsObject {
 public:
  Sprite sprite;

  static void draw(Object *me) {
    PhysicsBall *self = (PhysicsBall *)me;
    self->sprite.draw(self->location);
  }

  PhysicsBall() : PhysicsObject(10, 4) {
    location = Point(50, 50);
    sprite = Sprite("sample/images/pinball.png", Point(8, 8), 2);
    sprite.setFrame(0);
    //Vector vector;
    //Image *mask = sprite->createImage(0, 0, 1, &vector);
    //setCollisionMask(mask, vector);
    createCollisionMask(sprite);
  }

  void init() { registerDrawEvent(&PhysicsBall::draw, 30); }
};

DemoLevel7::DemoLevel7() : DemoLevel("Simple Physics", 1, 1) {}

void DemoLevel7::init() { addObject(new PhysicsBall()); }
