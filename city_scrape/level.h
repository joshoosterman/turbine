#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "cityscrape.h"
#include "line.h"
#include "player.h"
#include <vector>

using std::vector;

class CityLevel : public Turbine::Level {
public:
	CityLevel();
	vector<Line*> getLines();
	void addLine(Line*);
protected:
    vector<Line*> lines;
};

#endif
