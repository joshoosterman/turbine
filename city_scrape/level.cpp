#include "level.h"
#include "building.h"

using namespace Turbine;

class ParalaxBackground : public Turbine::SimpleGameObject {
private:
	Turbine::Graphics::Image image;
	float r;

public:
	ParalaxBackground(Turbine::Level &level, std::string path, float r) : Turbine::SimpleGameObject(level, 200.0f * (1.0f - r)) {
		this->image = Turbine::Graphics::Image(path);
		this->r = r;
	}

	void Draw() {
		float pX = View::getCurrentView()->getPosition().x;
		float pY = View::getCurrentView()->getPosition().y;
		float width = image.getBBox().right;
		float shiftBack = pX * r, shiftUp = pY * r;
		while(shiftBack > width) {
			shiftBack -= width;
		}

		Turbine::geom::Point point(pX - shiftBack, pY - shiftUp);

		for(int i = 0; i < 800 + width;  i += width) {
			image.draw(point + Turbine::geom::Vector(i, 0));
		}
	}
};

CityLevel::CityLevel() : Turbine::Level(), lines() {
    new ParalaxBackground(*this, "skyscrape/images/bg1.png", 0.0);
    new ParalaxBackground(*this, "skyscrape/images/bg2.png", 0.25);
    new ParalaxBackground(*this, "skyscrape/images/Para1.png", 0.5);

    for(int i = 0; i < 40; i++) {
        new Building(*this, i * 250 + 100);
    }

    Player *player = new Player(*this);

    Turbine::extras::MovementStrategy *strat =
            new Turbine::extras::ObjectTrackingMovementStrategy(*player, Turbine::geom::Vector(-400, -200));

    this->GetView(0).setSize(Turbine::geom::Vector(800, 400));
    this->GetView(0).setMovementStrategy(strat);
}

vector<Line*> CityLevel::getLines() {
    return lines;
}

void CityLevel::addLine(Line* line) {
    lines.push_back(line);
}
