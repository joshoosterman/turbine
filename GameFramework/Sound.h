#ifndef _SOUND_H
#define _SOUND_H

#include <string>
#include <map>
#include <assert.h>

#include "Classes.h"

namespace Turbine {
namespace Audio {

/// A sound effect
class Sound {
public:
	Sound();
	Sound(std::string path);
	Sound(const Sound& other);
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
	Music(std::string path);
	Music(const Music& other);
	Music &operator=(const Music &rhs);
	~Music();

	void play(bool loop);

private:
	void *mus;
};

}
}

#endif
