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

bool InputManager::keyDown(KeyCode key)
{
	sf::Input *input = (sf::Input *) control;
	return input->IsKeyDown((sf::Key::Code) key);
}

bool InputManager::keyPressed(KeyCode key)
{
	//todo
	sf::Input *input = (sf::Input *) control;
	return input->IsKeyDown((sf::Key::Code) key);
}

bool InputManager::keyReleased(KeyCode key)
{
	//todo
	sf::Input *input = (sf::Input *) control;
	return input->IsKeyDown((sf::Key::Code) key);
}

Point InputManager::mouseGetViewPosition(View* view)
{
	return mouseGetWindowPosition() + view->getPosition();
}

Point InputManager::mouseGetWindowPosition()
{
	sf::Input *input = (sf::Input *) control;
	return Point(input->GetMouseX(), input->GetMouseY());
}

bool InputManager::mouseGetLeftButtonDown()
{
	sf::Input *input = (sf::Input *) control;
	return input->IsMouseButtonDown(sf::Mouse::Left);
}

bool InputManager::mouseGetMiddleButtonDown()
{
	sf::Input *input = (sf::Input *) control;
	return input->IsMouseButtonDown(sf::Mouse::Middle);
}

bool InputManager::mouseGetRightButtonDown()
{
	sf::Input *input = (sf::Input *) control;
	return input->IsMouseButtonDown(sf::Mouse::Right);
}
}
}
