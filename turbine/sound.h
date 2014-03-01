// Copyright 2011

#ifndef TURBINE_SOUND_H_
#define TURBINE_SOUND_H_

#include <string>
#include <map>

#include "turbine/classes.h"

namespace turbine {
namespace audio {

/// A sound effect
class Sound {
 public:
  Sound();
  explicit Sound(std::string path);
  Sound(const Sound &other);
  Sound &operator=(const Sound &rhs);
  ~Sound();

  void play();

 private:
  void *snd;
};

/// A longer sound file that should be streamed
class Music {
 public:
  Music();
  explicit Music(std::string path);
  Music(const Music &other);
  Music &operator=(const Music &rhs);
  ~Music();

  void play(bool loop);

 private:
  void *mus;
};

}  // namespace audio
}  // namespace turbine

#endif  // TURBINE_SOUND_H_
