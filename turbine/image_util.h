// Copyright 2011

#ifndef TURBINE_IMAGE_UTIL_H_
#define TURBINE_IMAGE_UTIL_H_

#include "turbine/classes.h"

namespace turbine {
namespace graphics {

/// A class that provides additional functions for image manipulation.
class ImageUtil {
 public:
  static bool collision(graphics::Image im1, geom::Point p1,
                        graphics::Image im2, geom::Point p2,
                        geom::Vector *normal, geom::Point *outCollisionPoint,
                        int resolution = 4);
};

}  // namespace graphics
}  // namespace turbine

#endif  // TURBINE_IMAGE_UTIL_H_
