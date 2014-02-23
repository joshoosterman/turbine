#ifndef _RTREE_H
#define _RTREE_H

#include "turbine/spatial_object_set.h"
#include <set>
#include <vector>

using namespace Turbine::Geom;

namespace Turbine {
namespace Internal {

class BasicSpatialObjectSet : public ISpatialObjectSet
{
public:
	~BasicSpatialObjectSet();

	void insertObject(GameObject *o);
	void removeObject(GameObject *o);
	std::set<GameObject *> queryArea(BoundingBox b);
private:
	std::set<GameObject *> objects;
};

struct Entry;
class RTreeSpatialObjectSet : public ISpatialObjectSet
{
public:
	~RTreeSpatialObjectSet();
	RTreeSpatialObjectSet();

	void insertObject(GameObject *o);
	void removeObject(GameObject *o);
	std::set<GameObject *> queryArea(BoundingBox b);
private:
	Entry *root;
	Entry *rootSplit;

	Entry *chooseLeaf(BoundingBox &rect);
	void pickSeeds(Entry ** seed1, Entry ** seed2);
	Entry *splitNode(Entry *L, Entry *E);
	void adjustTree(Entry *L, Entry *LL);
	void search(BoundingBox &r, Entry *T, std::set<GameObject *> &results);
	Entry *findLeaf(GameObject *r, Entry *T);
	void condenseTree(Entry *L);
};
}
}

#endif
