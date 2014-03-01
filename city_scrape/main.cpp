#include "Turbine.h"

#include <string>
#include <sstream>
#include <cstdio>
#include <math.h>
#include <typeinfo>

#define GRAVITY 0.4f

#include "player.h"
#include "level.h"

using namespace Turbine;
using namespace Turbine::geom;
using namespace Turbine::Input;
using namespace Turbine::Graphics;
using namespace Turbine::Audio;
using namespace Turbine::Physics;

int main(int argc, char* args[])
{
	Game game;
	game.SetSize(Turbine::geom::Size(800, 400));
    game.SetCaption("SkyScrape");

	CityLevel level;
    game.Run(level);

    return 0;
}
