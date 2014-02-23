#include "sample_game/sample.h"
#include "math.h"

class Maze : public GameObject
{
public:
	Sprite sprite;
	Image image;
	double rotation;

	static void draw(Object *me)
	{ 
		Maze *self = (Maze*) me;

		//self->rotation += 0.5;
		self->sprite.draw(self->location, self->rotation, Vector(1.0, 1.0));
		//self->createCollisionMask(self->sprite);
	}

	Maze()
	{
		location = Point(200, 200);
		sprite = Sprite("sample/images/maze.png", Point(150, 150), 1);
		rotation = 0;
	}

	void init()
	{
		registerDrawEvent(&Maze::draw, 50);
		createCollisionMask(sprite);
	}

	~Maze()
	{
	}
};

class Face : public GameObject
{
public:
	Sprite sprite;
	bool collide;

	static void draw(Object *me)
	{ 
		Face *self = (Face*) me;
		self->sprite.setFrame(self->collide ? 1 : 0);
		self->sprite.draw(self->location);
		self->collide = false;
	}

	static void step(Object *me)
	{ 
		Face *self = (Face*) me;
		self->location = Input::InputManager::getInstance()->mouseGetWindowPosition();
	}

	static void onCollide(GameObject *me, GameObject *other, Vector normal) {
		Face *self = (Face*) me;
		self->collide = true;
	}

	Face() {
		sprite = Sprite("sample/images/face.png", Point(7, 7), 2);
		createCollisionMask(sprite);
	}

	void init()
	{
		registerDrawEvent(&Face::draw, 40);
		registerStepEvent(&Face::step);
		registerCollisionEvent(&Face::onCollide);
	}

	~Face(){}
};


DemoLevel4::DemoLevel4() : DemoLevel("Collisions + Mouse", 1, 1){
}

void DemoLevel4::init()
{	
	addObject(new Maze());
	addObject(new Face());
}
