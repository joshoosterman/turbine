#include "turbine/object.h"
#include "turbine/exceptions.h"
#include "turbine/image_util.h"
#include "turbine/level.h"
#include "turbine/event_manager.h"
#include "turbine/view.h"
#include "turbine/geom.h"

using namespace Turbine;
using namespace Turbine::Input;
using namespace Turbine::Geom;
using namespace Turbine::Internal;
using namespace Turbine::Graphics;

namespace Turbine {

Object::Object() {}

void Object::destroy()
{
	checkInLevel();
	level->removeObject(this);
}

void Object::registerDrawEvent(DrawCallback c, int depth) {
	// register it with this object
	checkInLevel();
	level->getEventManager()->registerDrawEvent(this, c, depth);
}

void Object::registerBeginStepEvent(StepCallback c) {
	// register it with this object
	checkInLevel();
	level->getEventManager()->registerBeginStepEvent(this, c);
}

void Object::registerStepEvent(StepCallback c) {
	// register it with this object
	checkInLevel();
	level->getEventManager()->registerStepEvent(this, c);
}

void Object::registerEndStepEvent(StepCallback c) {
	// register it with this object
	checkInLevel();
	level->getEventManager()->registerEndStepEvent(this, c);
}

void Object::registerGlobalMouseEvent(MouseCallback c, EventType e) {
	// register it with this object
	checkInLevel();
	level->getEventManager()->registerGlobalMouseEvent(this, c, e);
}

void Object::registerKeyboardEvent(KeyboardCallback c, EventType e) {
	// register it with this object
	checkInLevel();
	level->getEventManager()->registerKeyboardEvent(this, c, e);
}

void GameObject::registerMouseEvent(MouseCallback c, EventType e) {
	// register it with this object
	checkInLevel();
	level->getEventManager()->registerMouseEvent(this, c, e);
}

void Object::unregisterDrawEvent(DrawCallback c, int depth) {
	// register it with this object
	checkInLevel();
	level->getEventManager()->unregisterDrawEvent(this, c, depth);
}

void Object::unregisterBeginStepEvent(StepCallback c) {
	// register it with this object
	checkInLevel();
	level->getEventManager()->unregisterBeginStepEvent(this, c);
}

void Object::unregisterStepEvent(StepCallback c) {
	// register it with this object
	checkInLevel();
	level->getEventManager()->unregisterStepEvent(this, c);
}

void Object::unregisterEndStepEvent(StepCallback c) {
	// register it with this object
	checkInLevel();
	level->getEventManager()->unregisterEndStepEvent(this, c);
}

void Object::unregisterGlobalMouseEvent(MouseCallback c, EventType e) {
	// register it with this object
	checkInLevel();
	level->getEventManager()->unregisterGlobalMouseEvent(this, c, e);
}

void Object::unregisterKeyboardEvent(KeyboardCallback c, EventType e) {
	// register it with this object
	checkInLevel();
	level->getEventManager()->unregisterKeyboardEvent(this, c, e);
}

void Object::checkInLevel() {
	if(level == NULL) {
		throw ObjectNotInLevelException("You must add the object to a level to call this operation.");
	}
}

void GameObject::unregisterMouseEvent(MouseCallback c, EventType e) {
	// register it with this object
	checkInLevel();
	level->getEventManager()->unregisterMouseEvent(this, c, e);
}

GameObject::GameObject() {}

//void GameObject::init() {}

void GameObject::registerCollisionEvent(CollisionCallback c) {
	// register it with this object
	checkInLevel();
	level->getEventManager()->registerCollisionEvent(this, c);
}

void GameObject::unregisterCollisionEvent(CollisionCallback c) {
	// register it with this object
	checkInLevel();
	level->getEventManager()->unregisterCollisionEvent(this, c);
}

void GameObject::createCollisionMask(Graphics::Image image)
{
	Point origin = image.getOrigin();
	BoundingBox bbox = image.getBBox();
	int x = MAX(origin.x, bbox.right - origin.x);
	int y = MAX(origin.y, bbox.bottom - origin.y);
	int size = MAX(x, y) * 3;

	Image mask(size, size);
	mask.setOrigin(Point(size / 2, size / 2));
	image.drawOnto(mask, Point(size / 2, size / 2));

	this->mask = mask;
	//this->mask.setOrigin(Point(size / 2, size / 2));
	//this->bbox = mask.getBBox();
	this->bbox = BoundingBox(0,0,0,0);
	this->bbox = this->bbox.expandToInclude(Point(0,0) + Vector(bbox.left, bbox.top).rotate(image.getRotation()));
	this->bbox = this->bbox.expandToInclude(Point(0,0) + Vector(bbox.right, bbox.top).rotate(image.getRotation()));
	this->bbox = this->bbox.expandToInclude(Point(0,0) + Vector(bbox.right, bbox.bottom).rotate(image.getRotation()));
	this->bbox = this->bbox.expandToInclude(Point(0,0) + Vector(bbox.left, bbox.bottom).rotate(image.getRotation()));
	
}

void GameObject::createCollisionMask(Graphics::Sprite sprite)
{
	Point origin = sprite.getOrigin();
	BoundingBox bbox = sprite.getBBox();
	int x = MAX(origin.x, bbox.right - origin.x);
	int y = MAX(origin.y, bbox.bottom - origin.y);
	int size = MAX(x, y) * 3;

	Image mask(size, size);
	mask.setOrigin(Point(size / 2, size / 2));
	sprite.drawOnto(mask, Point(0,0) + (Point(size / 2, size / 2) - sprite.getOrigin()));

	this->mask = mask;
	this->bbox = mask.getBBox();
	/*this->bbox = BoundingBox(0,0,0,0);
	this->bbox = this->bbox.ExpandToInclude(Point(0,0) + Vector(bbox.left, bbox.top).Rotate(sprite.getRotation()));
	this->bbox = this->bbox.ExpandToInclude(Point(0,0) + Vector(bbox.right, bbox.top).Rotate(sprite.getRotation()));
	this->bbox = this->bbox.ExpandToInclude(Point(0,0) + Vector(bbox.right, bbox.bottom).Rotate(sprite.getRotation()));
	this->bbox = this->bbox.ExpandToInclude(Point(0,0) + Vector(bbox.left, bbox.bottom).Rotate(sprite.getRotation()));
	*/
}


Graphics::Image GameObject::getCollisionMask()
{
	return mask;
}

BoundingBox GameObject::getBoundingBox() {
	return this->bbox + this->location;
}

Point GameObject::getLocation() {
	return this->location;
}

bool GameObject::collides(GameObject *other) {
	return collides(other, NULL, NULL);
}

bool GameObject::collides(GameObject *other, Vector *normal, Point *collisionPoint) {
	BoundingBox intersect = this->getBoundingBox().intersect(other->getBoundingBox());
	bool bboxintersects = intersect.top < intersect.bottom && intersect.left < intersect.right;
	bool pixelWise = this->mask.isValid() && other->mask.isValid();
	if (bboxintersects && pixelWise) {
		return ImageUtil::collision(this->mask, this->location, other->mask, other->location, normal, NULL);
	} else if (bboxintersects) {
		if (normal != NULL) {
			// just go through each of the edges of the intersect BB.
			// when we find one that doesn't match our bounding box, return
			// the normal for that edge.
			if (intersect.left != this->getBoundingBox().left) {
				normal->x = -1;
				normal->y = 0;
			} else if (intersect.right != this->getBoundingBox().right) {
				normal->x = 1;
				normal->y = 0;
			} else if (intersect.top != this->getBoundingBox().top) {
				normal->x = 0;
				normal->y = -1;
			} else {
				normal->x = 0;
				normal->y = 1;
			}
		}
		return true;
	} else {
		return false;
	}
}

bool GameObject::collides(Point &p) {
	return this->getBoundingBox().contains(p);
}

void GameObject::drawDebugInfo(bool showmask)
{
	if(showmask) {
		mask.draw(this->getLocation());
	}
	int cSize = 10;
	Turbine::Graphics::drawLine(getLocation() - Vector(0, cSize), getLocation() + Vector(0, cSize) , Color(255, 255, 255));
	Turbine::Graphics::drawLine(getLocation() - Vector(cSize, 0), getLocation() + Vector(cSize, 0) , Color(255, 255, 255));
	Turbine::Graphics::drawRectangle(this->getBoundingBox(), Color(255, 0, 0, 64), false);
}

SimpleGameObject::SimpleGameObject(int depth) {
	this->depth = depth;
}

void SimpleGameObject::init() {
	this->registerStepEvent(&_step);
	this->registerDrawEvent(&_draw, depth);
	this->setup();
}

void SimpleGameObject::_draw(Object *obj){
	((SimpleGameObject *) obj)->draw();
}

void SimpleGameObject::_step(Object *obj){
	((SimpleGameObject *) obj)->step();
}

void SimpleGameObject::setup(){}

void SimpleGameObject::draw(){}

void SimpleGameObject::step(){}
}

