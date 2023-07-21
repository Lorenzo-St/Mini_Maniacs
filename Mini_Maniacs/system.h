#pragma once
#include "Object.hpp"
class System : public Object
{
public:
  virtual System* Clone() = 0;
  System() = default;
  bool operator==(const System& other) const = delete;
};