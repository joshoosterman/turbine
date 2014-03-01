// Copyright 2011

#include "turbine/object.h"
#include "turbine/rtree.h"

namespace turbine {
namespace internal {

BasicSpatialObjectSet::~BasicSpatialObjectSet() {}

void BasicSpatialObjectSet::insertObject(GameObject *o) { objects.insert(o); }

void BasicSpatialObjectSet::removeObject(GameObject *o) { objects.erase(o); }

std::set<GameObject *> BasicSpatialObjectSet::queryArea(geom::BoundingBox b) {
  std::set<GameObject *> result;
  std::set<GameObject *>::iterator it;
  for (it = objects.begin(); it != objects.end(); it++) {
    if (b.contains((*it)->getLocation())) {
      result.insert(*it);
    }
  }
  return result;
}

}  // namespace internal
}  // namespace turbine
