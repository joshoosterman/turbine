#include "KeyCodes.h"
#include "SFML/Window/Keyboard.hpp"

#include "Sample.h"

#include "EventManager.h"

DemoLevel::DemoLevel(std::string text, int id, int background) : Level()
{
	this->text = text;
	this->id = id;
	this->hasInit = false;

	next = NULL;
	previous = NULL;

	switch(background)
	{
		case 1:
			addObject(new Background("sample/images/background.png"));
			break;
		case 2:
			addObject(new Background("sample/images/graffiti.png"));
			break;
	}

	addObject(new LevelLabel(this));
}

void DemoLevel::doInit() {
	if(!hasInit) {
		init();
	}
	hasInit = true;
}

Background::Background(std::string imageFile)
{
	sprite = Sprite(imageFile, Geom::Point(0, 0), 1);
}

void Background::init()
{
	registerDrawEvent(&Background::draw, 100);
	registerStepEvent(&Background::step);
	registerMouseEvent(&Background::click, Input::MouseButtonReleased);
}

void Background::click(Object *me, Input::MouseEvent ev)
{
	int a = 0;
	a++;
}

Background::~Background() {}

void Background::step(Object *me)
{
	int a = 0;
	a++;
}

void Background::draw(Object *me)
{
	Background *self = (Background*) me;
	self->sprite.draw(Point(0,0));
}

LevelLabel::LevelLabel(DemoLevel *dl)
{
	this->dlevel = dl;
	font = Font("sample/ariblk.ttf", 12);
	font.setColor(Color(0, 0, 0, 255));
	keys = Sprite("sample/images/keys.png", Geom::Point(0, 0), 1);
}

void LevelLabel::init() 
{
	registerKeyboardEvent(&LevelLabel::keydown, Input::KeyPressed);
	registerDrawEvent(&LevelLabel::draw, 0);
}

LevelLabel::~LevelLabel()
{
}

void LevelLabel::draw(Object *me)
{
	LevelLabel *self = (LevelLabel*) me;

	drawRectangle(BoundingBox(10, 220, 10, 50), Color(0xBB, 0xBB, 0xBB), false);
	drawRectangle(BoundingBox(10, 220, 10, 50), Color(0, 0, 0), true);
	self->keys.draw(Point(230, 12));

	std::string str = self->dlevel->text; 
	self->font.draw(str, Point(15, 15));
}

void LevelLabel::keydown(Object *me, Input::KeyEvent ev)
{
	LevelLabel *self = (LevelLabel*) me;

	switch(ev.key) {
		case sf::Keyboard::Left:
			if(self->dlevel->previous != NULL) {
				self->dlevel->previous->doInit();
				Game::getInstance().setActiveLevel(*self->dlevel->previous);
			}
			break;
		case sf::Keyboard::Right:
			if(self->dlevel->next != NULL) {
				self->dlevel->next->doInit();
				Game::getInstance().setActiveLevel(*self->dlevel->next);
			}
			break;
		default:
			break;
	}
}
