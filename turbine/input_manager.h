// Copyright 2011

#ifndef TURBINE_INPUT_MANAGER_H_
#define TURBINE_INPUT_MANAGER_H_

#include "turbine/classes.h"
#include "SFML/Window/Keyboard.hpp"

typedef unsigned char uint8_t;
typedef uint8_t Uint8;

namespace turbine {
namespace input {

/// Provides functions to check input devices such as the keyboard and house
class InputManager {
 public:
  static InputManager *getInstance();

  bool keyDown(sf::Keyboard::Key key);
  bool keyPressed(sf::Keyboard::Key key);
  bool keyReleased(sf::Keyboard::Key key);

  geom::Point mouseGetWindowPosition();
  geom::Point mouseGetViewPosition(View *view);
  bool mouseGetLeftButtonDown();
  bool mouseGetMiddleButtonDown();
  bool mouseGetRightButtonDown();

  static InputManager *instance;
};

struct KeyEvent {
  KeyEvent() {}
  sf::Keyboard::Key key;
};

struct MouseEvent {
  MouseEvent() {}
};

}  // namespace input
}  // namespace turbine

#endif  // TURBINE_INPUT_MANAGER_H_
