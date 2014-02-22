#include <assert.h>

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/OpenGl.hpp"

#include "iostream"

#include "Graphics.h"
#include "Game.h"
#include "ResourceCache.h"
#include "Exceptions.h"
#include "Geom.h"
#include "ImageUtil.h"
#include "View.h"

using namespace Turbine::Internal;
using namespace Turbine::Geom;

namespace Turbine {
namespace Internal {

SharedImage::SharedImage(std::string path, int arg)
{
	path = Game::getInstance().getResourcePath(path);
	image.LoadFromFile(path);
	image.CreateMaskFromColor(sf::Color(255, 0, 255));
}

SharedImage::~SharedImage() {}

SharedImage::SharedImage(int width, int height)
{
	image = sf::Image();
	image.Create(width, height, sf::Color(0,0,0,0));
}

SharedSprite::SharedSprite(std::string path, int arg)
{
	Turbine::Graphics::Image wholeImage(path);
	int w = wholeImage.getBBox().right / arg, h = wholeImage.getBBox().bottom;

	for(int i = 0; i < arg; i++) {
		Turbine::Graphics::Image frame(wholeImage, Geom::BoundingBox(i * w, (i + 1) * w, 0, h));
		frames.push_back(frame);
	}
}

SharedFont::SharedFont(std::string path, int arg)
{
	path = Game::getInstance().getResourcePath(path);
	font.LoadFromFile(path);
}
}

namespace Graphics {
Drawable::Drawable()
{
	setColor(Color());
	setScale(Vector(1, 1));
	setRotation(0);
	setOrigin(Point(0, 0));
}

void Drawable::copy(Drawable &other)
{
	setColor(other.color);
	setScale(other.scale);
	setRotation(other.rotation);
	setOrigin(other.origin);
}

void Drawable::setOrigin(Geom::Point origin)
{
	this->origin = origin;
}

void Drawable::setScale(Geom::Vector scale)
{
	this->scale = scale;
}

void Drawable::setRotation(float rotation)
{
	this->rotation = rotation;
}

void Drawable::setColor(Color c)
{
	this->color = c;
}

Geom::Point Drawable::getOrigin()
{
	return this->origin;
}

float Drawable::getRotation()
{
	return this->rotation;
}

Image::Image()
{
	img = NULL;
}

Image::Image(int width, int height)
{
	SharedImage *tmp = new SharedImage(width, height);
	tmp->add();

	this->img = tmp;
}

Image::Image(const Image& other, Geom::BoundingBox area)
{
	SharedImage *tmp = new SharedImage(area.right - area.left, area.bottom - area.top);
	tmp->add();

	tmp->image.Copy(((SharedImage *) other.img)->image, 0, 0, sf::IntRect(area.left, area.top, area.right, area.bottom));
	this->img = tmp;
}

Image::Image(std::string path)
{
	SharedImage *tmp = ResourceCache<SharedImage>::get()->Use(path);
	tmp->add();

	this->img = tmp;
}

Image& Image::operator=(const Image &rhs)
{
	if(this == &rhs) {
		return *this;
	}

	//Release old
	if(this->img != NULL) {
		SharedImage *tmp = (SharedImage *) img;
		tmp->remove();
	}

	//Use new resource
	this->img = rhs.img;
	SharedImage *tmp = (SharedImage *) this->img;
	tmp->add();

	//Copy scale etc
	copy((Drawable &) rhs);

	return *this;
}

Image::Image(const Image& other)
{
	SharedImage *tmp = (SharedImage *) other.img;
	tmp->add();
	img = tmp;

	//Copy scale etc
	copy((Drawable &) other);
}

Image::~Image()
{
	if(img != NULL) {
		SharedImage *tmp = (SharedImage *) img;
		tmp->remove();
	}
}

void Image::draw(Geom::Point position)
{
	sf::RenderTarget *rw = View::getCurrentView()->getRenderTarget();
	SharedImage *tmp = (SharedImage *) img;

	sf::Image *im = &(tmp->image);

	sf::Sprite sprite(tmp->image, sf::Vector2f(position.x, position.y));
	sprite.SetOrigin(origin.x, origin.y);
	sprite.SetScale(scale.x, scale.y);
	sprite.SetRotation(rotation);
	sprite.SetColor(sf::Color(color.r, color.g, color.b, color.a));
	rw->Draw(sprite);
}

bool Image::isValid()
{
	return img != NULL;
}

BoundingBox Image::getBBox()
{
	SharedImage *tmp = (SharedImage *) img;
	sf::Image *im = &(tmp->image);
	Point origin = getOrigin();
	return BoundingBox(-origin.x, im->GetWidth() - origin.x, -origin.y, im->GetHeight() - origin.y);
}

void Image::drawOnto(Graphics::Image target, Geom::Point position)
{
	SharedImage *tmp1 = (SharedImage *) target.img;
	sf::Image *s1 = &(tmp1->image);
	SharedImage *tmp2 = (SharedImage *) this->img;
	sf::Image *s2 = &(tmp2->image);

	sf::RenderImage img;
	img.Create(s1->GetWidth(), s1->GetHeight());
	img.Clear(sf::Color(255, 255, 255, 0));

	sf::Sprite sp1(*s1);
	sf::Sprite sp2(*s2, sf::Vector2f(position.x - this->origin.x, position.y - this->origin.y));
	img.Draw(sp1);
	img.Draw(sp2);
	img.Display();

	const sf::Image& result = img.GetImage();
	tmp1->image = sf::Image(result);
}

Font::Font()
{
	fnt = NULL;
}

Font::Font(std::string path, int size)
{
	SharedFont *tmp = ResourceCache<SharedFont>::get()->Use(path, size);
	tmp->add();

	this->fnt = tmp;
	this->size = size;
}

Font& Font::operator=(const Font &rhs)
{
	if(this == &rhs) {
		return *this;
	}

	//Free old
	if(fnt != NULL) {
		SharedFont *tmp = (SharedFont *) fnt;
		tmp->remove();
	}

	//Use new
	this->fnt = rhs.fnt;
	this->size = rhs.size;
	SharedFont *tmp = (SharedFont *) this->fnt;
	tmp->add();

	//Copy scale etc
	copy((Drawable &) rhs);

	return *this;
}

Font::Font(const Font& other)
{
	SharedFont *tmp = (SharedFont *) other.fnt;
	tmp->add();

	this->fnt = tmp;
	this->size = other.size;
	copy((Drawable &) other);
}

Font::~Font()
{
	if(fnt != NULL) {
		SharedFont *tmp = (SharedFont *) fnt;
		tmp->remove();
	}
}

void Font::draw(std::string txt, Geom::Point position)
{
	void *target = View::getCurrentView()->getRenderTarget();
	sf::RenderTarget *rw = (sf::RenderTarget *) target;
	SharedFont *tmp = (SharedFont *) fnt;

	sf::Text text(sf::String(txt), tmp->font, this->size);
	text.SetPosition(position.x, position.y);
	text.SetOrigin(origin.x, origin.y);
	text.SetScale(scale.x, scale.y);
	text.SetRotation(rotation);
	text.SetColor(sf::Color(color.r, color.g, color.b, color.a));
	rw->Draw(text);
}

Sprite::Sprite()
{
	spr = NULL;
}

Sprite::Sprite(std::string path, Geom::Point origin, int frames)
{
	SharedSprite *tmp = ResourceCache<SharedSprite>::get()->Use(path, frames);
	tmp->add();
	this->spr = tmp;
	this->setOrigin(origin);
	this->setFrame(0);
}

Sprite& Sprite::operator=(const Sprite &rhs)
{
	if(this == &rhs) {
		return *this;
	}

	if(spr != NULL) {
		SharedSprite *tmp = (SharedSprite *) spr;
		tmp->remove();
	}

	this->spr = rhs.spr;
	SharedSprite *tmp = (SharedSprite *) this->spr;
	tmp->add();

	this->copy((Drawable &) rhs);
	this->setFrame(rhs.frame);

	return *this;
}

Sprite::Sprite(const Sprite& other)
{
	SharedSprite *tmp = (SharedSprite *) other.spr;
	tmp->add();
	spr = tmp;

	this->copy((Drawable &) other);
	this->setFrame(other.frame);
}

Sprite::~Sprite()
{
	if(spr != NULL) {
		SharedSprite *tmp = (SharedSprite *) spr;
		tmp->remove();
	}
}

void Sprite::setFrame(int frame){
	this->frame = frame;
	SharedSprite *tmp = (SharedSprite *) spr;
	while(this->frame < 0) {
		this->frame += tmp->frames.size();
	}
	while(this->frame >= tmp->frames.size()) {
		this->frame -= tmp->frames.size();
	}
}

void Sprite::draw(Geom::Point position)
{
	SharedSprite *tmp = (SharedSprite *) spr;
	Image img = tmp->frames[frame];
	img.setOrigin(Point(origin.x, origin.y));
	img.setScale(Vector(scale.x, scale.y));
	img.setRotation(rotation);
	img.setColor(Color(color.r, color.g, color.b, color.a));
	img.draw(position);
}

void Sprite::draw(Geom::Point position, float rotation, Geom::Vector scale)
{
	SharedSprite *tmp = (SharedSprite *) spr;
	Image img = tmp->frames[frame];
	img.setOrigin(Point(origin.x, origin.y));
	img.setScale(Vector(scale.x, scale.y));
	img.setRotation(rotation);
	img.setColor(Color(color.r, color.g, color.b, color.a));
	img.draw(position);
}

void Sprite::drawOnto(Graphics::Image target, Geom::Point position)
{
	SharedSprite *tmp = (SharedSprite *) spr;
	Image img = tmp->frames[frame];
	img.drawOnto(target, position);
}

BoundingBox Sprite::getBBox()
{
	SharedSprite *tmp = (SharedSprite *) spr;
	Image img = tmp->frames[frame];
	return img.getBBox();
}

void drawLine(Geom::Point p1, Geom::Point p2, Color col)
{
	void *target = View::getCurrentView()->getRenderTarget();
	sf::RenderTarget *rw = (sf::RenderTarget *) target;

	sf::Color c(col.r, col.g, col.b, col.a);
	sf::Shape shape = sf::Shape::Line(p1.x, p1.y, p2.x, p2.y, 1.0, c);
	rw->Draw(shape);
}

void drawRectangle(Geom::BoundingBox bbox, Color col, bool outline)
{
	void *target = View::getCurrentView()->getRenderTarget();
	sf::RenderTarget *rw = (sf::RenderTarget *) target;

	sf::Color c(col.r, col.g, col.b, col.a);
	sf::Shape shape = sf::Shape::Rectangle(bbox.left, bbox.top, bbox.right - bbox.left, bbox.bottom - bbox.top, c);
	shape.EnableFill(!outline);
	shape.EnableOutline(outline);
	rw->Draw(shape);
}
}
}
