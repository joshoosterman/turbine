#include "sample_game/sample.h"
#include "math.h"

#define PI 3.14159265
#define PI180 0.01745327

class Smiley1 : public GameObject
{
public:
	Sprite sprite;
	int mode;
	double a, rotation;

	Smiley1(int mode, int rotation)
	{
		sprite = Sprite("sample/images/smiley.bmp", Geom::Point(40, 40), 1);

		this->mode = mode;
		this->a = 0;
		this->rotation = rotation;

		if(rotation % 180 == 0) {
			sprite.setColor(Color(255,128,128,128));
		}
	}

	void init()
	{
		registerDrawEvent(&Smiley1::draw, 50);
	}

	~Smiley1()
	{
	}

	static void draw(Object *me)
	{
		Smiley1 *self = (Smiley1*) me;
		self->a += 0.05;
		self->rotation += 0.5;
		self->location = Point(200, 200) + Vector::fromAngleMagnitude(self->rotation, 130);
		Vector v2 = Vector::fromAngleMagnitude(self->rotation, 20);
		double v;
		switch(self->mode)
		{
			case 1:
				if(self->a > 3.14) {
					self->a -= 3.14;
				}
				v = sin(self->a) * 0.6 + 0.4;
				self->sprite.draw(self->location, 0, Vector(v, v));
				break;
			case 2:
				v = self->a * 20;
				self->sprite.draw(self->location, v, Vector(1.0, 1.0));
				break;
		}
	}
};


DemoLevel1::DemoLevel1() : DemoLevel("Sprite Demo", 1, 2) {}

void DemoLevel1::init()
{

	for(int i = 0; i < 8; i++) {
		addObject(new Smiley1(i % 2 + 1, i * 45));
	}
}
