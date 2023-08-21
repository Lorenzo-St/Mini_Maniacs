#pragma once
#include "system.h"

class Entity;
class Scene;

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
  
  void Update();
  

private:
  EditorSystem* Clone() { return nullptr; };
  
  Scene* activeScene;
  bool Selected;
  
  SelectOBJ SelectedOBJ;
};
