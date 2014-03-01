// Copyright 2011

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Window/Event.hpp"

#include "turbine/event_manager.h"
#include "turbine/game.h"
#include "turbine/geom.h"
#include "turbine/input_manager.h"
#include "turbine/level.h"
#include "turbine/object.h"

namespace turbine {
namespace internal {

void MouseEventRegistration::operator()(sf::Event e) const {
  input::MouseEvent ev;
  callback(object, ev);
}

void KeyboardEventRegistration::operator()(sf::Event e) const {
  input::KeyEvent ev;
  ev.key = e.key.code;
  callback(object, ev);
}

bool operator<(const DrawEventRegistration &a, const DrawEventRegistration &b) {
  if (a.object == b.object) {
    return a.callback < b.callback;
  }
  return a.object < b.object;
}

bool operator<(const StepEventRegistration &a, const StepEventRegistration &b) {
  if (a.object == b.object) {
    return a.callback < b.callback;
  }
  return a.object < b.object;
}

bool operator<(const CollisionEventRegistration &a,
               const CollisionEventRegistration &b) {
  if (a.object == b.object) {
    return a.callback < b.callback;
  }
  return a.object < b.object;
}

bool operator<(const MouseEventRegistration &a,
               const MouseEventRegistration &b) {
  if (a.object == b.object) {
    return a.callback < b.callback;
  }
  return a.object < b.object;
}

bool operator<(const KeyboardEventRegistration &a,
               const KeyboardEventRegistration &b) {
  if (a.object == b.object) {
    return a.callback < b.callback;
  }
  return a.object < b.object;
}

EventManager::EventManager(Level *level) { this->level = level; }

void EventManager::registerDrawEvent(Object *o, DrawCallback callback,
                                     int depth) {
  DrawEventRegistration reg(o, callback);
  drawCallbacks[-depth].push_back(reg);
}

void EventManager::registerBeginStepEvent(Object *o, StepCallback callback) {
  StepEventRegistration reg(o, callback);
  beginStepCallbacks.insert(reg);
}

void EventManager::registerStepEvent(Object *o, StepCallback callback) {
  StepEventRegistration reg(o, callback);
  stepCallbacks.insert(reg);
}

void EventManager::registerEndStepEvent(Object *o, StepCallback callback) {
  StepEventRegistration reg(o, callback);
  endStepCallbacks.insert(reg);
}

void EventManager::registerCollisionEvent(GameObject *o,
                                          CollisionCallback callback) {
  CollisionEventRegistration reg(o, callback);
  collisionCallbacks.insert(reg);
}

void EventManager::registerMouseEvent(GameObject *o, MouseCallback callback,
                                      sf::Event::EventType e) {
  MouseEventRegistration reg(o, callback);
  mouseCallbacks[e].insert(reg);
}

void EventManager::registerGlobalMouseEvent(Object *o, MouseCallback callback,
                                            sf::Event::EventType e) {
  MouseEventRegistration reg(o, callback);
  globalMouseCallbacks[e].insert(reg);
}

void EventManager::registerKeyboardEvent(Object *o, KeyboardCallback callback,
                                         sf::Event::EventType e) {
  KeyboardEventRegistration reg(o, callback);
  keyboardCallbacks[e].insert(reg);
}

void EventManager::unregisterDrawEvent(Object *o, DrawCallback callback,
                                       int depth) {
  DrawEventRegistration reg(o, callback);
  // TODO(joshoosterman): drawCallbacks[-depth].erase(reg);
}

void EventManager::unregisterBeginStepEvent(Object *o, StepCallback callback) {
  StepEventRegistration reg(o, callback);
  beginStepCallbacks.erase(reg);
}

void EventManager::unregisterStepEvent(Object *o, StepCallback callback) {
  StepEventRegistration reg(o, callback);
  stepCallbacks.erase(reg);
}

void EventManager::unregisterEndStepEvent(Object *o, StepCallback callback) {
  StepEventRegistration reg(o, callback);
  endStepCallbacks.erase(reg);
}

void EventManager::unregisterCollisionEvent(GameObject *o,
                                            CollisionCallback callback) {
  CollisionEventRegistration reg(o, callback);
  collisionCallbacks.erase(reg);
}

void EventManager::unregisterMouseEvent(GameObject *o, MouseCallback callback,
                                        sf::Event::EventType e) {
  MouseEventRegistration reg(o, callback);
  mouseCallbacks[e].erase(reg);
}

void EventManager::unregisterGlobalMouseEvent(Object *o, MouseCallback callback,
                                              sf::Event::EventType e) {
  MouseEventRegistration reg(o, callback);
  globalMouseCallbacks[e].erase(reg);
}

void EventManager::unregisterKeyboardEvent(Object *o, KeyboardCallback callback,
                                           sf::Event::EventType e) {
  KeyboardEventRegistration reg(o, callback);
  keyboardCallbacks[e].erase(reg);
}

typedef std::map<int, std::vector<DrawEventRegistration> >::iterator DERmapiter;
typedef std::vector<DrawEventRegistration>::iterator DERiter;

void EventManager::performDraw() {
  // This works because maps are sorted by key. Objects will be drawn in
  // ascending order of depth.
  for (DERmapiter it = drawCallbacks.begin(); it != drawCallbacks.end(); ++it) {
    for (DERiter it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
      (*it2)();
    }
  }
}

typedef std::set<StepEventRegistration>::iterator SERiter;

void EventManager::performBeginStep() {
  for (SERiter it = beginStepCallbacks.begin(); it != beginStepCallbacks.end();
       ++it) {
    (*it)();
  }
}
void EventManager::performStep() {
  for (SERiter it = stepCallbacks.begin(); it != stepCallbacks.end(); ++it) {
    (*it)();
  }
}
void EventManager::performEndStep() {
  for (SERiter it = endStepCallbacks.begin(); it != endStepCallbacks.end();
       ++it) {
    (*it)();
  }
}

typedef std::map<sf::Event::EventType,
                 std::set<MouseEventRegistration> >::iterator MERmapiter;
typedef std::set<MouseEventRegistration>::iterator MERiter;

void EventManager::performMouseEvents(sf::Event ev) {
  for (MERmapiter it = globalMouseCallbacks.begin();
       it != globalMouseCallbacks.end(); ++it) {
    if (ev.type == it->first) {
      for (MERiter it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
        (*it2)(ev);
      }
    }
  }

  geom::Point p1 = input::InputManager::getInstance()->mouseGetWindowPosition();
  // this could be done with a spatial index in future
  for (MERmapiter it = mouseCallbacks.begin(); it != mouseCallbacks.end();
       ++it) {
    if (ev.type == it->first) {
      for (MERiter it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
        // NOTE: This fixes a bug where
        // the referenced object went out of scope before the function ran,
        //   ==> Undefined behaviour
        geom::Point p = level->toWorldPosition(p1);
        if (it2->getObject()->collides(p)) {
          (*it2)(ev);
        }
      }
    }
  }
}

typedef std::map<sf::Event::EventType,
                 std::set<KeyboardEventRegistration> >::iterator KERmapiter;
typedef std::set<KeyboardEventRegistration>::iterator KERiter;

void EventManager::performKeyboardEvents(sf::Event ev) {
  for (KERmapiter it = keyboardCallbacks.begin(); it != keyboardCallbacks.end();
       ++it) {
    if (ev.type == it->first) {
      for (KERiter it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
        (*it2)(ev);
      }
    }
  }
}

typedef std::set<CollisionEventRegistration>::iterator CERiter;
typedef std::map<CollisionEventRegistration,
                 std::map<GameObject *, geom::Vector> >::iterator
    allCollMapIter;
typedef std::map<GameObject *, geom::Vector>::iterator collMapIter;

void EventManager::performCollisions() {
  std::map<CollisionEventRegistration, std::map<GameObject *, geom::Vector> >
      allCollisions;
  for (CERiter it = collisionCallbacks.begin(); it != collisionCallbacks.end();
       ++it) {
    allCollisions[*it] = this->level->getCollisions(*it->getObject());
  }
  for (allCollMapIter it2 = allCollisions.begin(); it2 != allCollisions.end();
       ++it2) {
    for (collMapIter it3 = it2->second.begin(); it3 != it2->second.end();
         ++it3) {
      (it2->first)(it3->first, it3->second);
    }
  }
}
}  // namespace internal
}  // namespace turbine
