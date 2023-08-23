#include "EditorSystem.h"
#include "Entity.h"
#include "Transform.h"
#include "Backend.h"
#include "EntitySystem.h"
#include "Container.h"
#include <iostream>
#include <fstream>
#include <filesystem>
bool PointInRect(glm::vec2& point, glm::vec2& rectPos, glm::vec2& scale)
{

  if (std::abs(point.x - rectPos.x) >= scale.x / 2.0f) return false;
  if (std::abs(point.y - rectPos.y) >= scale.y / 2.0f) return false;
  return true;
}

EditorSystem::EditorSystem() 
{
  InputSystem::addBinding(Save, { SDLK_s });
  InputSystem::addBinding(GridLock, { SDLK_l });

}


void EditorSystem::Update() 
{

  glm::vec2 location = {};
  glm::vec2 scale = {};
  glm::vec2 mousePos = api.ConvertToWorldSpace({ InputSystem::GetMouseX(), InputSystem::GetMouseY() });
  if (InputSystem::isPressed(GridLock))
    GridLocked = true;
  else
    GridLocked = false;

  if (GridLocked) 
  {
    mousePos = glm::roundEven(mousePos / 16.0f) * 16.0f;
  }

  if (InputSystem::isPressed(Save)) 
  {
    auto& proto = EntitySystem::GetActive().EditorGetAllPrototypeEntities();
    
    Entity* a = proto.GetCollection()[0];
    std::string path = std::filesystem::current_path().string() + "Entities\\" + a->getProto() + ".dat";
    std::ofstream s(path.c_str());
    if (s.good() == false || s.is_open() == false)
      throw std::runtime_error("bbaababa");

    a->Write(&s);
    s.flush();
    s.close();
  }

  if (Selected)
  {
    switch (SelectedOBJ.type)
    {
    case entity:
      if(SelectedOBJ.OBJ.e->Parent() != nullptr)
        SelectedOBJ.OBJ.e->GetComponent<Transform>()->SetLocalPosition(mousePos);
      else
        SelectedOBJ.OBJ.e->GetComponent<Transform>()->SetPosition(mousePos);
      scale = SelectedOBJ.OBJ.e->GetComponent<Transform>()->GetScale();
      break;

    default:
      break;
    }
        
    api.DrawRect(mousePos, scale * 1.1f);
  }

  auto& entities = EntitySystem::GetActive().EditorGetAllActiveEntities().GetCollection();
  for (auto const& e : entities) 
  {
    Transform* t = e->GetComponent<Transform>();
    glm::vec2 eScale = t->GetScale();
    glm::vec2 ePos = t->GetPosition();
    if (PointInRect(mousePos, ePos, eScale) )
    {
      if (InputSystem::MouseDown()) 
      {
        SelectedOBJ.OBJ.e = e;
        SelectedOBJ.type = entity;
        Selected = true;

      }
    }
  
  }

  if (InputSystem::MouseDown() == false)
    Selected = false;

  //std::cout << Selected << "," << SelectedOBJ.OBJ.e << std::endl;
}

