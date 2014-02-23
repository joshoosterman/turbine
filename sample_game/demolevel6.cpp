#include "Sample.h"
#include "math.h"

class PinballCurve : public GameObject
{
public:
	Sprite sprite;
	bool collided;

	static void draw(Object *me)
	{ 
		PinballCurve *self = (PinballCurve*) me;
		self->sprite.draw(self->location);
	}

	static void collide(GameObject *me, GameObject *other, Vector normal)
	{ 
		PinballCurve *self = (PinballCurve*) me;
		self->sprite.setFrame(1);
		//Vector vector;
		//Image *mask = self->sprite->createImage(1, 0, 1, &vector);
		//self->setCollisionMask(mask, vector);
		if(!self->collided) {
			self->collided = true;
			self->createCollisionMask(self->sprite);
		}
	}

	PinballCurve()
	{
		location = Point(50, 50);
		sprite = Sprite("sample/images/pinballcurve.png", Point(0,0), 2);
		collided = false;
		//Vector vector;
		//Image *mask = sprite->createImage(0, 0, 1, &vector);
		//setCollisionMask(mask, vector);
		createCollisionMask(sprite);
	}

	void init()
	{
		registerDrawEvent(&PinballCurve::draw, 30);
		registerCollisionEvent(&PinballCurve::collide);
	}
};

DemoLevel6::DemoLevel6() : DemoLevel("Pinball 2", 1, 1) {}

void DemoLevel6::init()
{	
	addObject(new PinballCurve());
	addObject(new Pinball(Point(335,335),Vector(0,-5)));
}