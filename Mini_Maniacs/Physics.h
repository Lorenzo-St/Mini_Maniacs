#include "Component.h"

class Physics : public Component
{
public:
  Physics()
  {

  }
  Physics* Clone() { return nullptr; };
  void Read(Stream* s) { };
private:
  // -------------------------
  // Required Component things
  // -------------------------
  constexpr bool set() { setType(__CLASS_NAME__); return true; };
  const bool s = set();
  // -------------------------


};
