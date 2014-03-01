#ifndef _CITY_H
#define _CITY_H

#include "turbine/turbine.h"

class City : public turbine::Level {
 public:
  City(turbine::geom::Size size);
  virtual ~City();
  void init();

 private:
  friend class LevelLoader;
};

#endif
