// Copyright 2011

#include <math.h>
#include <algorithm>

#include "turbine/geom.h"

#define PI 3.14159265f
#define PI180 0.01745327f

namespace turbine {
namespace geom {

float max(float a, float b) { return a > b ? a : b; }
float min(float a, float b) { return a < b ? a : b; }

/// The main constructor for BoundingBox.
/**
Takes four parameters - the x co-ordinates for the left and right edges, and the
y co-ordinates for the top and bottom.
*/
BoundingBox::BoundingBox(float left, float right, float top, float bottom) {
  this->left = left;
  this->right = right;
  this->top = top;
  this->bottom = bottom;
}
/// Find the BoundingBox that encompasses all points contained by both this box
/// and and the specified other box (equivalent to the set intersection method).
/**
\param other	The BoundingBox to intersect with.
*/
BoundingBox BoundingBox::intersect(const BoundingBox &other) {
  return BoundingBox(max(left, other.left), min(right, other.right),
                     max(top, other.top), min(bottom, other.bottom));
}
/// Returns the smallest possible BoundingBox that contains both this
/// BoundingBox and the specified other box.
/**
\param other	The BoundingBox to include.
*/
BoundingBox BoundingBox::expandToInclude(const BoundingBox &other) {
  return BoundingBox(min(left, other.left), max(right, other.right),
                     min(top, other.top), max(bottom, other.bottom));
}
/// Returns the smallest possible BoundingBox that contains both this
/// BoundingBox and the specified point.
/**
\param other	The point to include.
*/
BoundingBox BoundingBox::expandToInclude(const Point &p) {
  return BoundingBox(min(left, p.x), max(right, p.x), min(top, p.y),
                     max(bottom, p.y));
}
/// Test whether the BoundingBox contains a point.
bool BoundingBox::contains(const Point &p) {
  return p.x >= left && p.x <= right && p.y >= top && p.y <= bottom;
}
/// Get the area of the BoundingBox.
float BoundingBox::area() { return abs((right - left) * (bottom - top)); }
/// Test whether the BoundingBox is valid.
bool BoundingBox::isValid() { return top < bottom && left < right; }
bool BoundingBox::intersects(const BoundingBox &other) {
  return intersect(other).isValid();
}

BoundingBox BoundingBox::scale(float factor) {
  Point center((left + right) / 2, (top + bottom) / 2);
  return BoundingBox((left - center.x) * factor + center.x,
                     (right - center.x) * factor + center.x,
                     (top - center.y) * factor + center.y,
                     (bottom - center.y) * factor + center.y);
}

/// Move this BoundingBox relative to the location of a Point.
/**
In other words, this translates the BoundingBox by the position vector (rooted
at [0,0]) of the given point.
*/
BoundingBox operator+(const BoundingBox &a, const Point &b) {
  return BoundingBox(a.left + b.x, a.right + b.x, a.top + b.y, a.bottom + b.y);
}

bool operator==(const BoundingBox &a, const BoundingBox &b) {
  return a.left == b.left && a.right == b.right && a.top == b.top &&
         a.bottom == b.bottom;
}

/// The default constructor. Initialises both x and y to 0.
Point::Point() : x(0), y(0) {}

/// The main constructor for Point.
/**
Takes x and y co-ordinates specifying the location of the Point.
*/
Point::Point(float x, float y) : x(x), y(y) {}

/// The copy constructor for Point.
Point::Point(const Point &other) : x(other.x), y(other.y) {}

/// Translates a point by the specified vector.
Point operator+(const Point &a, const Vector &b) {
  return Point(a.x + b.x, a.y + b.y);
}

/// Translates a point by the negative of the specified vector.
Point operator-(const Point &a, const Vector &b) {
  return Point(a.x - b.x, a.y - b.y);
}

/// Returns the difference between two points.
Vector operator-(const Point &a, const Point &b) {
  return Vector(a.x - b.x, a.y - b.y);
}

/// The default constructor. Initialises both x and y to 0.
Vector::Vector() : x(0), y(0) {}

/// The main constructor for Vector. Takes x and y co-ordinates specifying the
/// vector.
Vector::Vector(float x, float y) : x(x), y(y) {}

/// The copy constructor for Vector.
Vector::Vector(const Vector &other) : x(other.x), y(other.y) {}

/// Constructs a Vector given an angle and magnitude.
/**
\param angle		The angle (in degrees) specifying the direction of the vector.
					The angle increases counter-clockwise, so 0 degrees points up,
					90 points right, and so on.
\param magnitude	The size of the vector.
*/
Vector Vector::fromAngleMagnitude(float angle, float magnitude) {
  float x = sin(angle * PI180) * magnitude;
  float y = cos(angle * PI180) * magnitude;
  return Vector(x, y);
}

/// Returns the normalised version of this vector (i.e. a vector of magnitude 1
/// with the same direction).
Vector Vector::unit() {
  Vector result = Vector(*this);
  return result * (1.0f / result.getMagnitude());
}

/// Returns the negative of this vector.
Vector Vector::negative() {
  Vector result = Vector(*this);
  result.x = -result.x;
  result.y = -result.y;
  return result;
}

/// Rotates the direction of this vector clockwise by the given angle.
Vector Vector::rotate(float angle) {
  return Vector::fromAngleMagnitude(getAngle() + angle, getMagnitude());
}

/// Gets the direction in which this vector is pointing.
float Vector::getAngle() {
  float a = atan2(x, y);
  if (a < 0) {
    a += PI * 2;
  }

  return a / PI180;
}

/// Gets the magnitude of this vector.
float Vector::getMagnitude() { return sqrt(x * x + y * y); }

/// Calculate the dot product (inner product) of this vector with another.
float Vector::dotProduct(Vector other) { return x * other.x + y * other.y; }

/// Add two vectors together.
Vector operator+(const Vector &a, const Vector &b) {
  return Vector(a.x + b.x, a.y + b.y);
}

/// Subtract one vector from another.
Vector operator-(const Vector &a, const Vector &b) {
  return Vector(a.x - b.x, a.y - b.y);
}

/// Multiply a vector by a scalar.
Vector operator*(const Vector &a, const float scalar) {
  return Vector(a.x * scalar, a.y * scalar);
}

/// Multiply a vector by a scalar.
Vector operator*(const float scalar, const Vector &a) { return a * scalar; }

/// Divide a vector by a scalar.
Vector operator/(const Vector &a, const float scalar) {
  return Vector(a.x / scalar, a.y / scalar);
}

Vector &Vector::operator=(const Vector &rhs) {
  if (this == &rhs) {
    return *this;
  }

  this->x = rhs.x;
  this->y = rhs.y;

  return *this;
}

}  // namespace geom
}  // namespace turbine
