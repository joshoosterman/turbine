#ifndef _CITY_H
#define _CITY_H

#include "Turbine.h"
class City : public Level {
public:
	City(Turbine::Geom::Size size);
	virtual ~City();
    void init();

private:
	friend class LevelLoader;
};

#endif