#pragma once
#include "Component.h"

class Stim : public Component
{
public:
  Stim() 
  {
    
  }
  Stim* Clone() { return nullptr; };
  void Read() { };
private:
  // -------------------------
  // Required Component things
  // -------------------------
  constexpr bool set() { setType(__CLASS_NAME__); return true; };
  const bool s = set();
  // -------------------------


};
