#ifndef CONTROLMANAGER_H
#define CONTROLMANAGER_H

#include "Classes.h"
#include "KeyCodes.h"

typedef unsigned char uint8_t;
typedef uint8_t Uint8;

namespace Turbine {
namespace Input {

/// Provides functions to check input devices such as the keyboard and house
class InputManager {
public:
	static InputManager *getInstance();

	bool keyDown(KeyCode key);
	bool keyPressed(KeyCode key);
	bool keyReleased(KeyCode key);

	Geom::Point mouseGetWindowPosition();
	Geom::Point mouseGetViewPosition(View *view);
	bool mouseGetLeftButtonDown();
	bool mouseGetMiddleButtonDown();
	bool mouseGetRightButtonDown();

	static InputManager *instance;
	void *control;
};

struct KeyEvent {
	KeyEvent() {}
	KeyCode key;
};

struct MouseEvent {
	MouseEvent() {}
};

}
}

#endif //CONTROLMANAGER_H
