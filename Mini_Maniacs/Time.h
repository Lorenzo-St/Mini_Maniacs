#pragma once

class STime
{
public:
  STime(STime const& d) = delete;
  STime& operator=(STime const&) = delete;
  // If you are reading this, then you are attempting to use the wrong function; DON'T DO THIS
  void          deltaTime(float f) { dT = f; };
  float const& deltaTime(void) { return dT; };

  // If you are reading this, then you are attempting to use the wrong function; DON'T DO THIS
  void          runtime(float f) { rT = f; };
  float const& runtime(void) { return rT; };

  STime() = default;
  ~STime() = default;
private:
  float dT;
  float rT;
};

extern STime Time;
