#include "Sample.h"
#include "math.h"

class Vegetable2 : public GameObject
{
public:
	//AnimatedSprite *sprite;
	Sprite sprite;
	Vector movement;

	static void step(Object *me)
	{
		Vegetable2 *self = (Vegetable2*) me;
		if(self->location.x < 10 || self->location.x > 400) {
			self->movement.x = -self->movement.x;
		}
		self->location = self->location + self->movement;
	}

	static void draw(Object *me)
	{ 
		Vegetable2 *self = (Vegetable2*) me;
		static int a = 0;
		a++;
		self->sprite.setFrame(a);
		//view->drawSprite(self->sprite, self->location);
		self->sprite.draw(self->location);
	}

	Vegetable2(Point p, Vector v)
	{
		location = p;
		movement = v;
		sprite = Sprite("sample/images/carrot.bmp", Point(13, 25), 7);
		
	}

	void init()
	{
		registerStepEvent(&Vegetable2::step);
		registerDrawEvent(&Vegetable2::draw, 10);
	}
};

class Grass : public GameObject
{
public:
	Image image, image2;

	static void draw(Object *me)
	{ 
		Grass *self = (Grass*) me;

		//Crude terrain
		for(int x = -1; x < 3; x++)
		{
			for(int y = 0; y < 6; y++)
			{
				self->image.draw(Point(x * 256, y * 256));
			}
		}

		self->image2.draw(Point(100, 80));
	}

	Grass()
	{
		image = Image("sample/images/grassrock.png");
		image2 = Image("sample/images/racecar.png");
	}

	void init()
	{
		registerDrawEvent(&Grass::draw, 100);
	}
};

DemoLevel3::DemoLevel3() : DemoLevel("Multiple Views", 1, 1) {
}

void DemoLevel3::init()
{	
	addObject(new Grass());
	GameObject *vege1 = new Vegetable2(Point(200, 150), Vector(1, 0));
	GameObject *vege2 = new Vegetable2(Point(200, 150), Vector(-1, 0));

	addObject(vege1);
	addObject(vege2);

	View *v2 = new View(Point(0, 200), Vector(200, 200));
	v2->setEnabled(true);
	v2->setMovementStrategy(new Extras::KeyboardMovementStrategy(3));
	v2->setRotation(45);
	View *v3 = new View(Point(200, 200), Vector(200, 200));
	v3->setEnabled(true);
	v3->setMovementStrategy(new Extras::ObjectTrackingMovementStrategy(*vege2, Geom::Vector(-100, -100)));

	addView(v2);
	addView(v3);
}