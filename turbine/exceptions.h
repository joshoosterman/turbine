// Copyright 2011

#ifndef TURBINE_EXCEPTIONS_H_
#define TURBINE_EXCEPTIONS_H_

#include <string>
#include <stdexcept>

namespace turbine {

/// Base class for all exceptions thrown by turbine
class Exception {
 private:
  std::string message;

 public:
  explicit Exception(std::string msg) : message(msg) {}
  ~Exception() {}
  std::string getMessage() { return message; }
};

/// Thrown when a method is called on an object that is not in
/// a level.
class ObjectNotInLevelException : public Exception {
 public:
  explicit ObjectNotInLevelException(std::string msg) : Exception(msg) {}
};

/// Thrown when a resouce cannot be found at the specified
/// file path.
class ResourceNotFoundException : public Exception {
 public:
  explicit ResourceNotFoundException(std::string msg) : Exception(msg) {}
};

/// Thrown during engine initialization if an unexpected
/// failure occurs.
class EngineInitException : public Exception {
 public:
  explicit EngineInitException(std::string msg) : Exception(msg) {}
};

/// Thrown when a sound object fails to initialize
class SoundInitException : public Exception {
 public:
  explicit SoundInitException(std::string msg) : Exception(msg) {}
};

/// Thrown when a sound object fails to play
class SoundFailedException : public Exception {
 public:
  explicit SoundFailedException(std::string msg) : Exception(msg) {}
};

}  // namespace turbine

#endif  // TURBINE_EXCEPTIONS_H_
