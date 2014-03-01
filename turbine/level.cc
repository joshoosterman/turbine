// Copyright 2011

#include "turbine/event_manager.h"
#include "turbine/exceptions.h"
#include "turbine/game.h"
#include "turbine/level.h"
#include "turbine/object.h"
#include "turbine/rtree.h"
#include "turbine/view.h"
#include "turbine/window.h"

namespace turbine {

Level::Level() { Init(geom::Size(1000, 1000)); }

Level::Level(geom::Size size) { Init(size); }

void Level::Init(geom::Size size) {
  this->size = size;
  this->eventManager = new internal::EventManager(this);
  this->game = &Game::getInstance();
  this->gameObjects = new internal::BasicSpatialObjectSet();
  View *view = new View(geom::Point(0, 0), geom::Vector(800, 600));
  view->setEnabled(true);

  addView(view);
}

Level::~Level() {}

void Level::addObject(Object *o) {
  o->level = this;
  o->init();
  GameObject *go = dynamic_cast<GameObject *>(o);
  if (go != NULL) {
    gameObjects->insertObject(go);
  } else {
    objects.insert(o);
  }
}

void Level::removeObject(Object *o) {
  GameObject *go = dynamic_cast<GameObject *>(o);
  if (go != NULL) {
    gameObjects->removeObject(go);
  } else {
    objects.erase(o);
  }
  garbage.push(o);
}

void Level::addView(View *view) { views.push_back(view); }

View &Level::getView(int index) {
  if (index < 0 || index >= views.size()) {
    throw Exception("Invalid view index");
  }

  return *(views[index]);
}

geom::Point Level::toWorldPosition(geom::Point screenPosition) {
  std::vector<View *>::iterator it;

  for (it = views.begin(); it != views.end(); ++it) {
    geom::Point p1 = (*it)->getWindowPosition();
    geom::Point p2 = p1 + (*it)->getSize();
    geom::BoundingBox b(p1.x, p2.x, p1.y, p2.y);
    if (b.contains(screenPosition)) {
      return screenPosition + (*it)->getPosition();
    }
  }
  return screenPosition + (*views.begin())->getPosition();
}

std::set<GameObject *> Level::getObjects(geom::BoundingBox b) {
  return gameObjects->queryArea(b);
}

std::map<GameObject *, geom::Vector> Level::getCollisions(
    const GameObject &obj) {
  std::map<GameObject *, geom::Vector> res;

  // TODO(joshoosterman): improve this
  geom::BoundingBox bb = obj.getBoundingBox();
  bb.left -= 400;
  bb.top -= 400;
  bb.right += 400;
  bb.bottom += 400;

  std::set<GameObject *> toCheck = gameObjects->queryArea(bb);
  for (std::set<GameObject *>::iterator it = toCheck.begin();
       it != toCheck.end(); ++it) {
    if (&obj != *it) {
      geom::Vector normal;
      if (obj.collides(*it, &normal, NULL)) {
        res[*it] = normal;
      }
    }
  }
  return res;
}

std::vector<GameObject *> Level::getCollisions(geom::Point p) {
  std::vector<GameObject *> res;

  geom::BoundingBox bb(p.x - 500, p.x + 500, p.y - 500, p.y + 500);

  std::set<GameObject *> toCheck = gameObjects->queryArea(bb);
  for (std::set<GameObject *>::iterator it = toCheck.begin();
       it != toCheck.end(); ++it) {
    if ((*it)->collides(p)) {
      res.push_back(*it);
    }
  }
  return res;
}

void Level::frame() {
  this->game = &Game::getInstance();

  getEventManager()->performBeginStep();
  getEventManager()->performStep();
  getEventManager()->performCollisions();
  getEventManager()->performEndStep();

  std::vector<View *>::iterator it;
  for (it = views.begin(); it != views.end(); ++it) {
    if (!(*it)->enabled) {
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

internal::EventManager *Level::getEventManager() { return this->eventManager; }

}  // namespace turbine
