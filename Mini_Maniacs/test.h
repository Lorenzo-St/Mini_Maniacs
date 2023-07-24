#pragma once
#include "Component.h"


class Transform : public Component
{
public:
  Transform() 
  {

  }
  Transform* Clone() { return nullptr; };
  void Read() { };
private:
  constexpr bool set() { setType(__CLASS_NAME__); return true; };
};



