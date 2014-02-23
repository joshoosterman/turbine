#include "Physics.h"

namespace Turbine {
namespace Physics {

float PhysicsObject::getMass() {
	return mass;
}
Vector PhysicsObject::getVelocity() {
	return velocity;
}
Vector PhysicsObject::getMomentum() {
	return getVelocity() * getMass();
}
float PhysicsObject::getMassRadius() {
	return massRadius;
}
float PhysicsObject::getRotationalInertia() {
	return 0.5f * getMass() * getMassRadius() * getMassRadius();
}
float PhysicsObject::getAngularVelocity() {
	return angularVelocity;
}
float PhysicsObject::getAngularMomentum() {
	return getRotationalInertia() * getAngularVelocity();
}
void PhysicsObject::step(Object *me) {
	PhysicsObject *self = (PhysicsObject *)me;
	self->location += self->velocity;
}
void PhysicsObject::collide(GameObject *a, GameObject *b, Vector normal/*, Point collPoint*/) {
	PhysicsObject *self = (PhysicsObject *)a;
	PhysicsObject *other = dynamic_cast<PhysicsObject *>(b);
	if (other == NULL) return; // ignore collisions with non-physics objects

	Point collPoint(0,0); // replace this when points work properly

	// local force from this collision = (p2 + m2*g) - (p1 + m1*g)
	self->localForces += (other->getMomentum() + other->getMass() * other->gravity)
		- (self->getMomentum() + self->getMass() * self->gravity);
}
void PhysicsObject::endstep(Object *me) {
	PhysicsObject *self = (PhysicsObject *)me;
	// TODO: Change the following to totalForces when we have force propagation
	self->velocity += self->localForces / self->getMass();
	self->localForces = Vector(0,0);
}
void PhysicsObject::registerPhysicsEvents() {
	this->registerStepEvent(PhysicsObject::step);
	this->registerCollisionEvent(PhysicsObject::collide);
	this->registerEndStepEvent(PhysicsObject::endstep);
}

PhysicsObject::PhysicsObject(float mass, float massradius, Vector gravity) {
	this->mass = mass;
	this->massRadius = massradius;
	this->gravity = gravity;
	this->fixed = false;
	this->fixedRotational = true;
	this->angularVelocity = 0;
	this->velocity = Vector(0,0);
	this->localForces = Vector(0,0);
}

void PhysicsObject::init()
{
	registerPhysicsEvents();
}
}
}
