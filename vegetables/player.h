#ifndef _PLAYER_H
#define _PLAYER_H

#include "Turbine.h"
#include "Car.h"

using namespace Turbine;
using namespace Turbine::Input;
using namespace Turbine::Geom;
using namespace Turbine::Audio;

class Player : public SimpleGameObject {
public:
	Player();

	void setup();
	void step();
	void draw();
	static void _collide(GameObject *me, GameObject *other, Vector normal);

private:
	void collide(GameObject *other, Vector normal);

	void footMovement();
	void carMovement();

	bool inCar;
	Car *car;

	Vector motion;
	Sprite current;
	Sprite up, down, left, right;
};

#endif