// Copyright 2011

#ifndef TURBINE_OBJECT_H_
#define TURBINE_OBJECT_H_

#include "SFML/Window/Event.hpp"

#include "turbine/classes.h"
#include "turbine/input_manager.h"
#include "turbine/graphics.h"

namespace turbine {

// Event callbacks
typedef void (*DrawCallback)(Object *);
typedef void (*StepCallback)(Object *);
typedef void (*CollisionCallback)(GameObject *, GameObject *, geom::Vector);
typedef void (*MouseCallback)(Object *, input::MouseEvent);
typedef void (*KeyboardCallback)(Object *, input::KeyEvent);

class Object {
 private:
  // TODO(joshoosterman): friend Level;
  bool hasInit;

 protected:
  Object();

  void registerBeginStepEvent(StepCallback);
  void registerStepEvent(StepCallback);
  void registerEndStepEvent(StepCallback);
  void registerDrawEvent(DrawCallback, int depth);
  void registerGlobalMouseEvent(MouseCallback, sf::Event::EventType);
  void registerKeyboardEvent(KeyboardCallback, sf::Event::EventType);

  void unregisterBeginStepEvent(StepCallback);
  void unregisterStepEvent(StepCallback);
  void unregisterEndStepEvent(StepCallback);
  void unregisterDrawEvent(DrawCallback, int depth);
  void unregisterGlobalMouseEvent(MouseCallback, sf::Event::EventType);
  void unregisterKeyboardEvent(KeyboardCallback, sf::Event::EventType);

  void checkInLevel();

 public:
  Level *level;
  virtual ~Object() {}
  virtual void destroy();
  virtual void init() = 0;
};

class GameObject : public Object {
 private:
  graphics::Image mask;

 protected:
  virtual void registerCollisionEvent(CollisionCallback);
  void registerMouseEvent(MouseCallback, sf::Event::EventType);
  virtual void unregisterCollisionEvent(CollisionCallback);
  void unregisterMouseEvent(MouseCallback, sf::Event::EventType);

  void createCollisionMask(graphics::Image image);
  void createCollisionMask(graphics::Sprite sprite);
  graphics::Image getCollisionMask();

  geom::BoundingBox bbox;
  geom::Point location;

 public:
  GameObject();
  virtual ~GameObject() {}

  geom::BoundingBox getBoundingBox() const;
  geom::Point getLocation() const;

  void drawDebugInfo(bool showmask = false);
  bool collides(GameObject *other) const;
  bool collides(GameObject *other, geom::Vector *normal,
                geom::Point *collisionPoint) const;
  bool collides(const geom::Point &p) const;
  virtual void init() = 0;
};

class SimpleGameObject : public GameObject {
 private:
  int depth;
  static void _draw(Object *obj);
  static void _step(Object *obj);

 public:
  explicit SimpleGameObject(int depth);

  virtual void setup();
  virtual void draw();
  virtual void step();
  void init();
};

}  // namespace turbine

#endif  // TURBINE_OBJECT_H_
