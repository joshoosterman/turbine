#ifndef _LINE_H_
#define _LINE_H_

#include "cityscrape.h"
#include <Turbine.h>
using namespace Turbine;

class Line {
 protected:
  Line();

 public:
  virtual void doRunnerStep(Runner &r) = 0;
  virtual bool doCollisionTest(Turbine::geom::Point start,
                               Turbine::geom::Point &end,
                               Turbine::geom::Size box) = 0;
  virtual bool doesPlayerSnap();
};

class HorizontalLine : public Line {
 public:
  HorizontalLine(Turbine::geom::Point start, int width);
  virtual void doRunnerStep(Runner &r);
  virtual bool doCollisionTest(Turbine::geom::Point start,
                               Turbine::geom::Point &end,
                               Turbine::geom::Size box);
  virtual bool doesPlayerSnap();
  bool onLine(geom::Point pos, geom::Size size);

 protected:
  Turbine::geom::Point start;
  int width;
};

#endif
