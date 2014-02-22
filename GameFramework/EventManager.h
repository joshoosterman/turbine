#ifndef _EVENTMANAGER_H
#define _EVENTMANAGER_H

#include <vector>
#include <map>
#include <set>

#include "Classes.h"
#include "Geom.h"
#include "Keycodes.h"
#include "Object.h"

namespace Turbine {
namespace Internal {

class DrawEventRegistration {
public:
	Object *object;
	DrawCallback callback;
	DrawEventRegistration(Object *object, DrawCallback callback) {
		this->object = object;
		this->callback = callback;
	}
	void operator()() const {
		callback(object);
	}
};

bool operator<(const DrawEventRegistration &a, const DrawEventRegistration &b);

class StepEventRegistration {
public:
	Object *object;
	StepCallback callback;
	StepEventRegistration(Object *object, StepCallback callback) {
		this->object = object;
		this->callback = callback;
	}
	void operator()() const {
		callback(object);
	}
};

bool operator<(const StepEventRegistration &a, const StepEventRegistration &b);

class CollisionEventRegistration {
public:
	GameObject *object;
	CollisionCallback callback;
	CollisionEventRegistration(GameObject *object, CollisionCallback callback) {
		this->object = object;
		this->callback = callback;
	}
	GameObject *getObject() const {
		return object;
	}
	void operator()(GameObject *other, Geom::Vector normal) const {
		callback(object, other, normal);
	}
};

bool operator<(const CollisionEventRegistration &a, const CollisionEventRegistration &b);

class MouseEventRegistration {
public:
	Object *object;
	MouseCallback callback;
	MouseEventRegistration(Object *object, MouseCallback callback) {
		this->object = object;
		this->callback = callback;
	}
	GameObject *getObject() const {
		return (GameObject *)object;
	}
	void operator()(sf::Event ev) const;
};

bool operator<(const MouseEventRegistration &a, const MouseEventRegistration &b);

class KeyboardEventRegistration {
public:
	Object *object;
	KeyboardCallback callback;
	KeyboardEventRegistration(Object *object, KeyboardCallback callback) {
		this->object = object;
		this->callback = callback;
	}
	void operator()(sf::Event ev) const;
};

bool operator<(const KeyboardEventRegistration &a, const KeyboardEventRegistration &b);

class EventManager {
public:
	EventManager(Level *level);
	void registerDrawEvent(Object *object, DrawCallback callback, int depth);
	void registerBeginStepEvent(Object *object, StepCallback callback);
	void registerStepEvent(Object *object, StepCallback callback);
	void registerEndStepEvent(Object *object, StepCallback callback);
	void registerCollisionEvent(GameObject *object, CollisionCallback callback);
	void registerMouseEvent(GameObject *object, MouseCallback callback, Input::EventType);
	void registerGlobalMouseEvent(Object *object, MouseCallback callback, Input::EventType);
	void registerKeyboardEvent(Object *object, KeyboardCallback callback, Input::EventType);

	void unregisterDrawEvent(Object *object, DrawCallback callback, int depth);
	void unregisterBeginStepEvent(Object *object, StepCallback callback);
	void unregisterStepEvent(Object *object, StepCallback callback);
	void unregisterEndStepEvent(Object *object, StepCallback callback);
	void unregisterCollisionEvent(GameObject *object, CollisionCallback callback);
	void unregisterMouseEvent(GameObject *object, MouseCallback callback, Input::EventType);
	void unregisterGlobalMouseEvent(Object *object, MouseCallback callback, Input::EventType);
	void unregisterKeyboardEvent(Object *object, KeyboardCallback callback, Input::EventType);

	void performMouseEvents(sf::Event ev);
	void performKeyboardEvents(sf::Event ev);
	void performDraw();
	void performBeginStep();
	void performStep();
	void performEndStep();
	void performCollisions();
private:
	Level *level;
	std::map<int, std::set<DrawEventRegistration> > drawCallbacks;
	std::set<StepEventRegistration> beginStepCallbacks;
	std::set<StepEventRegistration> stepCallbacks;
	std::set<StepEventRegistration> endStepCallbacks;
	std::set<CollisionEventRegistration> collisionCallbacks;
	std::map<Input::EventType, std::set<MouseEventRegistration> > mouseCallbacks;
	std::map<Input::EventType, std::set<MouseEventRegistration> > globalMouseCallbacks;
	std::map<Input::EventType, std::set<KeyboardEventRegistration> > keyboardCallbacks;
};

}
}
#endif
