#ifndef _SPATIALOBJECTSET_H
#define _SPATIALOBJECTSET_H

#include <set>
#include <vector>

#include "Classes.h"

namespace Turbine {

/// Used to store objects with positioned in space, optimized for spatial queries
class ISpatialObjectSet
{
public:
	virtual ~ISpatialObjectSet() {};
	virtual void insertObject(GameObject *o) = 0;
	virtual void removeObject(GameObject *o) = 0;
	virtual std::set<GameObject *> queryArea(Geom::BoundingBox b) = 0;
};
}

#endif
