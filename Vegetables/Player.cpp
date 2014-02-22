#include "Vegetables.h"

Player::Player() : SimpleGameObject(10)
{
	left = Sprite("images/player/left.png", Point(16, 64), 1);
	right = Sprite("images/player/right.png", Point(16, 64), 1);
	up = Sprite("images/player/up.png", Point(16, 64), 1);
	down = Sprite("images/player/down.png", Point(16, 64), 1);
	current = down;

	inCar = false;
	car = NULL;
	location = Point(50, 50);
}

void Player::setup()
{
	Image mask("images/player/playermask.png");
	mask.setOrigin(Point(16, 8));
	createCollisionMask(mask);
	this->registerCollisionEvent(&Player::_collide);
}

void Player::step() {
	if(inCar) {
		carMovement();
	} else {
		footMovement();
	}

	level->getView(0).setPosition(location - Vector(400, 300));
}

void Player::footMovement()
{
	Vector motion(0, 0);

	if(InputManager::getInstance()->keyDown(Turbine::Input::KeyCode::Left)){
		motion = motion + Vector(-1, 0);
	}
	if(InputManager::getInstance()->keyDown(Turbine::Input::KeyCode::Right)){
		motion = motion + Vector(1, 0);
	}
	if(InputManager::getInstance()->keyDown(Turbine::Input::KeyCode::Up)){
		motion = motion + Vector(0, -1);
	}
	if(InputManager::getInstance()->keyDown(Turbine::Input::KeyCode::Down)){
		motion = motion + Vector(0, 1);
	}

	if(motion.getMagnitude() > 0) {
		motion = motion.unit() * 4.0f;
		motion.y = motion.y * 0.8f;
	}

	if(motion.x > 0) {
		current = right;
	} else if(motion.x < 0) {
		current = left;
	} else if(motion.y < 0) {
		current = up;
	} else if(motion.y > 0) {
		current = down;
	}

	location += motion;
}

void Player::carMovement()
{
	/*if(InputManager::getInstance()->keyPressed(Turbine::Input::KeyCode::E)){
		inCar = false;
		car = NULL;
		location = location - Vector(100, 0);
		return;
	}*/

	car->drive();
	location = car->getLocation();
}

void Player::draw() {
	if(inCar) {
		return;
	}
	current.draw(location);
#ifdef SHOW_MASKS
	drawDebugInfo(true);
#endif
}

void Player::_collide(GameObject *me, GameObject *other, Vector normal)
{
	((Player *) me)->collide(other, normal);
}

void Player::collide(GameObject *other, Vector normal) {
	if(inCar) {
		return;
	}

	if(strcmp(typeid(*other).name(), typeid(Car).name()) == 0) {
		if(InputManager::getInstance()->keyDown(Turbine::Input::KeyCode::E)) {
			car = (Car*) other;
			inCar = true;
			return;
		}
	}

	Vector escape = normal * 0.3;
	while (collides(other)) {
		location += escape;
	}
}