#ifndef _LINE_H_
#define _LINE_H_

#include "cityscrape.h"
#include <Turbine.h>
using namespace Turbine;

class Line {
protected:
    Line();
public:
    virtual void doRunnerStep(Runner& r) = 0;
    virtual bool doCollisionTest(Turbine::Geom::Point start, Turbine::Geom::Point& end, Turbine::Geom::Size box) = 0;
    virtual bool doesPlayerSnap();
};

class HorizontalLine : public Line {
public:
    HorizontalLine(Turbine::Geom::Point start, int width);
    virtual void doRunnerStep(Runner& r);
    virtual bool doCollisionTest(Turbine::Geom::Point start, Turbine::Geom::Point& end, Turbine::Geom::Size box);
    virtual bool doesPlayerSnap();
    bool onLine(Geom::Point pos, Geom::Size size);
protected:
    Turbine::Geom::Point start;
    int width;
};

#endif
