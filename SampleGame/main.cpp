#include "Sample.h"

int main(int argc, char* args[]) {
	Window window("GameFramework Feature Samples", Geom::Size(400, 400));
	Game game(window);
	DemoLevel1 level1;
	DemoLevel2 level2;
	DemoLevel3 level3;
	DemoLevel4 level4;
	DemoLevel5 level5;
	DemoLevel6 level6;
	DemoLevel7 level7;

	level1.next = &level2;
	level2.previous = &level1;
	level2.next = &level3;
	level3.previous = &level2;
	level3.next = &level4;
	level4.previous = &level3;
	level4.next = &level5;
	level5.previous = &level4;
	level5.next = &level6;
	level6.previous = &level5;
	level6.next = &level7;
	level7.previous = &level6;
	level7.next = &level1;
	level1.previous = &level7;

	level1.doInit();
    	game.run(level1);

    return 0;
}

