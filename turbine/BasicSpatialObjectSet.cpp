#include "RTree.h"
#include "Object.h"

namespace Turbine {
namespace Internal {

BasicSpatialObjectSet::~BasicSpatialObjectSet() {}

void BasicSpatialObjectSet::insertObject(GameObject *o)
{
	objects.insert(o);
}

void BasicSpatialObjectSet::removeObject(GameObject *o)
{
	objects.erase(o);
}

std::set<GameObject *> BasicSpatialObjectSet::queryArea(BoundingBox b)
{
	std::set<GameObject *> result;
	std::set<GameObject *>::iterator it;
	for(it = objects.begin(); it != objects.end(); it++)
	{
		if(b.contains((*it)->getLocation())) {
			result.insert(*it);
		}
	}
	return result;
}
}
}
