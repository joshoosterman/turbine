#ifndef _OBJECT_H
#define _OBJECT_H

#include "Classes.h"
#include "InputManager.h"
#include "Graphics.h"
#include "KeyCodes.h"

namespace Turbine {

// Event callbacks
typedef void (*DrawCallback)(Object *);
typedef void (*StepCallback)(Object *);
typedef void (*CollisionCallback)(GameObject *, GameObject *, Geom::Vector);
typedef void (*MouseCallback)(Object *, Input::MouseEvent);
typedef void (*KeyboardCallback)(Object *, Input::KeyEvent);

class Object {
private:
	//TODO friend Level;
	bool hasInit;

protected:
	Object();

	void registerBeginStepEvent(StepCallback);
	void registerStepEvent(StepCallback);
	void registerEndStepEvent(StepCallback);
	void registerDrawEvent(DrawCallback, int depth);
	void registerGlobalMouseEvent(MouseCallback, Input::EventType);
	void registerKeyboardEvent(KeyboardCallback, Input::EventType);

	void unregisterBeginStepEvent(StepCallback);
	void unregisterStepEvent(StepCallback);
	void unregisterEndStepEvent(StepCallback);
	void unregisterDrawEvent(DrawCallback, int depth);
	void unregisterGlobalMouseEvent(MouseCallback, Input::EventType);
	void unregisterKeyboardEvent(KeyboardCallback, Input::EventType);

	void checkInLevel();
public:
	Level *level;
	virtual ~Object() {};
	virtual void destroy();
	virtual void init() = 0;
};

class GameObject : public Object {
private:
	Graphics::Image mask;

protected:
	virtual void registerCollisionEvent(CollisionCallback);
	void registerMouseEvent(MouseCallback, Input::EventType);
	virtual void unregisterCollisionEvent(CollisionCallback);
	void unregisterMouseEvent(MouseCallback, Input::EventType);

	void createCollisionMask(Graphics::Image image);
	void createCollisionMask(Graphics::Sprite sprite);
	Graphics::Image getCollisionMask();

	Geom::BoundingBox bbox;
	Geom::Point location;

public:
	GameObject();
	virtual ~GameObject() {};

	Geom::BoundingBox getBoundingBox();
	Geom::Point getLocation();

	void drawDebugInfo(bool showmask = false);
	bool collides(GameObject *other);
	bool collides(GameObject *other, Geom::Vector *normal, Geom::Point *collisionPoint);
	bool collides(Geom::Point &p);
	virtual void init() = 0;
};

class SimpleGameObject : public GameObject {
private:
	int depth;
	static void _draw(Object *obj);
	static void _step(Object *obj);

public:
	SimpleGameObject(int depth);

	virtual void setup();
	virtual void draw();
	virtual void step();
	void init();
};

}

#endif
