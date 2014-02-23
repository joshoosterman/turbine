#include "player.h"
#include <math.h>

Player::Player(CityLevel& level) : Runner(level) {
    sprRunning = Turbine::Graphics::Sprite("skyscrape/images/man2.png", Turbine::Geom::Vector(0, 0), 8);
    location =Turbine::Geom::Point(0, 200);
    xspeed = 5;
    size = Geom::Size(25, 50);
}

void Player::Step() {
    xspeed += 0.02;
    runspeed = (sqrtf(xspeed) / 15.f);
    Runner::Step();
}

bool Player::shouldJump() {
    return Turbine::Input::InputManager::getInstance()->keyDown(Turbine::Input::Up);
}
