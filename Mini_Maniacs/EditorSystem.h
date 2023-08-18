#pragma once
#include "system.h"

class Entity;

typedef union Select 
{
  Entity* e;
}Select;

class EditorSystem : public System 
{

public:


private:
  EditorSystem* Clone() { return nullptr; };
  bool Selected;
  
};