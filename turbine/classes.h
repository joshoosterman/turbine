// Copyright 2011

#ifndef TURBINE_CLASSES_H_
#define TURBINE_CLASSES_H_

/// Forward decls for all classes
// TODO(joshoosterman): Don't do this... Encourages use of pointers
// over references.

namespace turbine {
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

namespace audio {
class Music;
class Sound;
}

namespace extras {
class TerrainControl;
class Tile;
class TileControl;
class MovementStrategy;
class FixedPositionMovementStrategy;
class KeyboardMovementStrategy;
class ObjectTrackingMovementStrategy;
}

namespace geom {
class Point;
typedef Point Size;
class Vector;
class BoundingBox;
}

namespace graphics {
struct Color;
class Drawable;
class Font;
class Image;
class ImageUtil;
class Sprite;
}
namespace input {
class InputManager;
struct KeyEvent;
struct MouseEvent;
}

namespace internal {
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
}  // namespace internal

namespace physics { class PhysicsObject; }
}  // namespace turbine

#endif  // TURBINE_CLASSES_H__
