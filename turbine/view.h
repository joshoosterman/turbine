// Copyright 2011

#ifndef TURBINE_VIEW_H_
#define TURBINE_VIEW_H_

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RenderTexture.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

#include "turbine/classes.h"

namespace turbine {

/// Represents a viewport of a level to be rendered to the screen
class View {
 public:
  View(geom::Point screenPosition, geom::Vector size);
  ~View();

  void setWindowPosition(geom::Point p);
  void setSize(geom::Vector s);
  void setPosition(geom::Point p);
  void setRotation(float rotation);
  void setMovementStrategy(extras::MovementStrategy *strat);

  geom::Point getWindowPosition();
  geom::Vector getSize();
  geom::Vector getPosition();
  float getRotation();

  void setEnabled(bool enabled);

  void update();
  void activate();
  void finish();

  static View *getCurrentView();
  void setRenderTarget(sf::RenderWindow *renderTarget);
  sf::RenderTarget *getRenderTarget();

  bool enabled;

 private:
  geom::Point screenPosition;
  geom::Vector position;
  geom::Vector size;
  float rotation;

  bool needsUpdate;

  Level *level;

  sf::RenderTarget *surface;
  sf::RenderWindow *renderTarget;
  sf::View *view;
  static View *activeView;
  extras::MovementStrategy *strat;
};

}  // namespace turbine

#endif  // TURBINE_VIEW_H_
