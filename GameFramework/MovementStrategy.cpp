#include "MovementStrategy.h"
#include "InputManager.h"
#include "Object.h"

namespace Turbine {
namespace Extras {

KeyboardMovementStrategy::KeyboardMovementStrategy(float speed)
{
	this->speed = speed;
}

void KeyboardMovementStrategy::move(Geom::Point &position)
{
	Geom::Vector motion(0, 0);

	if(Input::InputManager::getInstance()->keyDown(Input::Left)){
		motion = motion + Geom::Vector(-1, 0);
	}
	if(Input::InputManager::getInstance()->keyDown(Input::Right)){
		motion = motion + Geom::Vector(1, 0);
	}
	if(Input::InputManager::getInstance()->keyDown(Input::Up)){
		motion = motion + Geom::Vector(0, -1);
	}
	if(Input::InputManager::getInstance()->keyDown(Input::Down)){
		motion = motion + Geom::Vector(0, 1);
	}

	if(motion.getMagnitude() > 0) {
		motion = motion.unit() * this->speed;
	}

	position = position + motion;
}

FixedPositionMovementStrategy::FixedPositionMovementStrategy(Geom::Point position)
{
	this->position = position;
}

void FixedPositionMovementStrategy::move(Geom::Point &position)
{
	position = this->position;
}

ObjectTrackingMovementStrategy::ObjectTrackingMovementStrategy(GameObject &object, Geom::Vector offset)
: object(object), offset(offset) {}

void ObjectTrackingMovementStrategy::move(Geom::Point &position)
{
	position = this->object.getLocation() + offset;
}

}
}
