#pragma once

class STime
{
public:
  STime(STime const& d) = delete;
  STime& operator=(STime const&) = delete;
  // If you are reading this, then you are attempting to use the wrong function; DON'T DO THIS
  void          deltaTime(double f) { dT = f; };
  double const& deltaTime(void) { return dT; };

  // If you are reading this, then you are attempting to use the wrong function; DON'T DO THIS
  void          runtime(double f) { rT = f; };
  double const& runtime(void) { return rT; };

  STime() = default;
  ~STime() = default;
private:
  double dT;
  double rT;
};

extern STime Time;
