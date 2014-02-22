#ifndef _CLASSES_H
#define _CLASSES_H

/// Forward decls for all classes

namespace Turbine {
class Game;
class Window;
class Level;
class View;
class GameObject;
class Object;
class SimpleGameObject;
class ISpatialObjectSet;

class Exception;
class EngineInitException;
class ObjectNotInLevelException;
class ResourceNotFoundException;
class SoundFailedException;
class SoundInitException;


namespace Audio {
class Music;
class Sound;
}

namespace Extras {
class TerrainControl;
class Tile;
class TileControl;
class MovementStrategy;
class FixedPositionMovementStrategy;
class KeyboardMovementStrategy;
class ObjectTrackingMovementStrategy;
}

namespace Geom {
class Point;
typedef Point Size;
class Vector;
class BoundingBox;
}

namespace Graphics {
struct Color;
class Drawable;
class Font;
class Image;
class ImageUtil;
class Sprite;
}
namespace Input {
class InputManager;
struct KeyEvent;
struct MouseEvent;
}

namespace Internal {
class EventManager;
class RTreeSpatialObjectSet;
class BasicSpatialObjectSet;
template <class T> class ResourceCache;
template <class T> class SharedResource;
class SharedFont;
class SharedImage;
class SharedMusic;
class SharedSound;
class StepEventRegistration;
class CollisionEventRegistration;
class DrawEventRegistration;
class KeyboardEventRegistration;
class MouseEventRegistration;
}

namespace Physics {
class PhysicsObject;
}
}

namespace sf {
	class RenderWindow;
	class RenderImage;
	class Event;
	class View;
}

#endif _CLASSES_H