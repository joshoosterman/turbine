#include "vegetables/vegetables.h"

Car::Car() : SimpleGameObject(10) {}

void Car::setup() {
  sprite = turbine::graphics::Sprite("images\\vehicles\\raceCar.png",
                                     turbine::geom::Point(40, 20), 1);
  bbox = turbine::geom::BoundingBox(-40, 40, -40, 40);
  location = turbine::geom::Point(200, 450);
  motion = turbine::geom::Vector(0, 0);

  createCollisionMask(sprite);
}

void Car::step() { location = location + motion; }

void Car::drive() {
  if (turbine::input::InputManager::getInstance()->keyDown(
          sf::Keyboard::Left)) {
    motion = turbine::geom::Vector::fromAngleMagnitude(motion.getAngle() + 5,
                                                       motion.getMagnitude());
  }
  if (turbine::input::InputManager::getInstance()->keyDown(
          sf::Keyboard::Right)) {
    motion = turbine::geom::Vector::fromAngleMagnitude(motion.getAngle() - 5,
                                                       motion.getMagnitude());
  }
  if (turbine::input::InputManager::getInstance()->keyDown(sf::Keyboard::Up)) {
    motion = turbine::geom::Vector::fromAngleMagnitude(
        motion.getAngle(), motion.getMagnitude() + 1);
  }
  if (turbine::input::InputManager::getInstance()->keyDown(
          sf::Keyboard::Down)) {
    motion = turbine::geom::Vector::fromAngleMagnitude(
        motion.getAngle(), motion.getMagnitude() - 1);
  }
}

void Car::draw() {
  sprite.draw(location, motion.getAngle() - 90,
              turbine::geom::Vector(1.0, 1.0));
#ifdef SHOW_MASKS
  drawDebugInfo(true);
#endif
}
