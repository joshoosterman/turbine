// Copyright 2011

#ifndef TURBINE_GRAPHICS_H_
#define TURBINE_GRAPHICS_H_

#include <assert.h>
#include <algorithm>
#include <map>
#include <string>

#include "turbine/classes.h"
#include "turbine/geom.h"

#define MAX_DEPTH 100.0

namespace turbine {
namespace graphics {

/// Represents a color as an R,G,B tuple
struct Color {
  int r, g, b, a;
  Color() : r(255), g(255), b(255), a(255) {}
  explicit Color(int rgba)
      : r((rgba & 0xFF000000) >> 24),
        g((rgba & 0x00FF0000) >> 16),
        b((rgba & 0x0000FF00) >> 8),
        a(rgba & 0x000000FF) {}
  Color(int r, int g, int b) : r(r), g(g), b(b), a(255) {}
  Color(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) {}
};

/// An abstract, drawable object that can have various transformations applied
class Drawable {
 public:
  Drawable();
  void setOrigin(geom::Point origin);
  void setScale(geom::Vector scale);
  void setRotation(float rotation);
  void setColor(Color c);

  geom::Point getOrigin();
  float getRotation();

 protected:
  void copy(const Drawable &other);

  geom::Point origin;
  geom::Vector scale;
  float rotation;
  Color color;
};

/// An image repesents a bitmap of pixels that can be positioned and drawn onto
/// the screen. An
/// image object uses reference counting, so copying an image is efficient.
class Image : public Drawable {
 public:
  Image();
  Image(int width, int height);
  Image(const Image &other, geom::BoundingBox area);
  explicit Image(std::string path);
  Image(const Image &other);
  Image &operator=(const Image &rhs);
  ~Image();

  void draw(geom::Point position);
  void drawOnto(graphics::Image target, geom::Point position);

  geom::Size getSize();
  geom::BoundingBox getBBox();
  bool isValid() const;
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
  Font(const Font &other);
  Font &operator=(const Font &rhs);
  ~Font();

  void draw(std::string text, geom::Point position);

 private:
  void *fnt;
  int size;
};

/// A sprite repesents a series of images that can be positioned and drawn onto
/// the screen.
/// Sprites can be used to represent animated objects. A sprite object uses
/// reference
/// counting, so copying an image is efficient.
class Sprite : public Drawable {
 public:
  Sprite();
  Sprite(std::string path, geom::Point origin, int frames);
  Sprite(const Sprite &other);
  Sprite &operator=(const Sprite &rhs);
  ~Sprite();

  void draw(geom::Point position);
  void draw(geom::Point position, float rotation, geom::Vector scale);
  void drawOnto(graphics::Image target, geom::Point position);
  void setFrame(int frame);

  geom::Size getSize();
  geom::BoundingBox getBBox();

 private:
  int frame;
  void *spr;
};

// Other graphical functions
void drawLine(geom::Point p1, geom::Point p2, Color col);
void drawRectangle(geom::BoundingBox, Color col, bool outline = true);

}  // namespace graphics
}  // namespace turbine

#endif  // TURBINE_GRAPHICS_H_
