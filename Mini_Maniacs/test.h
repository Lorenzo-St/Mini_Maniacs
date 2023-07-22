#pragma once
#include "Component.h"


class Transform : public Component
{
public:
  Transform() 
  {

  }

private:
  constexpr bool set() { setType(__CLASS_NAME__); };
};



