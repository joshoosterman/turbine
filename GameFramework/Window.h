#ifndef _WINDOW_H
#define _WINDOW_H

#include <string>

#include "Classes.h"
#include "Geom.h"

namespace Turbine {
	
class Window {
public:
	Window(std::string caption, Geom::Size size);
	~Window();

	/// Sets the caption of the game window.
	void setCaption(std::string caption);

	/// Sets the size of the game window, in pixels.
	void setSize(Geom::Size size);

	/// Sets the game to fullscreen or windowed mode.
	void setFullScreen(bool fullScreen);

	/// Sets the visibility of the cursor, when positioned over the game window.
	void setCursorVisible(bool cursorVisible);

	/// Gets the SFML render window object, useful for rendering and retrieving
	/// events.
	sf::RenderWindow &getRenderTarget();
private:
	void initWindow();

	Geom::Size size;
	std::string caption;
	sf::RenderWindow *rWindow;
};

}

#endif