#ifndef _PHYSICS_H
#define _PHYSICS_H

#include <cstdlib>

#include "classes.h"
#include "turbine/object.h"

using namespace Turbine::Geom;

namespace Turbine {
namespace Physics {

/// A specialization of GameObject for objects with physical properties (mass, gravity, etc)
class PhysicsObject : public GameObject {
private:
	float mass;
	Geom::Vector velocity;
	float massRadius;
	float angularVelocity;
	Vector localForces;
protected:
	void init();
public:
	PhysicsObject(float mass, float massradius, Vector gravity = Vector(0, 0));

	bool fixed;
	bool fixedRotational;
	Vector gravity;
	float getMass();
	Vector getVelocity();
	Vector getMomentum();
	float getMassRadius();
	float getRotationalInertia();
	float getAngularVelocity();
	float getAngularMomentum();
	static void step(Object *me);
	static void endstep(Object *me);
	static void collide(GameObject *a, GameObject *b, Vector normal/*, Point collPoint*/);
	void registerPhysicsEvents();
};

}
}

#endif
