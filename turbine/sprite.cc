#include "turbine/sprite.h"
#include "turbine/image_util.h"
#include "turbine/graphics.h"
#include "classes.h"

//#include "Resource.h"

/*
using namespace Turbine::Geom;
using namespace Turbine::Internal;

namespace Turbine
{
	namespace Extras
	{
		Sprite::Sprite(std::string path, Vector origin, int frames)
		{
			this->imageStrip = ResourceManager::getInstance()->Use<ImageStrip>(path, frames);
			this->origin = origin;
			this->frame = 0;
		}

		Image *Sprite::createImage(int frame, double rotation, double scale, Vector* vector)
		{
			SDL_Surface **frames = (SDL_Surface **) imageStrip->data;
			SDL_Surface *surface = frames[frame];

			Vector offset1 = Vector(0, 0), offset2 = Vector(0, 0);
			SDL_Surface *rotated = surface;
			if(rotation != 0) {
				rotated = ImageUtil::rotateImage(surface, Point(0, 0) + origin, &offset1, rotation);
			}
			SDL_Surface *scaled = rotated;
			if(scale != 1) {
				scaled = ImageUtil::scaleImage(rotated, Point(0, 0) + origin, &offset2, scale);
			}
			if(rotation != 0 && scale != 1) {
				SDL_FreeSurface(rotated);
			}

			if(vector != NULL) {
				*vector = offset1 + offset2 - origin;
			}
			Image *result = new Image();
			result->data = scaled;

			return result;
		}

		Sprite::~Sprite()
		{
			ResourceManager::getInstance()->Free(imageStrip);
		}

		AnimatedSprite::AnimatedSprite(std::string path, Vector origin, int frames, double speed)
		: Sprite(path, origin, frames)
		{
			this->speed = speed;
			this->preciseFrame = 0;
		}

		AnimatedSprite::~AnimatedSprite() {}

		void AnimatedSprite::setAnimationSpeed(double speed)
		{
			this->speed = speed;
		}

		void AnimatedSprite::next()
		{
			preciseFrame += speed;
			while(preciseFrame >= imageStrip->numFrames) {
				preciseFrame -= imageStrip->numFrames;
			}
			frame = (int)preciseFrame;
		}
	}
}
*/
