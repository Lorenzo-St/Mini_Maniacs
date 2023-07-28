#include "Component.h"

class Physics : public Component
{
public:
  Physics()
  {

  }
  Physics* Clone() { return nullptr; };
  void Read(Stream* s) { };
  constexpr std::string GetName(void) { return __CLASS_NAME__; };
private:
  // -------------------------
  // Required Component things
  // -------------------------
  constexpr bool set() { setType(__CLASS_NAME__); return true; };
  const bool s = set();
  // -------------------------
  bool doGravity;


};
