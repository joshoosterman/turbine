#ifndef _LEVEL_H
#define _LEVEL_H

#include <vector>
#include <set>
#include <map>
#include <queue>

#include "Classes.h"
#include "Geom.h"

namespace Turbine {

/// Represents a single screen/area of play in a computer game. Maintains
/// a spatial index of game objects for collision checking etc. Only one
/// level is active at a time, and an object may only exist in one level.
class Level {
public:
	/// Constructor
	Level();
	Level(Geom::Size size);

	/// Destructor
	~Level();

	/// Adds an object to the level. If the Object is a GameObject, it
	/// will be indexed accordingly
	void addObject(Object *o);

	/// Removes an object from the level
	void removeObject(Object *o);

	/// Adds a view to the level. The level is rendered for every view
	/// each frame
	void addView(View *view);

	/// Removes a view from the level
	void removeView(View *view);

	/// Get the nth view
	View &getView(int index);

	/// Forces the level to clean up disposed objects, up to the specified limit.
	void garbageCollect(int limit);

	/// Forces the level to clean up disposed objects.
	void garbageCollect();

	/// Converts a window position to a position in the level. If the window
	/// position intersects multiple viewports, the
	Geom::Point toWorldPosition(Geom::Point screenPosition);

	/// Finds all of the objects inside a given bounding box
	std::set<GameObject *> getObjects(Geom::BoundingBox b);

	/// Finds all of the objects that collide with the given
	/// GameObject
	std::map<GameObject *, Geom::Vector> getCollisions(GameObject &obj);

	/// Finds all of the objects that collide with the given
	/// point in the level
	std::vector<GameObject *> getCollisions(Geom::Point p);



	/// Returns a pointer to the event manager for this level. Used
	/// to register events.
	Internal::EventManager *getEventManager();

private:

		/// Executes a frame of the game, calling all events and rendering
	/// to the screen
	 friend Game void frame();

	std::vector<View *> views;
	std::set<Object *> objects;
	ISpatialObjectSet *gameObjects;
	Internal::EventManager *eventManager;
	Game *game;
	std::queue<Object *> garbage;
	Geom::Size size;
};

}
#endif
