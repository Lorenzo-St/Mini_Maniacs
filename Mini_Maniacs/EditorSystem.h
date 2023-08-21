#pragma once
#include "system.h"

class Entity;

typedef union Select 
{
  Entity* e;
}Select;

typedef enum type
{
  entity,
}type;

typedef struct SelectOBJ 
{
  type type;
  Select OBJ;
}SelectOBJ;


class EditorSystem : public System 
{

public:


private:
  EditorSystem* Clone() { return nullptr; };
  bool Selected;
  SelectOBJ SelectedOBJ;
};