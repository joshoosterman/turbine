// Copyright 2011

#include "SFML/Window/Event.hpp"

#include "turbine/turbine.h"

#include <string>
#include <sstream>
#include <cstdio>
#include <math.h>
#include <typeinfo>

using namespace turbine;
using namespace turbine::geom;
using namespace turbine::input;
using namespace turbine::graphics;
using namespace turbine::audio;
using namespace turbine::physics;

class DemoLevel : public Level {
 public:
  DemoLevel(std::string text, int id, int background);
  virtual void doInit();

  std::string text;
  int id;
  DemoLevel *next;
  DemoLevel *previous;

 protected:
  virtual void init() = 0;
  bool hasInit;
};

class Background : public GameObject {
 public:
  Background(std::string imageFile);
  ~Background();

  void init();
  static void draw(Object *me);
  static void step(Object *me);
  static void click(Object *me, input::MouseEvent ev);

 private:
  Sprite sprite;
};

class LevelLabel : public GameObject {
 public:
  LevelLabel(DemoLevel *dl);
  ~LevelLabel();
  void init();

  static void draw(Object *me);
  static void keydown(Object *me, input::KeyEvent ev);

 private:
  DemoLevel *dlevel;
  Sprite keys;
  Font font;
};

class Arrow : public GameObject {
 public:
  Point origin;
  Vector dir;
  int life;
  static void draw(Object *me) {
    Arrow *self = (Arrow *)me;
    if (self->life > 0) {
      Point end = self->origin + (self->dir * 30);

      drawLine(self->origin, end, Color(0xFF0000FF));
      Point tip1 = end - self->dir.rotate(30) * 5;
      drawLine(end, tip1, Color(0xFF0000FF));
      Point tip2 = end - self->dir.rotate(-30) * 5;
      drawLine(end, tip2, Color(0xFF0000FF));
      self->life--;
    } else {
      self->destroy();
    }
  }

  Arrow(Point origin, Vector dir) {
    this->dir = dir;
    this->origin = origin - dir * 8;
    life = 100;
  }

  void init() { registerDrawEvent(&Arrow::draw, 40); }

  ~Arrow() { unregisterDrawEvent(&Arrow::draw, 40); }
};

class Pinball : public GameObject {
 public:
  Sprite sprite;
  Vector velocity;
  bool stopped;

  static void draw(Object *me) {
    Pinball *self = (Pinball *)me;
    self->sprite.draw(self->location);
    drawRectangle(self->getBoundingBox(), Color(0xFF000000));
  }

  static void step(Object *me) {
    Pinball *self = (Pinball *)me;
    if (!self->stopped) {
      self->location = self->location + self->velocity;
    }
  }

  static void collide(GameObject *me, GameObject *other, Vector normal) {
    Pinball *self = (Pinball *)me;

    /*if (normal.dotProduct(self->velocity) > 0)
  			normal = normal.negative();*/
    Vector escape = normal;
    /*if (self->velocity.x != 0 && self->velocity.y != 0 && !self->stopped){
  			escape = self->velocity.unit().negative();
  		}*/
    while (self->collides(other)) {
      self->location = self->location + escape;
    }

    self->velocity =
        normal * 2 * (self->velocity.negative().dotProduct(normal)) +
        self->velocity;
    self->level->addObject(new Arrow(self->location, normal));
  }

  static void click(Object *me, input::MouseEvent ev) {
    Pinball *self = (Pinball *)me;
    self->stopped = !self->stopped;
  }

  Pinball(Point location, Vector velocity) {
    sprite = Sprite("sample/images/pinball.png", Point(7, 7), 1);
    this->location = location;
    this->velocity = velocity;
    stopped = true;

    createCollisionMask(sprite);
  }

  void init() {
    registerDrawEvent(&Pinball::draw, 30);
    registerStepEvent(&Pinball::step);
    registerCollisionEvent(&Pinball::collide);
    registerMouseEvent(&Pinball::click, sf::Event::MouseButtonPressed);
  }
};

class DemoLevel1 : public DemoLevel {
 public:
  DemoLevel1();

 protected:
  virtual void init();
};

class DemoLevel2 : public DemoLevel {
 public:
  DemoLevel2();

 protected:
  virtual void init();
};

class DemoLevel3 : public DemoLevel {
 public:
  DemoLevel3();

 protected:
  virtual void init();
};

class DemoLevel4 : public DemoLevel {
 public:
  DemoLevel4();

 protected:
  virtual void init();
};

class DemoLevel5 : public DemoLevel {
 public:
  DemoLevel5();

 protected:
  virtual void init();
};

class DemoLevel6 : public DemoLevel {
 public:
  DemoLevel6();

 protected:
  virtual void init();
};

class DemoLevel7 : public DemoLevel {
 public:
  DemoLevel7();

 protected:
  virtual void init();
};
