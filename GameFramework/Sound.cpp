#include <assert.h>

#include "SFML/System.hpp"
#include "SFML/Audio.hpp"

#include "Sound.h"
#include "ResourceCache.h"
#include "Exceptions.h"
#include "Geom.h"
#include "Game.h"

using namespace Turbine::Internal;
using namespace Turbine::Geom;

namespace Turbine {
namespace Internal {

SharedSound::SharedSound(std::string path, int arg)
{
	path = Game::getInstance().getResourcePath(path);
	sf::SoundBuffer buff;
	buff.LoadFromFile(path);
	sound = sf::Sound(buff);
}

SharedMusic::SharedMusic(std::string path, int arg)
{
	path = Game::getInstance().getResourcePath(path);
	music.OpenFromFile(path);
}
}

namespace Audio {

Sound::Sound()
{
	snd = NULL;
}

Sound::Sound(std::string path)
{
	SharedSound *tmp = ResourceCache<SharedSound>::get()->Use(path);
	tmp->add();

	this->snd = tmp;
}

Sound& Sound::operator=(const Sound &rhs)
{
	if(this == &rhs) {
		return *this;
	}

	//Release old
	if(this->snd != NULL) {
		SharedSound *tmp = (SharedSound *) snd;
		tmp->remove();
	}

	//Use new resource
	this->snd = rhs.snd;
	SharedSound *tmp = (SharedSound *) this->snd;
	tmp->add();

	return *this;
}

Sound::Sound(const Sound& other)
{
	SharedSound *tmp = (SharedSound *) other.snd;
	tmp->add();
	snd = tmp;
}

Sound::~Sound()
{
	if(snd != NULL) {
		SharedSound *tmp = (SharedSound *) snd;
		tmp->remove();
	}
}

void Sound::play()
{
	SharedSound *tmp = (SharedSound *) snd;
	//sf::Sound *snd = &(tmp->sound);
	//snd->Play();
}

Music::Music()
{
	mus = NULL;
}

Music::Music(std::string path)
{
	SharedMusic *tmp = ResourceCache<SharedMusic>::get()->Use(path);
	tmp->add();

	this->mus = tmp;
}

Music& Music::operator=(const Music &rhs)
{
	if(this == &rhs) {
		return *this;
	}

	//Release old
	if(this->mus != NULL) {
		SharedMusic *tmp = (SharedMusic *) mus;
		tmp->remove();
	}

	//Use new resource
	this->mus = rhs.mus;
	SharedMusic *tmp = (SharedMusic *) this->mus;
	tmp->add();

	return *this;
}

Music::Music(const Music& other)
{
	SharedMusic *tmp = (SharedMusic *) other.mus;
	tmp->add();
	mus = tmp;
}

Music::~Music()
{
	if(mus != NULL) {
		SharedMusic *tmp = (SharedMusic *) mus;
		tmp->remove();
	}
}

void Music::play(bool loop)
{
	SharedMusic *tmp = (SharedMusic *) mus;
	//sf::Music *mus = &(tmp->music);
	//mus->SetLoop(loop);
	//mus->Play();
}
}
}
