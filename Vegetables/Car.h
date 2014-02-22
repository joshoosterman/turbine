#ifndef _CAR_H
#define _CAR_H

#include "Turbine.h"

using namespace Turbine;
using namespace Turbine::Geom;
using namespace Turbine::Graphics;
using namespace Turbine::Extras;

class Car : public SimpleGameObject {
public:
	Car();

	void setup();
	void step();
	void drive();
	void draw();

private:
	Vector motion;
	Sprite sprite;
};

#endif