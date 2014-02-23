#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include "Geom.h"
#include "InputManager.h"
#include "Exceptions.h"
#include "View.h"

using namespace Turbine::Geom;

namespace Turbine {
namespace Input {

InputManager *InputManager::instance = NULL;

InputManager* InputManager::getInstance()
{
	if(instance == NULL)
	{
		instance = new InputManager();
	}

	return instance;
}

// TODO(joshoosterman): This module is pretty much redundant with SFML2 providing
// static functions for checking keyboard & mouse state.

bool InputManager::keyDown(sf::Keyboard::Key key)
{
	//sf::Input *input = (sf::Input *) control;
	//return input->IsKeyDown((sf::Key::Code) key);
	return sf::Keyboard::isKeyPressed(key);
}

bool InputManager::keyPressed(sf::Keyboard::Key key)
{
	//todo
	//sf::Input *input = (sf::Input *) control;
	//return input->IsKeyDown((sf::Key::Code) key);
	return sf::Keyboard::isKeyPressed(key);
}

bool InputManager::keyReleased(sf::Keyboard::Key key)
{
	//todo
	//sf::Input *input = (sf::Input *) control;
	//return input->IsKeyDown((sf::Key::Code) key);
	return sf::Keyboard::isKeyPressed(key);
}

Point InputManager::mouseGetViewPosition(View* view)
{
	return mouseGetWindowPosition() + view->getPosition();
}

Point InputManager::mouseGetWindowPosition()
{
	// TODO(joshoosterman)
	//sf::Input *input = (sf::Input *) control;
	sf::Vector2i pos = sf::Mouse::getPosition();
	return Point(pos.x, pos.y);
}

bool InputManager::mouseGetLeftButtonDown()
{
	//sf::Input *input = (sf::Input *) control;
	//return input->IsMouseButtonDown(sf::Mouse::Left);
	return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

bool InputManager::mouseGetMiddleButtonDown()
{
	//sf::Input *input = (sf::Input *) control;
	//return input->IsMouseButtonDown(sf::Mouse::Middle);
	return sf::Mouse::isButtonPressed(sf::Mouse::Middle);
}

bool InputManager::mouseGetRightButtonDown()
{
	//sf::Input *input = (sf::Input *) control;
	//return input->IsMouseButtonDown(sf::Mouse::Right);
	return sf::Mouse::isButtonPressed(sf::Mouse::Right);
}
}
}
