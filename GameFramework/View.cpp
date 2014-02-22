#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/OpenGl.hpp"

#include "Game.h"
#include "View.h"
#include "ResourceCache.h"
#include "Level.h"
#include "MovementStrategy.h"

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
	delete (sf::RenderImage *) surface;
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
		delete (sf::RenderImage *) this->surface;
	}

	sf::View *view = new sf::View();
	sf::RenderImage *img = new sf::RenderImage();
	img->Create((int) size.x, (int) size.y);

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

	view->SetCenter(position.x + size.x / 2, position.y + size.y / 2);
	view->SetSize(size.x, size.y);
	view->SetRotation(rotation);

	sf::RenderImage *rw = (sf::RenderImage *) this->surface;
	rw->Clear(sf::Color(255, 255, 255));
	rw->SetView(*view);
	activeView = this;
}

void View::finish()
{
	sf::RenderImage *img = (sf::RenderImage *) this->surface;
	sf::RenderWindow *rw = (sf::RenderWindow *) this->renderTarget;

	img->Display();
	sf::Sprite s(img->GetImage());
	s.SetPosition(this->screenPosition.x, this->screenPosition.y);
	rw->Draw(s);
}

void View::setRenderTarget(sf::RenderWindow *renderTarget)
{
	this->renderTarget = renderTarget;
}

sf::RenderImage *View::getRenderTarget()
{
	return this->surface;
}

}