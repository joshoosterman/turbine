#include "Vegetables.h"

Vegetable::Vegetable(Point location) : SimpleGameObject(10)
{
	this->location = location;
}

void Vegetable::setup()
{
	dead = false;
	sprite1 = Sprite("images/gunBanana.png", Point(16, 42), 1);
	sprite2 = Sprite("images/splatterBanana.png", Point(10, 30), 1);
	death = Sound("sounds/wa.wav");

    registerCollisionEvent(&Vegetable::collide);

	bbox = BoundingBox(-16, 16, -42, 0);
}

void Vegetable::step(Object *me) {}

void Vegetable::draw() {
	(dead ? sprite2 : sprite1).draw(location);
#ifdef SHOW_MASKS
	drawDebugInfo(true);
#endif
}

void Vegetable::collide(GameObject *me, GameObject *other, Geom::Vector normal) {
	Vegetable *self = (Vegetable *)me;
	if (!self->dead) {
		self->death.play();
		printf("Collision succeeded between %s and %s\n", typeid(*me).name(), typeid(*other).name());
	}
	self->dead = true;
}

