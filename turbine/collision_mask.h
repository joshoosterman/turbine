#ifndef _COLLISIONMASK_H
#define _COLLISIONMASK_H

#include "turbine/geom.h"
#include "turbine/object.h"

using namespace Turbine;
using namespace Turbine::Geom;

class CollisionMask {
	GameObject *parent;
	BoundingBox bb;
public:
	virtual bool contains(const Point& p);
	virtual Vector collides(CollisionMask *other);
	virtual BoundingBox getBoundingBox();
};

class BoundingBoxCollisionMask : public CollisionMask {
public:
	bool contains(const Point& p);
	Vector collides(CollisionMask *other);
	BoundingBox getBoundingBox();
};


#endif
