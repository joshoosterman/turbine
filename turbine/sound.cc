// Copyright 2011

#include <assert.h>

#include "SFML/System.hpp"
#include "SFML/Audio.hpp"

#include "turbine/exceptions.h"
#include "turbine/game.h"
#include "turbine/geom.h"
#include "turbine/resource_cache.h"
#include "turbine/sound.h"

namespace turbine {
namespace internal {

SharedSound::SharedSound(std::string path, int arg) {
  path = Game::getInstance().getResourcePath(path);
  sf::SoundBuffer buff;
  buff.loadFromFile(path);
  sound = sf::Sound(buff);
}

SharedMusic::SharedMusic(std::string path, int arg) {
  path = Game::getInstance().getResourcePath(path);
  music.openFromFile(path);
}
}  // namespace internal

namespace audio {

Sound::Sound() { snd = NULL; }

Sound::Sound(std::string path) {
  internal::SharedSound *tmp =
      internal::ResourceCache<internal::SharedSound>::get()->Use(path);
  tmp->add();

  this->snd = tmp;
}

Sound &Sound::operator=(const Sound &rhs) {
  if (this == &rhs) {
    return *this;
  }

  // Release old
  if (this->snd != NULL) {
    internal::SharedSound *tmp = reinterpret_cast<internal::SharedSound *>(snd);
    tmp->remove();
  }

  // Use new resource
  this->snd = rhs.snd;
  internal::SharedSound *tmp =
      reinterpret_cast<internal::SharedSound *>(this->snd);
  tmp->add();

  return *this;
}

Sound::Sound(const Sound &other) {
  internal::SharedSound *tmp =
      reinterpret_cast<internal::SharedSound *>(other.snd);
  tmp->add();
  snd = tmp;
}

Sound::~Sound() {
  if (snd != NULL) {
    internal::SharedSound *tmp = reinterpret_cast<internal::SharedSound *>(snd);
    tmp->remove();
  }
}

void Sound::play() {
  internal::SharedSound *tmp = reinterpret_cast<internal::SharedSound *>(snd);
  // sf::Sound *snd = &(tmp->sound);
  // snd->Play();
}

Music::Music() { mus = NULL; }

Music::Music(std::string path) {
  internal::SharedMusic *tmp =
      internal::ResourceCache<internal::SharedMusic>::get()->Use(path);
  tmp->add();

  this->mus = tmp;
}

Music &Music::operator=(const Music &rhs) {
  if (this == &rhs) {
    return *this;
  }

  // Release old
  if (this->mus != NULL) {
    internal::SharedMusic *tmp = reinterpret_cast<internal::SharedMusic *>(mus);
    tmp->remove();
  }

  // Use new resource
  this->mus = rhs.mus;
  internal::SharedMusic *tmp =
      reinterpret_cast<internal::SharedMusic *>(this->mus);
  tmp->add();

  return *this;
}

Music::Music(const Music &other) {
  internal::SharedMusic *tmp =
      reinterpret_cast<internal::SharedMusic *>(other.mus);
  tmp->add();
  mus = tmp;
}

Music::~Music() {
  if (mus != NULL) {
    internal::SharedMusic *tmp = reinterpret_cast<internal::SharedMusic *>(mus);
    tmp->remove();
  }
}

void Music::play(bool loop) {
  internal::SharedMusic *tmp = reinterpret_cast<internal::SharedMusic *>(mus);
  // sf::Music *mus = &(tmp->music);
  // mus->SetLoop(loop);
  // mus->Play();
}
}  // namespace audio
}  // namespace turbine
