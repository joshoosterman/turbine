#include <assert.h>

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/OpenGl.hpp"

#include "Graphics.h"
#include "ResourceCache.h"
#include "Exceptions.h"
#include "Geom.h"
#include "ImageUtil.h"

using namespace Turbine::Graphics;
using namespace Turbine::Geom;
using namespace Turbine::Internal;

namespace Turbine {
namespace Graphics {


Vector dirs[8] = {Vector(-1,-1),
						Vector(0,-1),
						Vector(1,-1),
						Vector(1,0),
						Vector(1,1),
						Vector(0,1),
						Vector(-1,1),
						Vector(-1,0)};
int dirIndex[3][3] = {	{0, 7, 6},
						{1, 0/*none*/, 5},
						{2, 3, 4}};

int getDirIndex(int x, int y) {
	assert(x != 0 || y != 0);
	x++;
	y++;
	return dirIndex[x][y];
}

bool pixelIsTransparent(sf::Image *surface, int x , int y)
{
	if(x < 0 || x >= surface->GetWidth() || y < 0 || y >= surface->GetHeight()) {
		return true;
	}

	sf::Color col = surface->GetPixel(x, y);
	return col.a == 0;
}

/// Calculates the collision between two SDL_Surfaces.
/**
Returns whether the two surfaces intersect. This method also provides the point of intersection
and the normal of s2 at that point if the required parameters are not NULL.
*/
bool ImageUtil::collision(Image im1, Point p1, Image im2, Point p2, Vector *outNormal, Point *outCollisionPoint, int resolution)
{
	SharedImage *tmp1 = (SharedImage *) im1.img;
	sf::Image *s1 = &(tmp1->image);
	SharedImage *tmp2 = (SharedImage *) im2.img;
	sf::Image *s2 = &(tmp2->image);

	p1 = p1 - (im1.getOrigin() - Point(0,0));
	p2 = p2 - (im2.getOrigin() - Point(0,0));
	BoundingBox bb1 = BoundingBox(p1.x, p1.x + s1->GetWidth(), p1.y, p1.y + s1->GetHeight());
	BoundingBox bb2 = BoundingBox(p2.x, p2.x + s2->GetWidth(), p2.y, p2.y + s2->GetHeight());
	BoundingBox intersect = bb1.intersect(bb2);

	bool collides = false;
	Point collisionPoint;
	for(int y = (int)intersect.top; y <= intersect.bottom && !collides; y += resolution)
	{
		for(int x = (int)intersect.left; x <= intersect.right && !collides; x += resolution)
		{
			if(!pixelIsTransparent(s1, (int)(x - p1.x), (int)(y - p1.y)) &&
				!pixelIsTransparent(s2, (int)(x - p2.x), (int)(y - p2.y)))
			{
				collides = true;
				collisionPoint = Point(x, y);
			}
		}
	}

	if (outCollisionPoint != NULL) {
		outCollisionPoint->x = collisionPoint.x;
		outCollisionPoint->y = collisionPoint.y;
	}

	if (collides && outNormal != NULL) {
		// work out the normal to return - this is currently a bit rough
		// 1. start with the detected collision point
		// 2. move towards mask1 as far as possible, without exiting mask2
		// 3. approximate the slope of the edge

		Point s1cent((p1.x * 2 + s1->GetWidth()) / 2.0f, (p1.y * 2 + s1->GetHeight()) / 2.0f);
		//Point s1cent = p1;
		//Point s2cent((p2.x + s2->w) / 2.0, (p2.y + s2->h) / 2.0);

		int xdir = (int)(s1cent.x - collisionPoint.x);
		if (xdir != 0) {
			xdir = xdir / abs(xdir);
			assert(xdir == -1 || xdir == 1);
		}
		int ydir = (int)(s1cent.y - collisionPoint.y);
		if (ydir != 0) {
			ydir = ydir / abs(ydir);
			assert(ydir == -1 || ydir == 1);
		}

		if (xdir == 0 && ydir == 0) {
			// the masks are right on top of each other,
			// so we have to return an arbitrary vector.
			// Let's say it points right
			outNormal->x = 1;
			outNormal->y = 0;
			return true;
		} else {
			while (!pixelIsTransparent(s2, (int)(collisionPoint.x + xdir - p2.x),
														(int)(collisionPoint.y + ydir - p2.y))) {
				collisionPoint.x += xdir;
				collisionPoint.y += ydir;
			}

			// traverse the edge 5 pixels clockwise
			int steps = 0;
			Point p(collisionPoint.x,collisionPoint.y);
			while (steps < 5) {
				int dir = getDirIndex(xdir, ydir);
				do {
					if (!pixelIsTransparent(s2, (int)(p.x + dirs[dir].x - p2.x), (int)(p.y + dirs[dir].y - p2.y))) {
						p += dirs[dir]; // move in that direction
						break;
					}
					dir = (dir + 1) % 8; // try the next clockwise direction
				} while (dir != getDirIndex(xdir, ydir));
				steps++;
			}
			Vector gradient((p.x - collisionPoint.x), (p.y - collisionPoint.y));
			// traverse the edge 5 pixels counter-clockwise
			steps = 0;
			Point r(collisionPoint.x,collisionPoint.y);
			while (steps < 5) {
				int dir = getDirIndex(xdir, ydir);
				do {
					if (!pixelIsTransparent(s2, (int)(r.x + dirs[dir].x - p2.x), (int)(r.y + dirs[dir].y - p2.y))) {
						r += dirs[dir]; // move in that direction
						break;
					}
					dir = (dir + 7) % 8; // try the next counter-clockwise direction
				} while (dir != getDirIndex(xdir, ydir));
				steps++;
			}
			gradient += Vector((collisionPoint.x - r.x), (collisionPoint.y - r.y));

			Vector normal(gradient.y, -gradient.x);
			normal = normal.unit();

			if ((collisionPoint - s1cent + normal).getMagnitude() > (collisionPoint - s1cent).getMagnitude()) {
				// if following the normal moves us away from mask1,
				// our normal is facing the wrong way and needs reversing
				normal = normal.negative();
			}

			outNormal->x = normal.x;
			outNormal->y = normal.y;
		}
		return true;
	}

	return collides;
}
}
}
