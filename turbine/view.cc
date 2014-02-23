#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include "SFML/System.hpp"

#include "turbine/game.h"
#include "turbine/level.h"
#include "turbine/movement_strategy.h"
#include "turbine/resource_cache.h"
#include "turbine/view.h"

using namespace Turbine::Geom;
using namespace Turbine::Internal;

namespace Turbine {

View *View::activeView = NULL;

View::View(Point screenPosition, Vector size)
{
	this->screenPosition = screenPosition;
	this->strat = new Extras::FixedPositionMovementStrategy(Geom::Point(0, 0));

	this->position = Vector(0, 0);
	this->size = size;
	this->rotation = 0;

	this->view = NULL;
	this->surface = NULL;

	this->needsUpdate = true;
}

View::~View()
{
	delete (sf::View *) view;
	delete (sf::RenderTexture *) surface;
	delete strat;
}

void View::setPosition(Point p)
{
	position = p - Point(0, 0);
}

void View::setWindowPosition(Point p)
{
	this->screenPosition = p;
	needsUpdate = true;
}

void View::setRotation(float r)
{
	rotation = r;
}

void View::setMovementStrategy(Extras::MovementStrategy *strat)
{
	delete this->strat;
	this->strat = strat;
}

void View::setSize(Vector s)
{
   size = s;
   needsUpdate = true;
}


View *View::getCurrentView()
{
	return activeView;
}

Vector View::getSize()
{
	return size;
}

Vector View::getPosition()
{
	return position;
}

Point View::getWindowPosition()
{
	return screenPosition;
}

float View::getRotation()
{
	return rotation;
}

void View::setEnabled(bool enabled)
{
	this->enabled = enabled;
}

void View::update()
{
	if(this->view != NULL) {
		delete (sf::View *) this->view;
	}
	if(this->surface != NULL) {
		delete (sf::RenderTexture *) this->surface;
	}

	sf::View *view = new sf::View();
	sf::RenderTexture *img = new sf::RenderTexture();
	img->create((int) size.x, (int) size.y);

	this->surface = img;
	this->view = view;
}

void View::activate()
{
	if(needsUpdate)  {
		needsUpdate = false;
		update();
	}

	Geom::Point temp(position.x, position.y);
	this->strat->move(temp);
	position = temp - Geom::Point(0, 0);

	view->setCenter(position.x + size.x / 2, position.y + size.y / 2);
	view->setSize(size.x, size.y);
	view->setRotation(rotation);

	sf::RenderTexture *rw = (sf::RenderTexture *) this->surface;
	rw->clear(sf::Color(255, 255, 255));
	rw->setView(*view);
	activeView = this;
}

void View::finish()
{
	sf::RenderTexture *img = (sf::RenderTexture *) this->surface;
	sf::RenderWindow *rw = (sf::RenderWindow *) this->renderTarget;

	img->display();
	sf::Sprite s(img->getTexture());
	s.setPosition(this->screenPosition.x, this->screenPosition.y);
	rw->draw(s);
}

void View::setRenderTarget(sf::RenderWindow *renderTarget)
{
	this->renderTarget = renderTarget;
}

sf::RenderTarget *View::getRenderTarget()
{
	return this->surface;
}

}
