#pragma once
#include "system.h"
#include "glm.hpp"
#include "sdl.h"



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
  
  void PostUpdate();

private:
  EditorSystem* Clone() { return nullptr; };
  void SaveData(void);
  void DuplicateEntity(void);
  void DeleteEntity(void);
  void DrawSelectedInfo(void);
  void DrawObjectMenu(void);
  void DrawParentMenu(void);

  Scene* activeScene = nullptr;
  
  bool Selected = false;
  bool GridLocked = false;
  bool inObjectMenu = false;
  bool inParentMenu = false;


  SelectOBJ SelectedOBJ = {};
};

