// Copyright 2011

#ifndef TURBINE_PHYSICS_H_
#define TURBINE_PHYSICS_H_

#include <cstdlib>

#include "turbine/classes.h"
#include "turbine/object.h"

namespace turbine {
namespace physics {

/// A specialization of GameObject for objects with physical properties (mass,
/// gravity, etc)
class PhysicsObject : public GameObject {
 private:
  float mass;
  geom::Vector velocity;
  float massRadius;
  float angularVelocity;
  geom::Vector localForces;

 protected:
  void init();

 public:
  PhysicsObject(float mass, float massradius,
                geom::Vector gravity = geom::Vector(0, 0));

  bool fixed;
  bool fixedRotational;
  geom::Vector gravity;
  float getMass();
  geom::Vector getVelocity();
  geom::Vector getMomentum();
  float getMassRadius();
  float getRotationalInertia();
  float getAngularVelocity();
  float getAngularMomentum();
  static void step(Object *me);
  static void endstep(Object *me);
  static void collide(GameObject *a, GameObject *b,
                      geom::Vector normal /*, geom::Point collPoint*/);
  void registerPhysicsEvents();
};

}  // namespace physics
}  // namespace turbine

#endif  // TURBINE_PHYSICS_H_
