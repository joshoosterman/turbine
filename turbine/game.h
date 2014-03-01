// Copyright 2011

#ifndef TURBINE_GAME_H_
#define TURBINE_GAME_H_

#include <string>

#include "turbine/classes.h"
#include "turbine/geom.h"

namespace turbine {

/// Represents an instance of a computer game. Responsible for window settings,
/// frame rate control, and running the active level.
class Game {
 public:
  /// Constructor
  explicit Game(const Window &window);

  /// Destructor
  ~Game();

  /// Returns the active instance of a Game
  static Game &getInstance();

  /// Sets the active level
  void setActiveLevel(Level *activeLevel);

  /// Starts the game loop, using the given level as the first active level.
  void run(Level *level);

  /// Sets the desired frame rate for the game
  void setTargetFrameRate(int targetFrameRate);

  /// Gets the actual average number of frames rendered per second.
  float getFrameRate();

  /// Sets the path to load resources from
  void setBaseResourcePath(std::string path);

  /// Gets a resource path relative to the base resouce path
  std::string getResourcePath(std::string path);

  /// Gets the game window
  const Window &getWindow();

 private:
  static Game *inst;
  float fps, frameTime;
  std::string resourcePath;
  Level *activeLevel;
  const Window &window;
};

}  // namespace turbine

#endif  // TURBINE_GAME_H__
