#ifndef _RESOURCE_CACHE_H
#define _RESOURCE_CACHE_H

#include <string>
#include <map>
#include <assert.h>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "Classes.h"

namespace Turbine {
namespace Internal {

template <class T>
class ResourceCache {
private:
	ResourceCache() {}
	static ResourceCache* instance;
	std::map<std::string, T*> cache;

public:
	static ResourceCache *get() {
		if(instance == NULL) {
			instance = new ResourceCache();
		}
		return instance;
	}

	T* Use(std::string filePath, int arg = 0) {
		//TODO: Fix cache to handle different resource types from the same file
		if(cache.find(filePath) == cache.end())
		{
			T *res = new T(filePath, arg);
			cache[filePath] = res;
		}

		return cache[filePath];
	}

	void Remove(T *t){
		typename std::map<std::string, T*>::iterator it;
		for(it = cache.begin(); it != cache.end(); it++) {
			if((*it).second == t) {
				break;
			}
		}
		if(it != cache.end()) {
			cache.erase(it);
		}
	}
};

template <class T>
class SharedResource {
public:
	SharedResource() {
		numUsers = 0;
	}

	virtual ~SharedResource() {}

	void add()
	{
		numUsers++;
	}

	void remove()
	{
		numUsers--;
		if(numUsers == 0) {
			ResourceCache<SharedResource<T> >::get()->Remove(this);
			delete this;
		}
	}

private:
	int numUsers;
};

class SharedImage : public SharedResource<SharedImage> {
public:
	SharedImage(std::string path, int arg);
	~SharedImage();
	SharedImage(int width, int height);
	sf::Image image;
};

class SharedFont : public SharedResource<SharedFont> {
public:
	SharedFont(std::string path, int arg);
	sf::Font font;
};

class SharedSprite : public SharedResource<SharedSprite> {
public:
	SharedSprite(std::string path, int arg);
	std::vector<Turbine::Graphics::Image> frames;
	int numFrames;
};

class SharedSound : public SharedResource<SharedSound> {
public:
	SharedSound(std::string path, int arg);
	sf::Sound sound;
};

class SharedMusic : public SharedResource<SharedMusic> {
public:
	SharedMusic(std::string path, int arg);
	sf::Music music;
};

template <class T>
ResourceCache<T> *ResourceCache<T>::instance;
}
}

#endif
