// Copyright 2011

#include "GameFramework.h"

#include <string>
#include <sstream>
#include <cstdio>
#include <math.h>

class PinballObject : public GameObject {
	double momentum;
	double elasticity; // 0..1, 1 for perfectly elastic collisions
};

class PinballBall : PinballObject {
	
};

class MyLevel : public Level{
public:
    MyLevel() {}

    void init()
    {
        addView(new View(Point(0, 0), Vector(400, 600)));
    }

    virtual ~MyLevel()
    {
    }
};

int main(int argc, char* args[])
{
    Game *game = new Game();
    game->getWindow()->setCaption("Pinball");
    game->getWindow()->setSize(400, 600);

    MyLevel *level = new MyLevel();
    level->init();
    game->run(level);

    return 0;
}
