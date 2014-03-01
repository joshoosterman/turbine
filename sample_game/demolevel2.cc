// Copyright 2011

#include "sample_game/sample.h"
#include "math.h"

class Seizure : public GameObject {
 public:
  Sound sound;

  Seizure() { sound = Sound("sample/sounds/ding.wav"); }

  void init() { registerDrawEvent(&Seizure::draw, 10); }

  static void draw(Object *me) {
    Seizure *self = (Seizure *)me;
    static Point p = Point(100, 100);
    static Vector v = Vector(2, -2);
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        int r = rand() * 255;
        int g = rand() * 255;
        int b = rand() * 255;
        drawRectangle(
            BoundingBox(i * 100, (i + 1) * 100, j * 100, (j + 1) * 100),
            Color(r, g, b), false);
      }
    }

    if (p.x < 50 || p.x > 350) {
      v.x = -v.x;
      self->sound.play();
    } else if (p.y < 50 || p.y > 350) {
      v.y = -v.y;
      self->sound.play();
    }
    p = p + v;
    drawRectangle(BoundingBox(p.x - 50, p.x + 50, p.y - 50, p.y + 50),
                  Color(255, 0, 0, 200), false);
    drawRectangle(BoundingBox(p.x - 50, p.x + 50, p.y - 50, p.y + 50),
                  Color(255, 255, 255, 200), true);

    drawLine(Point(200, 0), p - Vector(0, 50), Color(255, 255, 255));
    drawLine(Point(200, 400), p + Vector(0, 50), Color(255, 255, 255));
    drawLine(Point(0, 200), p - Vector(50, 0), Color(255, 255, 255));
    drawLine(Point(400, 200), p + Vector(50, 0), Color(255, 255, 255));
  }
};

DemoLevel2::DemoLevel2() : DemoLevel("GFX Demo", 1, 0) {}

void DemoLevel2::init() { addObject(new Seizure()); }
