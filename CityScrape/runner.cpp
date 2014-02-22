#include "runner.h"
#include "level.h"

#define GRAVITY 0.5

using namespace Turbine;

Runner::Runner(CityLevel& level) : SimpleGameObject(level, 0), xspeed(0.f), yspeed(0.f),
        frame(0.f), standingOn(NULL), level(level), jump_power(6) {
}

void Runner::Step() {
    if (standingOn) {
        standingOn->doRunnerStep(*this);
    }
    else {
        yspeed += GRAVITY;
        if (shouldJump() && yspeed < 0)
            yspeed -= 0.35;
        
        Geom::Point new_location = location;
        new_location.x += xspeed;
        new_location.y += yspeed;
        
        moveTo(new_location);
    }

    frame -= runspeed;
}

void Runner::Draw() {
	sprRunning.setFrame(frame);
	sprRunning.draw(location);
}

void Runner::applyX() {
    location.x += xspeed;
}

void Runner::applyY() {
    location.y += yspeed;
}

bool Runner::moveTo(Geom::Point new_location) {
        bool hit = false;
        vector<Line*> lines = level.getLines();
        vector<Line*>::iterator it;
        for (it = lines.begin(); it != lines.end(); it++) {
            if ((*it)->doCollisionTest(location, new_location, size)) {
                hit = true;
                if ((*it)->doesPlayerSnap())
                    standingOn = *it;
            }
        }
        location = new_location;
        return hit;
}

void Runner::doStep(HorizontalLine* line) {
    moveTo(Geom::Point(location.x + xspeed, location.y));
    if (shouldJump()){
		yspeed = -jump_power;
        standingOn = NULL;
        return;
    }
    if (!line->onLine(location, size)) {
        yspeed = 0;
        standingOn = NULL;
    }
}
