#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include "EventManager.h"
#include "Geom.h"
#include "Game.h"
#include "Level.h"
#include "Object.h"
#include "InputManager.h"

using namespace Turbine::Geom;
using namespace Turbine::Input;

namespace Turbine {
namespace Internal {

void MouseEventRegistration::operator()(sf::Event e) const {
	MouseEvent ev;
	callback(object, ev);
}

void KeyboardEventRegistration::operator()(sf::Event e) const {
	KeyEvent ev;
	ev.key = (Input::KeyCode)((int) e.Key.Code);
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

bool operator<(const CollisionEventRegistration &a, const CollisionEventRegistration &b) {
	if (a.object == b.object) {
		return a.callback < b.callback;
	}
	return a.object < b.object;
}

bool operator<(const MouseEventRegistration &a, const MouseEventRegistration &b) {
	if (a.object == b.object) {
		return a.callback < b.callback;
	}
	return a.object < b.object;
}

bool operator<(const KeyboardEventRegistration &a, const KeyboardEventRegistration &b) {
	if (a.object == b.object) {
		return a.callback < b.callback;
	}
	return a.object < b.object;
}

EventManager::EventManager(Level *level) {
	this->level = level;
}

void EventManager::registerDrawEvent(Object *o, DrawCallback callback, int depth) {
	DrawEventRegistration reg(o, callback);
	drawCallbacks[-depth].insert(reg);
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

void EventManager::registerCollisionEvent(GameObject *o, CollisionCallback callback) {
	CollisionEventRegistration reg(o, callback);
	collisionCallbacks.insert(reg);
}

void EventManager::registerMouseEvent(GameObject *o, MouseCallback callback, EventType e) {
	MouseEventRegistration reg(o, callback);
	mouseCallbacks[e].insert(reg);
}

void EventManager::registerGlobalMouseEvent(Object *o, MouseCallback callback, EventType e) {
	MouseEventRegistration reg(o, callback);
	globalMouseCallbacks[e].insert(reg);
}

void EventManager::registerKeyboardEvent(Object *o, KeyboardCallback callback, EventType e) {
	KeyboardEventRegistration reg(o, callback);
	keyboardCallbacks[e].insert(reg);
}

void EventManager::unregisterDrawEvent(Object *o, DrawCallback callback, int depth) {
	DrawEventRegistration reg(o, callback);
	drawCallbacks[-depth].erase(reg);
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

void EventManager::unregisterCollisionEvent(GameObject *o, CollisionCallback callback) {
	CollisionEventRegistration reg(o, callback);
	collisionCallbacks.erase(reg);
}

void EventManager::unregisterMouseEvent(GameObject *o, MouseCallback callback, EventType e) {
	MouseEventRegistration reg(o, callback);
	mouseCallbacks[e].erase(reg);
}

void EventManager::unregisterGlobalMouseEvent(Object *o, MouseCallback callback, EventType e) {
	MouseEventRegistration reg(o, callback);
	globalMouseCallbacks[e].erase(reg);
}

void EventManager::unregisterKeyboardEvent(Object *o, KeyboardCallback callback, EventType e) {
	KeyboardEventRegistration reg(o, callback);
	keyboardCallbacks[e].erase(reg);
}



typedef std::map<int,std::set<DrawEventRegistration> >::iterator DERmapiter;
typedef std::set<DrawEventRegistration>::iterator DERiter;

void EventManager::performDraw() {
	// This works because maps are sorted by key. Objects will be drawn in ascending order of depth.
    for (DERmapiter it = drawCallbacks.begin(); it != drawCallbacks.end(); ++it) {
		for (DERiter it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            (*it2)();
        }
    }
}

typedef std::set<StepEventRegistration>::iterator SERiter;

void EventManager::performBeginStep() {
	for (SERiter it = beginStepCallbacks.begin(); it != beginStepCallbacks.end(); ++it) {
		(*it)();
	}
}
void EventManager::performStep() {
	for (SERiter it = stepCallbacks.begin(); it != stepCallbacks.end(); ++it) {
		(*it)();
	}
}
void EventManager::performEndStep() {
	for (SERiter it = endStepCallbacks.begin(); it != endStepCallbacks.end(); ++it) {
		(*it)();
	}
}

typedef std::map<Input::EventType, std::set<MouseEventRegistration> >::iterator MERmapiter;
typedef std::set<MouseEventRegistration>::iterator MERiter;

void EventManager::performMouseEvents(sf::Event ev) {
	for (MERmapiter it = globalMouseCallbacks.begin(); it != globalMouseCallbacks.end(); ++it) {
		if (ev.Type == it->first) {
			for (MERiter it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
				(*it2)(ev);
			}
		}
	}

	Point p1 = InputManager::getInstance()->mouseGetWindowPosition();
	// this could be done with a spatial index in future
	for (MERmapiter it = mouseCallbacks.begin(); it != mouseCallbacks.end(); ++it) {
		if (ev.Type == it->first) {
			for (MERiter it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
					// NOTE: This fixes a bug where
					// the referenced object went out of scope before the function ran,
					//   ==> Undefined behaviour
				Point p = level->toWorldPosition(p1);
				if (it2->getObject()->collides(p)) {
					(*it2)(ev);
				}
			}
		}
	}
}

typedef std::map<Input::EventType, std::set<KeyboardEventRegistration> >::iterator KERmapiter;
typedef std::set<KeyboardEventRegistration>::iterator KERiter;

void EventManager::performKeyboardEvents(sf::Event ev) {
	for (KERmapiter it = keyboardCallbacks.begin(); it != keyboardCallbacks.end(); ++it) {
		if (ev.Type == it->first) {
			for (KERiter it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
				(*it2)(ev);
			}
		}
	}
}

typedef std::set<CollisionEventRegistration>::iterator CERiter;
typedef std::map<CollisionEventRegistration *, std::map<GameObject *, Vector> >::iterator allCollMapIter;
typedef std::map<GameObject *, Vector>::iterator collMapIter;

void EventManager::performCollisions() {
	std::map<CollisionEventRegistration *, std::map<GameObject *, Vector> > allCollisions;
	for (CERiter it = collisionCallbacks.begin(); it != collisionCallbacks.end(); ++it) {
		allCollisions[(CollisionEventRegistration*)&*it] = this->level->getCollisions(*it->getObject());
	}
	for (allCollMapIter it2 = allCollisions.begin(); it2 != allCollisions.end(); ++it2) {
		for (collMapIter it3 = it2->second.begin(); it3 != it2->second.end(); ++it3) {
			(*(it2->first))(it3->first, it3->second);
		}
	}
}
}
}
