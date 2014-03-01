// Copyright 2011

#ifndef TURBINE_MOVEMENT_STRATEGY_H_
#define TURBINE_MOVEMENT_STRATEGY_H_

#include "turbine/classes.h"
#include "turbine/geom.h"

namespace turbine {
namespace extras {

/// On interface for an object used to move a point on a per frame basis. Using
/// the GOF
/// strategy design pattern.
class MovementStrategy {
 public:
  virtual ~MovementStrategy() {}
  virtual void move(geom::Point* position) = 0;
};

/// Keeps a point at a fixed position.
class FixedPositionMovementStrategy : public MovementStrategy {
 public:
  explicit FixedPositionMovementStrategy(geom::Point position);
  void setPosition(geom::Point position);
  virtual void move(geom::Point* position);

 private:
  geom::Point position;
};

/// Moves a point in 8 directions by the arrow keys.
class KeyboardMovementStrategy : public MovementStrategy {
 public:
  explicit KeyboardMovementStrategy(float speed);
  virtual void move(geom::Point* position);

 private:
  float speed;
};

/// Moves a point to track a GameObject, with an offset
class ObjectTrackingMovementStrategy : public MovementStrategy {
 public:
  ObjectTrackingMovementStrategy(const GameObject& object, geom::Vector offset);
  virtual void move(geom::Point* position);

 private:
  const GameObject& object;
  geom::Vector offset;
};

}       // namespace extras
}       // namespace turbine
#endif  // TURBINE_MOVEMENT_STRATEGY_H_
