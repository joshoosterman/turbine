#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <string>
#include <map>
#include <assert.h>

#include "classes.h"
#include "turbine/geom.h"

#define MAX_DEPTH 100.0

namespace Turbine {
namespace Graphics {

/// Represents a color as an R,G,B tuple
struct Color {
	int r, g, b, a;
	Color() : r(255), g(255), b(255), a(255) {}
	Color(int rgba) : r((rgba & 0xFF000000) >> 24), g((rgba & 0x00FF0000) >> 16), b((rgba & 0x0000FF00) >> 8), a(rgba & 0x000000FF) {}
	Color(int r, int g, int b) : r(r), g(g), b(b), a(255) {}
	Color(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) {}
};

/// An abstract, drawable object that can have various transformations applied
class Drawable {
public:
	Drawable();
	void setOrigin(Geom::Point origin);
	void setScale(Geom::Vector scale);
	void setRotation(float rotation);
	void setColor(Color c);

	Geom::Point getOrigin();
	float getRotation();

protected:
	void copy(Drawable &other);

	Geom::Point origin;
	Geom::Vector scale;
	float rotation;
	Color color;
};

/// An image repesents a bitmap of pixels that can be positioned and drawn onto the screen. An
/// image object uses reference counting, so copying an image is efficient.
class Image : public Drawable {
public:
	Image();
	Image(int width, int height);
	Image(const Image& other, Geom::BoundingBox area);
	Image(std::string path);
	Image(const Image& other);
	Image &operator=(const Image &rhs);
	~Image();

	void draw(Geom::Point position);
	void drawOnto(Graphics::Image target, Geom::Point position);

	Geom::Size getSize();
	Geom::BoundingBox getBBox();
	bool isValid();
	bool collides();

private:
	friend class ImageUtil;
	void *img;
};

/// A font can format, position and draw a text string onto the screen. A
/// font object uses reference counting, so copying an font is efficient.
class Font : public Drawable {
public:
	Font();
	Font(std::string path, int size);
	Font(const Font& other);
	Font &operator=(const Font &rhs);
	~Font();

	void draw(std::string text, Geom::Point position);

private:
	void *fnt;
	int size;
};

/// A sprite repesents a series of images that can be positioned and drawn onto the screen. 
/// Sprites can be used to represent animated objects. A sprite object uses reference
/// counting, so copying an image is efficient.
class Sprite : public Drawable {
public:
	Sprite();
	Sprite(std::string path, Geom::Point origin, int frames);
	Sprite(const Sprite& other);
	Sprite &operator=(const Sprite &rhs);
	~Sprite();

	void draw(Geom::Point position);
	void draw(Geom::Point position, float rotation, Geom::Vector scale);
	void drawOnto(Graphics::Image target, Geom::Point position);
	void setFrame(int frame);

	Geom::Size getSize();
	Geom::BoundingBox getBBox();

private:
	int frame;
	void *spr;
};

//Other graphical functions
void drawLine(Geom::Point p1, Geom::Point p2, Color col);
void drawRectangle(Geom::BoundingBox, Color col, bool outline = true);
}
}

#endif
