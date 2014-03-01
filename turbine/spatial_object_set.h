// Copyright 2011

#ifndef TURBINE_SPATIAL_OBJECT_SET_H_
#define TURBINE_SPATIAL_OBJECT_SET_H_

#include <set>
#include <vector>

#include "turbine/classes.h"

namespace turbine {

/// Used to store objects with positioned in space, optimized for spatial
/// queries
class ISpatialObjectSet {
 public:
  virtual ~ISpatialObjectSet() {}
  virtual void insertObject(GameObject *o) = 0;
  virtual void removeObject(GameObject *o) = 0;
  virtual std::set<GameObject *> queryArea(geom::BoundingBox b) = 0;
};
}  // namespace turbine

#endif  // TURBINE_SPATIAL_OBJECT_SET_H_
