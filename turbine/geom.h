// Copyright 2011

#ifndef TURBINE_GEOM_H_
#define TURBINE_GEOM_H_

#include <stdio.h>
#include <stdlib.h>

#include "turbine/classes.h"

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif
#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

// TODO(joshoosterman): We shouldn't need these any more, SFML2 has Vector
// classes.

namespace turbine {
namespace geom {

/// Represents a point in 2D space using floating-point arithmetic.
class Point {
 public:
  float x, y;

  Point();
  Point(float x, float y);
  Point(const Point &other);
};

Point operator+(const Point &a, const Vector &b);
Point operator-(const Point &a, const Vector &b);
Vector operator-(const Point &a, const Point &b);

/// Represents a vector in 2D space using floating-point arithmetic.
class Vector {
 public:
  float x, y;

  Vector();
  Vector(float x, float y);
  Vector(const Vector &other);

  float getAngle();
  float getMagnitude();
  float dotProduct(Vector other);
  Vector unit();
  Vector negative();
  Vector rotate(float angle);

  static Vector fromAngleMagnitude(float angle, float magnitude);
  Vector &operator=(const Vector &rhs);
};

Vector operator+(const Vector &a, const Vector &b);
Vector operator-(const Vector &a, const Vector &b);
Vector operator*(const Vector &a, const float scalar);
Vector operator/(const Vector &a, const float scalar);
Vector operator*(const float scalar, const Vector &a);

/// A bounding box, represented by a rectangle in 2D space.
class BoundingBox {
 public:
  float left, right, top, bottom;
  BoundingBox() { left = right = top = bottom = 0; }
  BoundingBox(float left, float right, float top, float bottom);
  BoundingBox intersect(const BoundingBox &other);
  BoundingBox expandToInclude(const BoundingBox &other);
  BoundingBox expandToInclude(const Point &p);
  BoundingBox scale(float factor);
  bool contains(const Point &p);
  float area();
  bool isValid();
  bool intersects(const BoundingBox &other);
};

BoundingBox operator+(const BoundingBox &a, const Point &b);
bool operator==(const BoundingBox &a, const BoundingBox &b);

}  // namespace geom
}  // namespace turbine

#endif  // TURBINE_GEOM_H_
