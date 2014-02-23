#ifndef _MOVESRAT_H
#define _MOVESTRAT_H

#include "Classes.h"
#include "Geom.h"

namespace Turbine {
namespace Extras {

/// On interface for an object used to move a point on a per frame basis. Using the GOF
/// strategy design pattern.
class MovementStrategy
{
public:
	virtual ~MovementStrategy() {};
	virtual void move(Geom::Point &position) = 0;
};

/// Keeps a point at a fixed position.
class FixedPositionMovementStrategy : public MovementStrategy
{
public:
	FixedPositionMovementStrategy(Geom::Point position);
	void setPosition(Geom::Point position);
	virtual void move(Geom::Point &position);

private:
	Geom::Point position;
};

/// Moves a point in 8 directions by the arrow keys.
class KeyboardMovementStrategy : public MovementStrategy
{
public:
	KeyboardMovementStrategy(float speed);
	virtual void move(Geom::Point &position);

private:
	float speed;
};

/// Moves a point to track a GameObject, with an offset
class ObjectTrackingMovementStrategy : public MovementStrategy
{
public:
	ObjectTrackingMovementStrategy(GameObject &object, Geom::Vector offset);
	virtual void move(Geom::Point &position);
	
private:
	GameObject &object;
	Geom::Vector offset;
};

}
}
#endif
