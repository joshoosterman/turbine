// Copyright 2011

#include "turbine/physics.h"

namespace turbine {
namespace physics {

float PhysicsObject::getMass() { return mass; }
geom::Vector PhysicsObject::getVelocity() { return velocity; }
geom::Vector PhysicsObject::getMomentum() { return getVelocity() * getMass(); }
float PhysicsObject::getMassRadius() { return massRadius; }
float PhysicsObject::getRotationalInertia() {
  return 0.5f * getMass() * getMassRadius() * getMassRadius();
}
float PhysicsObject::getAngularVelocity() { return angularVelocity; }
float PhysicsObject::getAngularMomentum() {
  return getRotationalInertia() * getAngularVelocity();
}
void PhysicsObject::step(Object *me) {
  PhysicsObject *self = reinterpret_cast<PhysicsObject *>(me);
  self->location = self->location + self->velocity;
}
void PhysicsObject::collide(GameObject *a, GameObject *b,
                            geom::Vector normal /*, Point collPoint*/) {
  PhysicsObject *self = reinterpret_cast<PhysicsObject *>(a);
  PhysicsObject *other = dynamic_cast<PhysicsObject *>(b);
  if (other == NULL) return;  // ignore collisions with non-physics objects

  geom::Point collPoint(0, 0);  // replace this when points work properly

  // local force from this collision = (p2 + m2*g) - (p1 + m1*g)
  self->localForces = self->localForces + (other->getMomentum() +
                                           other->getMass() * other->gravity) -
                      (self->getMomentum() + self->getMass() * self->gravity);
}
void PhysicsObject::endstep(Object *me) {
  PhysicsObject *self = reinterpret_cast<PhysicsObject *>(me);
  // TODO(joshoosterman): Change the following to totalForces
  // when we have force propagation
  self->velocity = self->velocity + self->localForces / self->getMass();
  self->localForces = geom::Vector(0, 0);
}
void PhysicsObject::registerPhysicsEvents() {
  this->registerStepEvent(PhysicsObject::step);
  this->registerCollisionEvent(PhysicsObject::collide);
  this->registerEndStepEvent(PhysicsObject::endstep);
}

PhysicsObject::PhysicsObject(float mass, float massradius,
                             geom::Vector gravity) {
  this->mass = mass;
  this->massRadius = massradius;
  this->gravity = gravity;
  this->fixed = false;
  this->fixedRotational = true;
  this->angularVelocity = 0;
  this->velocity = geom::Vector(0, 0);
  this->localForces = geom::Vector(0, 0);
}

void PhysicsObject::init() { registerPhysicsEvents(); }
}  // namespace physics
}  // namespace turbine
