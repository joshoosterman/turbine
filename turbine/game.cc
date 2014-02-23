#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include <iostream>
#include <sstream>

#include "turbine/event_manager.h"
#include "turbine/exceptions.h"
#include "turbine/game.h"
#include "turbine/input_manager.h"
#include "turbine/level.h"
#include "turbine/window.h"

using namespace Turbine::Geom;
using namespace Turbine::Input;
using namespace Turbine::Internal;

namespace Turbine {

Game *Game::inst = NULL;

Game::Game(Window &window)
{
	this->window = &window;
	inst = this;
}

Game::~Game()
{
}

Game &Game::getInstance()
{
	return *inst;
}

void Game::run(Level &level)
{
	setActiveLevel(level);

	int targetFPS = 50;
	float secondsPerFrame = 1.0f / ((float) targetFPS);
	sf::Clock AITimer;

	while(window->getRenderTarget().isOpen())
	{
		Level* level = activeLevel;
		AITimer.restart();

		sf::Event ev;
		while(window->getRenderTarget().pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed) {
				return;
			}
			//TODO: Find a better way to filter for mouse/key events
			else if(ev.type == sf::Event::MouseButtonPressed || ev.type == sf::Event::MouseButtonReleased) {
				 level->getEventManager()->performMouseEvents(ev);
			} else if(ev.type == sf::Event::KeyPressed || ev.type == sf::Event::KeyReleased) {
				 level->getEventManager()->performKeyboardEvents(ev);
			}
		}
		window->getRenderTarget().clear(sf::Color(0, 0, 0, 255));

		level->frame();

		window->getRenderTarget().display();
		float secondsPassed = AITimer.getElapsedTime().asSeconds();
		float left = secondsPerFrame - secondsPassed;

		if(left > 0) {
			sf::sleep(sf::seconds(left));
		}
	}
}

void Game::setActiveLevel(Level &level)
{
	activeLevel = &level;
}

/// Sets the desired frame rate for the game
void Game::setTargetFrameRate(int targetFrameRate)
{
	this->fps = targetFrameRate;
}

/// Gets the actual average number of frames rendered per second.
float Game::getFrameRate()
{
	return this->frameTime;
}

void Game::setBaseResourcePath(std::string path)
{
	this->resourcePath = path;
}

std::string Game::getResourcePath(std::string path)
{
	if(resourcePath.length() > 0) {
		std::stringstream out;
		out << resourcePath << "/" << path;
		return out.str();
	}
	return path;
}

Window &Game::getWindow()
{
	return *window;
}

Window::Window(std::string caption, Geom::Size size)
{
	this->rWindow = NULL;
	this->size = size;
	this->caption = caption;

	initWindow();
}

Window::~Window()
{
	delete rWindow;
}

void Window::setSize(Geom::Size size)
{
	this->size = size;
	initWindow();
}

void Window::initWindow()
{
	if(rWindow != NULL)
	{
		rWindow->close();
		delete rWindow;
		rWindow = NULL;
	}

	sf::ContextSettings settings;
	rWindow = new sf::RenderWindow(sf::VideoMode(size.x, size.y, 32), caption, sf::Style::Close, settings);
	if(rWindow == NULL)
	{
		throw EngineInitException("Could not create screen surface");
	}
	//InputManager::getInstance()->control = (void *) &rWindow->getInput();
}

void Window::setFullScreen(bool fullScreen)
{
}

/// Sets the visibility of the cursor, when positioned over the game window.
void Window::setCursorVisible(bool cursorVisible)
{
	this->rWindow->setMouseCursorVisible(cursorVisible);
	//this->rWindow->showMouseCursor(cursorVisible);
}

sf::RenderWindow &Window::getRenderTarget()
{
	return *(this->rWindow);
}

}
