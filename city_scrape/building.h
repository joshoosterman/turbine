#ifndef _BUILDING_H_
#define _BUILDING_H_

#include <Turbine.h>
#include "level.h"

using namespace Turbine;

class Building : public Turbine::SimpleGameObject {
private:
	Turbine::Graphics::Sprite sprite;

public:
	Building(CityLevel& level, int x);
	void Draw();
};

#endif
