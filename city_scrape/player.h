#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "cityscrape.h"
#include "runner.h"

class Player : public Runner {
public:
    Player(CityLevel& level);
    virtual void Step();
    bool shouldJump();
};

#endif
