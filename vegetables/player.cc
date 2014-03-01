#include <typeinfo>
#include <cstring>

#include "vegetables/vegetables.h"

Player::Player() : SimpleGameObject(10) {
  left = turbine::graphics::Sprite("images/player/left.png",
                                   turbine::geom::Point(16, 64), 1);
  right = turbine::graphics::Sprite("images/player/right.png",
                                    turbine::geom::Point(16, 64), 1);
  up = turbine::graphics::Sprite("images/player/up.png",
                                 turbine::geom::Point(16, 64), 1);
  down = turbine::graphics::Sprite("images/player/down.png",
                                   turbine::geom::Point(16, 64), 1);
  current = down;

  inCar = false;
  car = NULL;
  location = turbine::geom::Point(50, 50);
}

void Player::setup() {
  turbine::graphics::Image mask("images/player/playermask.png");
  mask.setOrigin(turbine::geom::Point(16, 8));
  createCollisionMask(mask);
  this->registerCollisionEvent(&Player::_collide);
}

void Player::step() {
  if (inCar) {
    carMovement();
  } else {
    footMovement();
  }

  level->getView(0).setPosition(location - turbine::geom::Vector(400, 300));
}

void Player::footMovement() {
  turbine::geom::Vector motion(0, 0);

  if (turbine::input::InputManager::getInstance()->keyDown(
          sf::Keyboard::Left)) {
    motion = motion + turbine::geom::Vector(-1, 0);
  }
  if (turbine::input::InputManager::getInstance()->keyDown(
          sf::Keyboard::Right)) {
    motion = motion + turbine::geom::Vector(1, 0);
  }
  if (turbine::input::InputManager::getInstance()->keyDown(sf::Keyboard::Up)) {
    motion = motion + turbine::geom::Vector(0, -1);
  }
  if (turbine::input::InputManager::getInstance()->keyDown(
          sf::Keyboard::Down)) {
    motion = motion + turbine::geom::Vector(0, 1);
  }

  if (motion.getMagnitude() > 0) {
    motion = motion.unit() * 4.0f;
    motion.y = motion.y * 0.8f;
  }

  if (motion.x > 0) {
    current = right;
  } else if (motion.x < 0) {
    current = left;
  } else if (motion.y < 0) {
    current = up;
  } else if (motion.y > 0) {
    current = down;
  }

  location = location + motion;
}

void Player::carMovement() {
  /*if(turbine::input::InputManager::getInstance()->keyPressed(sf::Keyboard::E)){
 		inCar = false;
 		car = NULL;
 		location = location - turbine::geom::Vector(100, 0);
 		return;
 	}*/

  car->drive();
  location = car->getLocation();
}

void Player::draw() {
  if (inCar) {
    return;
  }
  current.draw(location);
#ifdef SHOW_MASKS
  drawDebugInfo(true);
#endif
}

void Player::_collide(GameObject *me, GameObject *other,
                      turbine::geom::Vector normal) {
  ((Player *)me)->collide(other, normal);
}

void Player::collide(GameObject *other, turbine::geom::Vector normal) {
  if (inCar) {
    return;
  }

  if (strcmp(typeid(*other).name(), typeid(Car).name()) == 0) {
    if (turbine::input::InputManager::getInstance()->keyDown(sf::Keyboard::E)) {
      car = (Car *)other;
      inCar = true;
      return;
    }
  }

  turbine::geom::Vector escape = normal * 0.3;
  while (collides(other)) {
    location = location + escape;
  }
}
