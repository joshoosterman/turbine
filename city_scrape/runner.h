#ifndef _RUNNER_H_
#define _RUNNER_H_

#include "cityscrape.h"
#include "line.h"
#include <Turbine.h>

using namespace Turbine;

class Runner : public SimpleGameObject {
 public:  // Should be protected, but cbf right now
  Runner(CityLevel &level);
  Graphics::Sprite sprRunning;
  double xspeed, yspeed, runspeed;
  double frame;
  double jump_power;
  Line *standingOn;
  CityLevel &level;
  virtual bool shouldJump() = 0;
  void doStep(HorizontalLine *line);
  geom::Size size;

 public:
  bool moveTo(geom::Point new_loc);
  void applyX();
  void applyY();

  virtual void Step();
  virtual void Draw();
};

#endif
