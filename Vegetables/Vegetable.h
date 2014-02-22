#ifndef _VEGETABLE_H
#define _VEGETABLE_H

#include "Turbine.h"

class Vegetable : public SimpleGameObject {
public:
	Vegetable(Point location);

	void setup();
    void step(Object *me);
	void draw();

	static void collide(GameObject *me, GameObject *other, Geom::Vector normal);
private:
	Sprite sprite1, sprite2;
	bool dead;
	Sound death;
};

#endif