#include "line.h"
#include "runner.h"

Line::Line() {
}

bool Line::doesPlayerSnap() {
    return false;
}

HorizontalLine::HorizontalLine(Turbine::Geom::Point start, int width) : start(start), width(width) {
}

void HorizontalLine::doRunnerStep(Runner& r) {
    r.doStep(this);
}

bool HorizontalLine::doCollisionTest(Turbine::Geom::Point start, Turbine::Geom::Point& end, Turbine::Geom::Size size) {
    if ((start.y + size.y> this->start.y) || (end.y + size.y < this->start.y) || (end.y <= start.y))
        return false;
    
    double coll_y = this->start.y - (start.y + size.y);
    double x_dy = (end.x - start.x) / (end.y - start.y);
    double next_x = start.x + coll_y * x_dy;
    
    Geom::Point new_location(next_x, this->start.y - size.y);
    if (!onLine(new_location, size))
        return false;

    end = new_location;
    return true;
}

bool HorizontalLine::doesPlayerSnap() {
    return true;
}

bool HorizontalLine::onLine(Geom::Point start, Geom::Size size) {
    if (start.x + size.x < this->start.x)
        return false;
    if (start.x > this->start.x + this->width)
        return false;
    return true;
}
