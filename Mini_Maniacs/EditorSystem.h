#pragma once
#include "system.h"
#include "glm.hpp"
#include "sdl.h"
#ifdef ESystem
struct button
{
  bool selected;
  glm::vec2 pos;
  glm::vec2 scale;
  SDL_Color bgColor;
  SDL_Color selectedColor;

  SDL_Color textcolor;
  std::string const* text;
  int textSize;
  void drawButton(void);
  
};
#endif


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

#ifdef ESystem
  void UpdateButtons(std::vector<button>& but);
#endif
  Scene* activeScene = nullptr;
  
  bool Selected = false;
  bool GridLocked = false;
  bool inObjectMenu = false;

  SelectOBJ SelectedOBJ = {};
};

