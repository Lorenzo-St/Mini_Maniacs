#pragma once

class ITime
{
public:
  ITime(ITime const& d) = delete;
  ITime& operator=(ITime const&) = delete;
  // If you are reading this, then you are attempting to use the wrong function; DON'T DO THIS
  void         deltaTime(float f) { dT = f; };
  float const& deltaTime(void) { return dT; };

  // If you are reading this, then you are attempting to use the wrong function; DON'T DO THIS
  void         runtime(float f) { rT = f; };
  float const& runtime(void) { return rT; };

  ITime() = default;
  ~ITime() = default;
private:
  float dT;
  float rT;
};

static ITime Times;
static ITime& Time = Times;