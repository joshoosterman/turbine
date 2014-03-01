// Copyright 2011

#include <assert.h>

#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include "SFML/System.hpp"

#include "turbine/exceptions.h"
#include "turbine/game.h"
#include "turbine/geom.h"
#include "turbine/graphics.h"
#include "turbine/image_util.h"
#include "turbine/resource_cache.h"
#include "turbine/view.h"

// TODO(joshoosterman): Replace all these shared image things with smart
// pointers or something simpler instead.

namespace turbine {
namespace internal {

SharedImage::SharedImage(std::string path, int arg) {
  path = Game::getInstance().getResourcePath(path);
  image.loadFromFile(path);
  image.createMaskFromColor(sf::Color(255, 0, 255));
}

SharedImage::~SharedImage() {}

SharedImage::SharedImage(int width, int height) {
  image = sf::Image();
  image.create(width, height, sf::Color(0, 0, 0, 0));
}

SharedSprite::SharedSprite(std::string path, int arg) {
  turbine::graphics::Image wholeImage(path);
  int w = wholeImage.getBBox().right / arg, h = wholeImage.getBBox().bottom;

  for (int i = 0; i < arg; i++) {
    turbine::graphics::Image frame(wholeImage,
                                   geom::BoundingBox(i * w, (i + 1) * w, 0, h));
    frames.push_back(frame);
  }
}

SharedFont::SharedFont(std::string path, int arg) {
  path = Game::getInstance().getResourcePath(path);
  font.loadFromFile(path);
}
}  // namespace internal

namespace graphics {
Drawable::Drawable() {
  setColor(Color());
  setScale(geom::Vector(1, 1));
  setRotation(0);
  setOrigin(geom::Point(0, 0));
}

void Drawable::copy(const Drawable &other) {
  setColor(other.color);
  setScale(other.scale);
  setRotation(other.rotation);
  setOrigin(other.origin);
}

void Drawable::setOrigin(geom::Point origin) { this->origin = origin; }

void Drawable::setScale(geom::Vector scale) { this->scale = scale; }

void Drawable::setRotation(float rotation) { this->rotation = rotation; }

void Drawable::setColor(Color c) { this->color = c; }

geom::Point Drawable::getOrigin() { return this->origin; }

float Drawable::getRotation() { return this->rotation; }

Image::Image() { img = NULL; }

Image::Image(int width, int height) {
  internal::SharedImage *tmp = new internal::SharedImage(width, height);
  tmp->add();

  this->img = tmp;
}

Image::Image(const Image &other, geom::BoundingBox area) {
  internal::SharedImage *tmp =
      new internal::SharedImage(area.right - area.left, area.bottom - area.top);
  tmp->add();

  tmp->image
      .copy((reinterpret_cast<internal::SharedImage *>(other.img))->image, 0, 0,
            sf::IntRect(area.left, area.top, area.right, area.bottom));
  this->img = tmp;
}

Image::Image(std::string path) {
  internal::SharedImage *tmp =
      internal::ResourceCache<internal::SharedImage>::get()->Use(path);
  tmp->add();

  this->img = tmp;
}

Image &Image::operator=(const Image &rhs) {
  if (this == &rhs) {
    return *this;
  }

  // Release old
  if (this->img != NULL) {
    internal::SharedImage *tmp = reinterpret_cast<internal::SharedImage *>(img);
    tmp->remove();
  }

  // Use new resource
  this->img = rhs.img;
  internal::SharedImage *tmp =
      reinterpret_cast<internal::SharedImage *>(this->img);
  tmp->add();

  // Copy scale etc
  copy((Drawable &)rhs);

  return *this;
}

Image::Image(const Image &other) {
  internal::SharedImage *tmp =
      reinterpret_cast<internal::SharedImage *>(other.img);
  tmp->add();
  img = tmp;

  // Copy scale etc
  copy((Drawable &)other);
}

Image::~Image() {
  if (img != NULL) {
    internal::SharedImage *tmp = reinterpret_cast<internal::SharedImage *>(img);
    tmp->remove();
  }
}

void Image::draw(geom::Point position) {
  sf::RenderTarget *rw = View::getCurrentView()->getRenderTarget();
  internal::SharedImage *tmp = reinterpret_cast<internal::SharedImage *>(img);

  // sf::Image *im = &(tmp->image);

  // TODO(joshoosterman): Probably very inefficient?
  // figure out what 'Texture' is and how it relates to 'Image'.
  sf::Texture t;
  t.loadFromImage(tmp->image);

  sf::Sprite sprite(t);
  sprite.setPosition(sf::Vector2f(position.x, position.y));
  sprite.setOrigin(origin.x, origin.y);
  sprite.setScale(scale.x, scale.y);
  sprite.setRotation(rotation);
  sprite.setColor(sf::Color(color.r, color.g, color.b, color.a));
  rw->draw(sprite);
}

bool Image::isValid() const { return img != NULL; }

geom::BoundingBox Image::getBBox() {
  internal::SharedImage *tmp = reinterpret_cast<internal::SharedImage *>(img);
  sf::Image *im = &(tmp->image);
  geom::Point origin = getOrigin();
  return geom::BoundingBox(-origin.x, im->getSize().x - origin.x, -origin.y,
                           im->getSize().y - origin.y);
}

void Image::drawOnto(graphics::Image target, geom::Point position) {
  internal::SharedImage *tmp1 =
      reinterpret_cast<internal::SharedImage *>(target.img);
  sf::Image *s1 = &(tmp1->image);
  internal::SharedImage *tmp2 =
      reinterpret_cast<internal::SharedImage *>(this->img);
  sf::Image *s2 = &(tmp2->image);

  sf::RenderTexture rt;
  rt.create(s1->getSize().x, s1->getSize().y);  // overload?
  rt.clear(sf::Color(255, 255, 255, 0));

  // slow!
  sf::Texture t1;
  t1.loadFromImage(*s1);
  sf::Texture t2;
  t2.loadFromImage(*s2);

  sf::Sprite sp1(t1);
  sf::Sprite sp2(t2);
  sp2.setPosition(
      sf::Vector2f(position.x - this->origin.x, position.y - this->origin.y));
  rt.draw(sp1);
  rt.draw(sp2);
  rt.display();

  const sf::Image result = rt.getTexture().copyToImage();
  tmp1->image = sf::Image(result);
}

Font::Font() { fnt = NULL; }

Font::Font(std::string path, int size) {
  internal::SharedFont *tmp =
      internal::ResourceCache<internal::SharedFont>::get()->Use(path, size);
  tmp->add();

  this->fnt = tmp;
  this->size = size;
}

Font &Font::operator=(const Font &rhs) {
  if (this == &rhs) {
    return *this;
  }

  // Free old
  if (fnt != NULL) {
    internal::SharedFont *tmp = reinterpret_cast<internal::SharedFont *>(fnt);
    tmp->remove();
  }

  // Use new
  this->fnt = rhs.fnt;
  this->size = rhs.size;
  internal::SharedFont *tmp =
      reinterpret_cast<internal::SharedFont *>(this->fnt);
  tmp->add();

  // Copy scale etc
  copy((Drawable &)rhs);

  return *this;
}

Font::Font(const Font &other) {
  internal::SharedFont *tmp =
      reinterpret_cast<internal::SharedFont *>(other.fnt);
  tmp->add();

  this->fnt = tmp;
  this->size = other.size;
  copy((Drawable &)other);
}

Font::~Font() {
  if (fnt != NULL) {
    internal::SharedFont *tmp = reinterpret_cast<internal::SharedFont *>(fnt);
    tmp->remove();
  }
}

void Font::draw(std::string txt, geom::Point position) {
  void *target = View::getCurrentView()->getRenderTarget();
  sf::RenderTarget *rw = (sf::RenderTarget *)target;
  internal::SharedFont *tmp = reinterpret_cast<internal::SharedFont *>(fnt);

  sf::Text text(sf::String(txt), tmp->font, this->size);
  text.setPosition(position.x, position.y);
  text.setOrigin(origin.x, origin.y);
  text.setScale(scale.x, scale.y);
  text.setRotation(rotation);
  text.setColor(sf::Color(color.r, color.g, color.b, color.a));
  rw->draw(text);
}

Sprite::Sprite() { spr = NULL; }

Sprite::Sprite(std::string path, geom::Point origin, int frames) {
  internal::SharedSprite *tmp =
      internal::ResourceCache<internal::SharedSprite>::get()->Use(path, frames);
  tmp->add();
  this->spr = tmp;
  this->setOrigin(origin);
  this->setFrame(0);
}

Sprite &Sprite::operator=(const Sprite &rhs) {
  if (this == &rhs) {
    return *this;
  }

  if (spr != NULL) {
    internal::SharedSprite *tmp =
        reinterpret_cast<internal::SharedSprite *>(spr);
    tmp->remove();
  }

  this->spr = rhs.spr;
  internal::SharedSprite *tmp =
      reinterpret_cast<internal::SharedSprite *>(this->spr);
  tmp->add();

  this->copy((Drawable &)rhs);
  this->setFrame(rhs.frame);

  return *this;
}

Sprite::Sprite(const Sprite &other) {
  internal::SharedSprite *tmp =
      reinterpret_cast<internal::SharedSprite *>(other.spr);

  tmp->add();
  spr = tmp;

  this->copy((Drawable &)other);
  this->setFrame(other.frame);
}

Sprite::~Sprite() {
  if (spr != NULL) {
    internal::SharedSprite *tmp =
        reinterpret_cast<internal::SharedSprite *>(spr);
    tmp->remove();
  }
}

void Sprite::setFrame(int frame) {
  this->frame = frame;
  internal::SharedSprite *tmp = reinterpret_cast<internal::SharedSprite *>(spr);
  while (this->frame < 0) {
    this->frame += tmp->frames.size();
  }
  while (this->frame >= tmp->frames.size()) {
    this->frame -= tmp->frames.size();
  }
}

void Sprite::draw(geom::Point position) {
  internal::SharedSprite *tmp = reinterpret_cast<internal::SharedSprite *>(spr);
  Image img = tmp->frames[frame];
  img.setOrigin(geom::Point(origin.x, origin.y));
  img.setScale(geom::Vector(scale.x, scale.y));
  img.setRotation(rotation);
  img.setColor(Color(color.r, color.g, color.b, color.a));
  img.draw(position);
}

void Sprite::draw(geom::Point position, float rotation, geom::Vector scale) {
  internal::SharedSprite *tmp = reinterpret_cast<internal::SharedSprite *>(spr);
  Image img = tmp->frames[frame];
  img.setOrigin(geom::Point(origin.x, origin.y));
  img.setScale(geom::Vector(scale.x, scale.y));
  img.setRotation(rotation);
  img.setColor(Color(color.r, color.g, color.b, color.a));
  img.draw(position);
}

void Sprite::drawOnto(graphics::Image target, geom::Point position) {
  internal::SharedSprite *tmp = reinterpret_cast<internal::SharedSprite *>(spr);
  Image img = tmp->frames[frame];
  img.drawOnto(target, position);
}

geom::BoundingBox Sprite::getBBox() {
  internal::SharedSprite *tmp = reinterpret_cast<internal::SharedSprite *>(spr);
  Image img = tmp->frames[frame];
  return img.getBBox();
}

void drawLine(geom::Point p1, geom::Point p2, Color col) {
  return;
  /*void *target = View::getCurrentView()->getRenderTarget();
 	sf::RenderTarget *rw = (sf::RenderTarget *) target;
 
 	sf::Color c(col.r, col.g, col.b, col.a);
 	sf::Shape shape = sf::Shape::Line(p1.x, p1.y, p2.x, p2.y, 1.0, c);
 	rw->Draw(shape);*/
}

void drawRectangle(geom::BoundingBox bbox, Color col, bool outline) {
  void *target = View::getCurrentView()->getRenderTarget();
  sf::RenderTarget *rw = (sf::RenderTarget *)target;

  sf::Color c(col.r, col.g, col.b, col.a);
  sf::RectangleShape shape;
  shape.setPosition(bbox.left, bbox.top);
  shape.setSize(sf::Vector2f(bbox.right - bbox.left, bbox.bottom - bbox.top));
  shape.setFillColor(c);
  shape.setOutlineColor(c);
  // TODO(joshoosterman): Fix.
  // shape.EnableFill(!outline);
  // shape.EnableOutline(outline);
  rw->draw(shape);
}

}  // namespace graphics
}  // namespace turbine
