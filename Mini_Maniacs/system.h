#pragma once
#include "Object.hpp"
class System : public Object
{
public:
  virtual System* Clone() = 0;
  virtual void PostUpdate(void) { return; }
  System() = default;
  bool operator==(const System& other) const = delete;
};