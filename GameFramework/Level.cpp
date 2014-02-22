#include "Game.h"
#include "Level.h"
#include "Exceptions.h"
#include "EventManager.h"
#include "View.h"
#include "RTree.h"
#include "Object.h"
#include "Window.h"

using namespace Turbine::Internal;
using namespace Turbine::Geom;

namespace Turbine {

Level::Level()
{
	Level(Size(1000, 1000));
}

Level::Level(Size size)
{
	this->size = size;
	this->eventManager = new EventManager(this);
	this->game = &Game::getInstance();
	this->gameObjects = new BasicSpatialObjectSet();

	View *view = new View(Geom::Point(0, 0), Geom::Vector(800, 600));
	view->setEnabled(true);

	addView(view);
}

Level::~Level()
{
}

void Level::addObject(Object *o)
{
	o->level = this;
	o->init();
	GameObject *go = dynamic_cast<GameObject*>(o);
	if(go != NULL) {
		gameObjects->insertObject(go);
	} else {
		objects.insert(o);
	}
}

void Level::removeObject(Object *o) {
	GameObject *go = dynamic_cast<GameObject*>(o);
	if(go != NULL) {
		gameObjects->removeObject(go);
	} else {
		objects.erase(o);
	}
	garbage.push(o);
}

void Level::addView(View *view)
{
	views.push_back(view);
}

View &Level::getView(int index)
{
	if(index < 0 || index >= views.size()) {
		throw Exception("Invalid view index");
	}

	return *(views[index]);
}

Point Level::toWorldPosition(Point screenPosition)
{
	std::vector<View*>::iterator it;

	for (it = views.begin(); it != views.end(); ++it)
	{
		Point p1 = (*it)->getWindowPosition();
		Point p2 = p1 + (*it)->getSize();
		BoundingBox b = BoundingBox(p1.x, p2.x, p1.y, p2.y);
		if(b.contains(screenPosition)){
			return screenPosition + (*it)->getPosition();
		}
	}
	return screenPosition + (*views.begin())->getPosition();
}

std::set<GameObject *> Level::getObjects(Geom::BoundingBox b)
{
	return gameObjects->queryArea(b);
}

std::map<GameObject *, Vector> Level::getCollisions(GameObject &obj) {
	std::map<GameObject *, Vector> res;

	//ToDo - improve this
	BoundingBox bb = obj.getBoundingBox();
	bb.left -= 400;
	bb.top -= 400;
	bb.right += 400;
	bb.bottom += 400;

	std::set<GameObject *> toCheck = gameObjects->queryArea(bb);
	for (std::set<GameObject *>::iterator it = toCheck.begin(); it != toCheck.end(); ++it) {
		if (&obj != *it) {
			Vector *normal = new Vector();
			if (obj.collides(*it, normal, NULL)) {
				res[*it] = *normal;
			}
			delete normal;
		}
	}
	return res;
}

std::vector<GameObject *> Level::getCollisions(Point p) {
	std::vector<GameObject *> res;

	//ToDo - improve this
	BoundingBox bb(p.x - 500, p.x + 500, p.y - 500, p.y + 500);

	std::set<GameObject *> toCheck = gameObjects->queryArea(bb);
	for (std::set<GameObject *>::iterator it = toCheck.begin(); it != toCheck.end(); ++it) {
		if ((*it)->collides(p)) {
			res.push_back(*it);
		}
	}
	return res;
}

void Level::frame()
{
	this->game = &Game::getInstance();

	getEventManager()->performBeginStep();
	getEventManager()->performStep();
	getEventManager()->performCollisions();
	getEventManager()->performEndStep();

	std::vector<View*>::iterator it;
	for (it = views.begin(); it != views.end(); ++it)
	{
		if(!(*it)->enabled) {
			continue;
		}
		(*it)->setRenderTarget(&game->getWindow().getRenderTarget());
		(*it)->activate();
		getEventManager()->performDraw();
		(*it)->finish();
	}

	garbageCollect(10);
}

void Level::garbageCollect(int limit) {
	if (limit > 0) {
		int i = 0;
		while (i < limit && !garbage.empty()) {
			Object *toDelete = garbage.front();
			garbage.pop();
			delete toDelete;
			i++;
		}
	} else {
		while (!garbage.empty()) {
			Object *toDelete = garbage.front();
			garbage.pop();
			delete toDelete;
		}
	}
}


EventManager *Level::getEventManager() {
	return this->eventManager;
}

}
