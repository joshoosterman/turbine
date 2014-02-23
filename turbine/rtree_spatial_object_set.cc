#include "RTree.h"
#include "Object.h"

#include <algorithm>
#include <vector>

#define M 3
#define INF 999999999

using namespace Turbine::Geom;

/*namespace Turbine {
	namespace Internal {
		struct Entry {
			GameObject *obj;
			int count;
			Entry *parent;
			Entry *children[M];
			void init() {
				count = 0;
				parent = NULL;
				for (int i = 0; i < M; i++) {
					children[i] = NULL;
				}
			}
			Entry() {
				init();
			}
			Entry(GameObject *obj) {
				init();
				this->obj = obj;
			}
			bool leaf() {
				for (int i = 0; i < count; i++) {
					if (children[i]->count>0) return false;
				}
				return true;
			}
			BoundingBox bbox() {
				return obj->getBoundingBox();
			}
		};

		RTreeSpatialObjectSet::RTreeSpatialObjectSet() {
			root = NULL;
			rootSplit = NULL;
		}

		RTreeSpatialObjectSet::~RTreeSpatialObjectSet() { }

		Entry *RTreeSpatialObjectSet::ChooseLeaf(BoundingBox &rect) {
			Entry *N = root;
			while (!N->leaf()) {
				// find child that will require minimum change to encompass this BoundingBox
				float minChange = INF;
				float minArea = INF;
				Entry *min = NULL;
				for (int i = 0; i < N->count; i++) {
					float area = N->children[i]->bbox().Area();
					float inflatedarea = N->children[i]->bbox().ExpandToInclude(rect).Area();
					if (inflatedarea - area < minChange || (inflatedarea - area == minChange && minArea < minArea)) {
						minChange = inflatedarea - area;
						minArea = area;
						min = N->children[i];
					}
				}
				N = min;
			}
			return N;
		}

		void RTreeSpatialObjectSet::PickSeeds(Entry ** seed1, Entry ** seed2) {
			// Select two entries to be the first elements of the groups
			// TODO: Write LinearPickSeeds
		}

		Entry *RTreeSpatialObjectSet::SplitNode(Entry *L, Entry *E) {
			// TODO: Write SplitNode
			Entry *LL = NULL;

			return LL;
		}

		void RTreeSpatialObjectSet::AdjustTree(Entry *L, Entry *LL) {
			// TODO: Write AdjustTree
		}

		void RTreeSpatialObjectSet::InsertObject(GameObject *obj) {
			Entry *L = ChooseLeaf(obj->getBoundingBox());
			Entry *LL = NULL;
			if (L->count < M) {
				L->children[L->count] = new Entry(obj);
				L->children[L->count]->parent = L;
				L->count++;
			} else {
				LL = SplitNode(L, new Entry(obj));
			}
			AdjustTree(L,LL);

			// If root just split, create new root
			// whose children are the two resulting nodes
			if (rootSplit) {
				Entry *newRoot = new Entry();
				newRoot->bbox().ExpandToInclude(root->bbox());
				newRoot->bbox().ExpandToInclude(rootSplit->bbox());
				newRoot->children[0] = root;
				newRoot->children[1] = rootSplit;
				newRoot->count = 2;
				root->parent = newRoot;
				rootSplit->parent = newRoot;
				root = newRoot;
				rootSplit = NULL;
			}
		}

		std::set<GameObject *> RTreeSpatialObjectSet::QueryArea(BoundingBox b) {
			std::set<GameObject *> res;
			Search(b, root, res);
			return res;
		}

		void RTreeSpatialObjectSet::Search(BoundingBox &r, Entry *T, std::set<GameObject *> &results) {
			if (!T->leaf())
				for (int i = 0; i < T->count; i++)
					if (r.Intersects(T->children[i]->bbox()))
						Search(r, T->children[i], results);
					else
						for (int i = 0; i < T->count; i++)
							if (r.Intersects(T->children[i]->bbox()))
								results.insert(T->children[i]->obj);
		}

		Entry *RTreeSpatialObjectSet::FindLeaf(GameObject *o, Entry *T) {
			Entry *result = NULL;
			if (!T->leaf())
				for (int i = 0; i < T->count && result == NULL; i++)
					if (o->getBoundingBox().Intersects(T->children[i]->bbox()))
						result = FindLeaf(o, T->children[i]);
					else
						for (int i = 0; i < T->count && result == NULL; i++)
							if (o == T->children[i]->obj)
								result = T;
			return result;
		}

		void RTreeSpatialObjectSet::CondenseTree(Entry *L) {
			// TODO: Write CondenseTree
		}

		void RTreeSpatialObjectSet::RemoveObject(GameObject *o) {
			Entry *L = FindLeaf(o,root);
			for (int i = 0; i < L->count; i++) {
				if (o == L->children[i]->obj) {
					delete L->children[i];
					for (int j = i + 1; j < L->count; j++) {
						L->children[j-1] = L->children[j];
					}
					L->count--;
					break;
				}
			}
			CondenseTree(L);
			if (root->count == 1) {
				Entry *oldRoot = root;
				root = root->children[0];
				delete oldRoot;
			}
		}
	}
}*/
