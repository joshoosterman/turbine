// Copyright 2011

#include "turbine/movement_strategy.h"
#include "turbine/input_manager.h"
#include "turbine/object.h"
#include "SFML/Window/Keyboard.hpp"

namespace turbine {
namespace extras {

KeyboardMovementStrategy::KeyboardMovementStrategy(float speed) {
  this->speed = speed;
}

void KeyboardMovementStrategy::move(geom::Point *position) {
  geom::Vector motion(0, 0);

  if (input::InputManager::getInstance()->keyDown(sf::Keyboard::Left)) {
    motion = motion + geom::Vector(-1, 0);
  }
  if (input::InputManager::getInstance()->keyDown(sf::Keyboard::Right)) {
    motion = motion + geom::Vector(1, 0);
  }
  if (input::InputManager::getInstance()->keyDown(sf::Keyboard::Up)) {
    motion = motion + geom::Vector(0, -1);
  }
  if (input::InputManager::getInstance()->keyDown(sf::Keyboard::Down)) {
    motion = motion + geom::Vector(0, 1);
  }

  if (motion.getMagnitude() > 0) {
    motion = motion.unit() * this->speed;
  }

  *position = *position + motion;
}

FixedPositionMovementStrategy::FixedPositionMovementStrategy(
    geom::Point position) {
  this->position = position;
}

void FixedPositionMovementStrategy::move(geom::Point *position) {
  *position = this->position;
}

ObjectTrackingMovementStrategy::ObjectTrackingMovementStrategy(
    const GameObject &object, geom::Vector offset)
    : object(object), offset(offset) {}

void ObjectTrackingMovementStrategy::move(geom::Point *position) {
  *position = this->object.getLocation() + offset;
}

}  // namespace extras
}  // namespace turbine
