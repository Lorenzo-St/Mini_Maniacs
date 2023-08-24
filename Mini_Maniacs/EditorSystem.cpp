#include <iostream>
#include <fstream>
#include <filesystem>

#include "EditorSystem.h"
#include "Entity.h"
#include "Transform.h"
#include "Backend.h"
#include "EntitySystem.h"
#include "Container.h"
#include "Scene.h"
#include "SceneSystem.h"

bool PointInRect(glm::vec2& point, glm::vec2& rectPos, glm::vec2& scale)
{

  if (std::abs(point.x - rectPos.x) >= scale.x / 2.0f) return false;
  if (std::abs(point.y - rectPos.y) >= scale.y / 2.0f) return false;
  return true;
}

EditorSystem::EditorSystem() 
  : activeScene(nullptr)
  , SelectedOBJ({})
{
  InputSystem::addBinding(Save, { SDLK_s });
  InputSystem::addBinding(GridLock, { SDLK_l });
  InputSystem::addBinding(Duplicate, { SDLK_d });
  InputSystem::addBinding(Delete, { SDLK_x });


}


void EditorSystem::SaveData()
{
  // Write out each prototype 
  auto& proto = EntitySystem::GetActive().EditorGetAllPrototypeEntities();
  for (auto& e : proto.GetCollection())
  {
    std::string path = std::filesystem::current_path().string() + ".\\Managed\\Entities\\" + e->getProto() + ".dat";
    std::ofstream s(path.c_str());
    if (s.good() == false || s.is_open() == false)
      throw std::runtime_error("bbaababa");

    e->Write(&s);
    s.flush();
    s.close();
    std::cout << "Wrote Out Prototype: " << e->getProto() << std::endl;
  }
  std::string path = std::filesystem::current_path().string() + ".\\Managed\\Scenes\\" + activeScene->name() + ".scn";
  std::ofstream s(path);
  if (s.good() == false || s.is_open() == false)
    throw std::runtime_error("bbaababa");
  activeScene->Write(&s);
  s.flush();
  s.close();
  std::cout << "Wrote Out Scene: " << activeScene->name() << std::endl;
  auto& live = EntitySystem::GetActive().EditorGetAllActiveEntities();
  for (auto& e : live.GetCollection())
  {
    if (e->isPrefabRoot())
    {
      EntitySystem::GetActive().WritePrefab(e);
      std::cout << "Wrote Out Prefab: " << e->getProto() << std::endl;
    }
  }
}

void EditorSystem::DuplicateEntity() 
{
  Entity* cloned = SelectedOBJ.OBJ.e->Clone();
  cloned->SetParent(SelectedOBJ.OBJ.e->Parent());
  EntitySystem::GetActive().AddEntity(cloned);
  SelectedOBJ.OBJ.e = cloned;
}

void EditorSystem::Update() 
{
  activeScene = Scene::getSceneSystem()->EditorGetActive();
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

  if (InputSystem::isTriggered(Save)) 
  {
    SaveData();
  }

  if (InputSystem::isTriggered(Duplicate) && Selected && SelectedOBJ.type == entity) 
  {
    DuplicateEntity();
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

