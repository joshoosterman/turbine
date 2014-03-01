// Copyright 2011

#ifndef TURBINE_RTREE_H_
#define TURBINE_RTREE_H_

#include <set>
#include <vector>

#include "turbine/spatial_object_set.h"

namespace turbine {
namespace internal {

class BasicSpatialObjectSet : public ISpatialObjectSet {
 public:
  ~BasicSpatialObjectSet();

  void insertObject(GameObject *o);
  void removeObject(GameObject *o);
  std::set<GameObject *> queryArea(geom::BoundingBox b);

 private:
  std::set<GameObject *> objects;
};

struct Entry;
class RTreeSpatialObjectSet : public ISpatialObjectSet {
 public:
  ~RTreeSpatialObjectSet();
  RTreeSpatialObjectSet();

  void insertObject(GameObject *o);
  void removeObject(GameObject *o);
  std::set<GameObject *> queryArea(geom::BoundingBox b);

 private:
  Entry *root;
  Entry *rootSplit;

  Entry *chooseLeaf(const geom::BoundingBox &rect);
  void pickSeeds(Entry **seed1, Entry **seed2);
  Entry *splitNode(Entry *L, Entry *E);
  void adjustTree(Entry *L, Entry *LL);
  void search(const geom::BoundingBox &r, Entry *T,
              std::set<GameObject *> *results);
  Entry *findLeaf(GameObject *r, Entry *T);
  void condenseTree(Entry *L);
};
}  // namespace internal
}  // namespace turbine

#endif  // TURBINE_RTREE_H_
