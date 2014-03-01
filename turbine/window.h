// Copyright 2011

#ifndef TURBINE_WINDOW_H_
#define TURBINE_WINDOW_H_

#include <string>

#include "SFML/Graphics/RenderWindow.hpp"

#include "turbine/classes.h"
#include "turbine/geom.h"

namespace turbine {

class Window {
 public:
  Window(std::string caption, geom::Size size);
  ~Window();

  /// Sets the caption of the game window.
  void setCaption(std::string caption);

  /// Sets the size of the game window, in pixels.
  void setSize(geom::Size size);

  /// Sets the game to fullscreen or windowed mode.
  void setFullScreen(bool fullScreen);

  /// Sets the visibility of the cursor, when positioned over the game window.
  void setCursorVisible(bool cursorVisible);

  /// Gets the SFML render window object, useful for rendering and retrieving
  /// events.
  sf::RenderWindow &getRenderTarget() const;

 private:
  void initWindow();

  geom::Size size;
  std::string caption;
  sf::RenderWindow *rWindow;
};

}  // namespace turbine

#endif  // TURBINE_WINDOW_H_
