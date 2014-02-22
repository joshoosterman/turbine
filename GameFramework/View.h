#ifndef _VIEW_H
#define _VIEW_H

#include "Classes.h"

namespace Turbine {

/// Represents a viewport of a level to be rendered to the screen
class View {
public:
	View(Geom::Point screenPosition, Geom::Vector size);
	~View();

	void setWindowPosition(Geom::Point p);
	void setSize(Geom::Vector s);
	void setPosition(Geom::Point p);
	void setRotation(float rotation);
	void setMovementStrategy(Extras::MovementStrategy *strat);

	Geom::Point getWindowPosition();
	Geom::Vector getSize();
	Geom::Vector getPosition();
	float getRotation();

	void setEnabled(bool enabled);

	void update();
	void activate();
	void finish();

	static View *getCurrentView();
	void setRenderTarget(sf::RenderWindow *renderTarget);
	sf::RenderImage *getRenderTarget();

	bool enabled;

private:
	Geom::Point screenPosition;
	Geom::Vector position;
	Geom::Vector size;
	float rotation;

	bool needsUpdate;

	Level *level;

	sf::RenderImage *surface;
	sf::RenderWindow *renderTarget;
	sf::View *view;
	static View *activeView;
	Extras::MovementStrategy *strat;
};

}

#endif
