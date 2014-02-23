#ifndef _EXCEPTIONS_H
#define _EXCEPTIONS_H

#include <string>
#include <stdexcept>

namespace Turbine {

/// Base class for all exceptions thrown by Turbine
class Exception {
private:
	std::string message;
public:
	Exception(std::string msg) : message(msg) {}
	~Exception() {}
	std::string getMessage() { 
		return message;
	}
};

/// Thrown when a method is called on an object that is not in
/// a level.
class ObjectNotInLevelException : public Exception
{
public:
	ObjectNotInLevelException(std::string msg) : Exception (msg) {}
};

/// Thrown when a resouce cannot be found at the specified
/// file path.
class ResourceNotFoundException : public Exception
{
public:
	ResourceNotFoundException(std::string msg) : Exception (msg) {}
};

/// Thrown during engine initialization if an unexpected
/// failure occurs.
class EngineInitException : public Exception
{
public:
	EngineInitException(std::string msg) : Exception (msg) {}
};

/// Thrown when a sound object fails to initialize
class SoundInitException : public Exception
{
public:
	SoundInitException(std::string msg) : Exception (msg) {}
};

/// Thrown when a sound object fails to play
class SoundFailedException : public Exception
{
public:
	SoundFailedException(std::string msg) : Exception (msg) {}
};
}

#endif
