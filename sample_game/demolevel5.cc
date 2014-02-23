#include "sample_game/sample.h"
#include "math.h"

class Box : public GameObject
{
public:
	Image image;

	static void draw(Object *me)
	{ 
		Box *self = (Box*) me;
		self->image.draw(self->location);
	}

	Box()
	{
		location = Point(50, 50);
		image = Image("sample/images/box.png");
		createCollisionMask(image);
	}

	void init() 
	{
		registerDrawEvent(&Box::draw, 30);
	}
};

class Bumper : public GameObject
{
public:
	Sprite sprite;
	Sound ding;
	int lightlife;

	static void draw(Object *me)
	{ 
		Bumper *self = (Bumper*) me;
		self->sprite.draw(self->location);
		if (self->lightlife > 0) {
			self->sprite.setFrame(1);
			self->lightlife--;
		} else {
			self->sprite.setFrame(0);
		}
	}

	static void collide(GameObject *me, GameObject *other, Vector normal) {
		Bumper *self = (Bumper*) me;

		self->lightlife = 100;
		self->ding.play();
	}

	Bumper(Point location)
	{
		lightlife = 0;
		this->location = location;

		ding = Sound("sample/sounds/ding.wav");
		sprite = Sprite("sample/images/bumper.png", Point(20, 20), 2);
		createCollisionMask(sprite);
	}

	void init() {
		registerDrawEvent(&Bumper::draw, 30);
		registerCollisionEvent(&Bumper::collide);
	}
};

DemoLevel5::DemoLevel5() : DemoLevel("Pinball 1", 1, 1)
{
}

void DemoLevel5::init()
{	
	addObject(new Box());
	addObject(new Pinball(Point(200,200),Vector(3,4)));
	addObject(new Pinball(Point(180,140),Vector(3,4)));
	addObject(new Pinball(Point(100,120),Vector(3,4)));
	addObject(new Pinball(Point(110,300),Vector(3,4)));
	addObject(new Bumper(Point(140,150)));
	addObject(new Bumper(Point(110,250)));
	addObject(new Bumper(Point(300,100)));
	addObject(new Bumper(Point(270,285)));
	addObject(new Bumper(Point(236,240)));
}
