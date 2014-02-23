#ifndef _BUILDING_H
#define _BUILDING_H

#include "Turbine.h"

using namespace Turbine;

class Building : public SimpleGameObject {
public:
	Building(Point pos);

	void setup();
	void draw();

private:
	Sprite sprite;
	Image mask;
};

#endif