#include "MovementStrategy.h"
#include "InputManager.h"
#include "Object.h"
#include "SFML/Window/Keyboard.hpp"


namespace Turbine {
namespace Extras {

KeyboardMovementStrategy::KeyboardMovementStrategy(float speed)
{
	this->speed = speed;
}

void KeyboardMovementStrategy::move(Geom::Point &position)
{
	Geom::Vector motion(0, 0);

	if(Input::InputManager::getInstance()->keyDown(sf::Keyboard::Left)){
		motion = motion + Geom::Vector(-1, 0);
	}
	if(Input::InputManager::getInstance()->keyDown(sf::Keyboard::Right)){
		motion = motion + Geom::Vector(1, 0);
	}
	if(Input::InputManager::getInstance()->keyDown(sf::Keyboard::Up)){
		motion = motion + Geom::Vector(0, -1);
	}
	if(Input::InputManager::getInstance()->keyDown(sf::Keyboard::Down)){
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
