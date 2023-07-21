#pragma once
#include "Object.hpp"
class System : Object
{
  virtual System* Clone(System const& s) = 0;

};