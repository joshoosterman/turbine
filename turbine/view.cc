// Copyright 2011

#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include "SFML/System.hpp"

#include "turbine/game.h"
#include "turbine/level.h"
#include "turbine/movement_strategy.h"
#include "turbine/resource_cache.h"
#include "turbine/view.h"

namespace turbine {

View *View::activeView = NULL;

View::View(geom::Point screenPosition, geom::Vector size) {
  this->screenPosition = screenPosition;
  this->strat = new extras::FixedPositionMovementStrategy(geom::Point(0, 0));

  this->position = geom::Vector(0, 0);
  this->size = size;
  this->rotation = 0;

  this->view = NULL;
  this->surface = NULL;

  this->needsUpdate = true;
}

View::~View() {
  delete (sf::View *)view;
  delete (sf::RenderTexture *)surface;
  delete strat;
}

void View::setPosition(geom::Point p) { position = p - geom::Point(0, 0); }

void View::setWindowPosition(geom::Point p) {
  this->screenPosition = p;
  needsUpdate = true;
}

void View::setRotation(float r) { rotation = r; }

void View::setMovementStrategy(extras::MovementStrategy *strat) {
  delete this->strat;
  this->strat = strat;
}

void View::setSize(geom::Vector s) {
  size = s;
  needsUpdate = true;
}

View *View::getCurrentView() { return activeView; }

geom::Vector View::getSize() { return size; }

geom::Vector View::getPosition() { return position; }

geom::Point View::getWindowPosition() { return screenPosition; }

float View::getRotation() { return rotation; }

void View::setEnabled(bool enabled) { this->enabled = enabled; }

void View::update() {
  if (this->view != NULL) {
    delete (sf::View *)this->view;
  }
  if (this->surface != NULL) {
    delete (sf::RenderTexture *)this->surface;
  }

  sf::View *view = new sf::View();
  sf::RenderTexture *img = new sf::RenderTexture();
  img->create(static_cast<int>(size.x), static_cast<int>(size.y));

  this->surface = img;
  this->view = view;
}

void View::activate() {
  if (needsUpdate) {
    needsUpdate = false;
    update();
  }

  geom::Point temp(position.x, position.y);
  this->strat->move(&temp);
  position = temp - geom::Point(0, 0);

  view->setCenter(position.x + size.x / 2, position.y + size.y / 2);
  view->setSize(size.x, size.y);
  view->setRotation(rotation);

  sf::RenderTexture *rw = (sf::RenderTexture *)this->surface;
  rw->clear(sf::Color(255, 255, 255));
  rw->setView(*view);
  activeView = this;
}

void View::finish() {
  sf::RenderTexture *img = (sf::RenderTexture *)this->surface;
  sf::RenderWindow *rw = (sf::RenderWindow *)this->renderTarget;

  img->display();
  sf::Sprite s(img->getTexture());
  s.setPosition(this->screenPosition.x, this->screenPosition.y);
  rw->draw(s);
}

void View::setRenderTarget(sf::RenderWindow *renderTarget) {
  this->renderTarget = renderTarget;
}

sf::RenderTarget *View::getRenderTarget() { return this->surface; }

}  // namespace turbine
