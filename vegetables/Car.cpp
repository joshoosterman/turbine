#include "Vegetables.h"

Car::Car() : SimpleGameObject(10) {}

void Car::setup()
{
	sprite = Sprite("images\\vehicles\\raceCar.png", Point(40, 20), 1);
	bbox = BoundingBox(-40, 40, -40, 40);
	location = Point(200, 450);
	motion = Vector(0, 0);

	createCollisionMask(sprite);
}

void Car::step() {
	location = location + motion;
}

void Car::drive() {
	if(InputManager::getInstance()->keyDown(KeyCode::Left)){
		motion = Vector::fromAngleMagnitude(motion.getAngle() + 5, motion.getMagnitude());
	}
	if(InputManager::getInstance()->keyDown(KeyCode::Right)){
		motion = Vector::fromAngleMagnitude(motion.getAngle() - 5, motion.getMagnitude());
	}
	if(InputManager::getInstance()->keyDown(KeyCode::Up)){
		motion = Vector::fromAngleMagnitude(motion.getAngle(), motion.getMagnitude() + 1);
	}
	if(InputManager::getInstance()->keyDown(KeyCode::Down)){
		motion = Vector::fromAngleMagnitude(motion.getAngle(), motion.getMagnitude() - 1);
	}
}

void Car::draw() {
	sprite.draw(location, motion.getAngle() - 90, Vector(1.0, 1.0));
#ifdef SHOW_MASKS
	drawDebugInfo(true);
#endif
}