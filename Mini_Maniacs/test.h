#pragma once
#include "Component.h"


class Transform : public Component
{
public:
  Transform() 
  {
    std::string s = __func__;
    if (s.find("::") != std::string::npos)
     s = s.replace(s.begin(), s.begin() + s.find("::"), "");
    Component::setType(s);
  }

private:
  constexpr bool set() { setType(__CLASS_NAME__); };
};



