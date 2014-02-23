#ifndef _IMAGEUTIL_H
#define _IMAGEUTIL_H

#include "classes.h"

namespace Turbine {
namespace Graphics {

/// A class that provides additional functions for image manipulation.
class ImageUtil
{
public:
	static bool collision(Graphics::Image im1, Geom::Point p1, Graphics::Image im2, Geom::Point p2, Geom::Vector *normal, Geom::Point *outCollisionPoint, int resolution = 4);
};

}
}

#endif
