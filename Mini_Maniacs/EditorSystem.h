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
  EditorSystem();
  void Update();
  

private:
  EditorSystem* Clone() { return nullptr; };
  void SaveData(void);
  void DuplicateEntity(void);
  void DeleteEntity(void);

  Scene* activeScene = nullptr;
  bool Selected = false;
  bool GridLocked = false;
  SelectOBJ SelectedOBJ = {};
};

