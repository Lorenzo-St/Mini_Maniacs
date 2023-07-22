#include "Component.h"
bool operator< (Component const& lhs, Component const& rhs) 
{
  return lhs.type < rhs.type;
}
