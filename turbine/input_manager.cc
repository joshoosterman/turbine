// Copyright 2011

#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include "turbine/exceptions.h"
#include "turbine/geom.h"
#include "turbine/input_manager.h"
#include "turbine/view.h"

namespace turbine {
namespace input {

InputManager *InputManager::instance = NULL;

InputManager *InputManager::getInstance() {
  if (instance == NULL) {
    instance = new InputManager();
  }

  return instance;
}

// TODO(joshoosterman): This module is pretty much redundant with SFML2
// providing.

// Static functions for checking keyboard & mouse state.

bool InputManager::keyDown(sf::Keyboard::Key key) {
  return sf::Keyboard::isKeyPressed(key);
}

bool InputManager::keyPressed(sf::Keyboard::Key key) { return false; }

bool InputManager::keyReleased(sf::Keyboard::Key key) { return false; }

geom::Point InputManager::mouseGetViewPosition(View *view) {
  return mouseGetWindowPosition() + view->getPosition();
}

geom::Point InputManager::mouseGetWindowPosition() {
  sf::Vector2i pos = sf::Mouse::getPosition();
  return geom::Point(pos.x, pos.y);
}

bool InputManager::mouseGetLeftButtonDown() {
  return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

bool InputManager::mouseGetMiddleButtonDown() {
  return sf::Mouse::isButtonPressed(sf::Mouse::Middle);
}

bool InputManager::mouseGetRightButtonDown() {
  return sf::Mouse::isButtonPressed(sf::Mouse::Right);
}

}  // namespace input
}  // namespace turbine
