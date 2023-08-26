#include <iostream>
#include <fstream>
#include <filesystem>
#define ESystem


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
  InputSystem::addBinding(Create, { SDLK_c });

  api.LoadFont((std::filesystem::current_path().string() + ".\\Assets\\Roboto-Regular.ttf").c_str());

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
  if (SelectedOBJ.OBJ.e->Parent() != nullptr) 
  {
    dynamic_cast<Entity*>(SelectedOBJ.OBJ.e->Parent())->AddChild(cloned);
  }
  EntitySystem::GetActive().AddEntity(cloned);
  SelectedOBJ.OBJ.e = cloned;
}

void EditorSystem::DeleteEntity() 
{
  if (SelectedOBJ.OBJ.e == nullptr)
    return;
  Selected = false;
  EntitySystem::GetActive().EditorGetAllActiveEntities().remove(SelectedOBJ.OBJ.e);
  dynamic_cast<Entity*>(SelectedOBJ.OBJ.e->Parent())->RemoveChild(SelectedOBJ.OBJ.e);
  delete SelectedOBJ.OBJ.e;
  SelectedOBJ.OBJ.e = nullptr;
}

void EditorSystem::DrawSelectedInfo(void) 
{
  glm::vec2 topCorner = { api.GetWindowWidth() * .75f, api.GetWindowHeight() * .05f };
  Transform* t = SelectedOBJ.OBJ.e->GetComponent<Transform>();
  std::string text = "Position: (" + std::to_string(t->GetPosition().x) + ", " + std::to_string(t->GetPosition().y) + ")";
  api.SetColor({ 255,255,255,255 });
  api.DrawText(text.c_str(), topCorner, 20);
  text = "Name: " + SelectedOBJ.OBJ.e->getName();
  topCorner.y -= 20;
  api.DrawText(text.c_str(), topCorner, 20);
  topCorner.y += 40;
  text = "Rotation: " + std::to_string(t->GetRotation());
  api.DrawText(text.c_str(), topCorner, 20);
  text = "Position: (" + std::to_string(t->GetScale().x) + ", " + std::to_string(t->GetScale().y) + ")";
  topCorner.y += 20;
  api.DrawText(text.c_str(), topCorner, 20);


}


void EditorSystem::DrawObjectMenu(void) 
{
  auto const& col = EntitySystem::GetActive().EditorGetAllPrototypeEntities().GetCollection();
   const int xCount = 10; 
   const int yCount = 3;
  
  glm::vec2 BGPos = { 0,0 };
  glm::vec2 BGScale = { api.GetWindowWidth() * .2f , api.GetWindowHeight() * .2f };
  api.SetColor({ 100, 100, 100, 175 });
  api.DrawRect(BGPos, BGScale);
  api.SetColor({ 255,255,255,255 });
  glm::vec2 startingPos = { BGPos.x - (BGScale.x*.4f), BGPos.y + (BGScale.y * .2f)};
  glm::vec2 BoxScale = BGScale / static_cast<float>(xCount + 1);
  api.DrawText("Objects",    api.ConvertToScreenSpace({ -30,  65 }), 50);
  int i = 0;
  for (auto const& e : col) 
  {
    api.DrawRect(startingPos + glm::vec2(BoxScale.x * (i % xCount), BoxScale.y * (i / yCount)), BoxScale);
  }
  


  api.DrawText("Create New", api.ConvertToScreenSpace({ -20, -55 }), 20);

}


void EditorSystem::PostUpdate(void) 
{
  if (inObjectMenu)
    DrawObjectMenu();
}


void EditorSystem::Update(void) 
{
  activeScene = Scene::getSceneSystem()->EditorGetActive();
  glm::vec2 location = {};
  glm::vec2 scale = {};
  glm::vec2 offset = glm::vec2(api.CameraPos().x, -api.CameraPos().y);
  glm::vec2 mousePos = api.ConvertToWorldSpace(glm::vec2( InputSystem::GetMouseX(), InputSystem::GetMouseY() )) ;
  

  if (InputSystem::isPressed(GridLock))
    GridLocked = true;
  else
    GridLocked = false;

  if (InputSystem::isTriggered(Create))
    inObjectMenu = !inObjectMenu;

  if (inObjectMenu)
    Selected = false;

  if (GridLocked) 
    mousePos = glm::roundEven(mousePos / 16.0f) * 16.0f;

  if (InputSystem::isTriggered(Save)) 
    SaveData();

  if (InputSystem::isTriggered(Delete) && Selected)
    DeleteEntity();

  if (InputSystem::isTriggered(Duplicate) && Selected && SelectedOBJ.type == entity) 
    DuplicateEntity();
  
  glm::vec2 MouseOff = mousePos - offset;

  if (Selected)
  {
    switch (SelectedOBJ.type)
    {
    case entity:
      if(SelectedOBJ.OBJ.e->Parent() != nullptr)
        SelectedOBJ.OBJ.e->GetComponent<Transform>()->SetLocalPosition(MouseOff);
      else
        SelectedOBJ.OBJ.e->GetComponent<Transform>()->SetPosition(MouseOff);
      scale = SelectedOBJ.OBJ.e->GetComponent<Transform>()->GetScale();
      break;

    default:
      break;
    }
    api.SetColor({ 255,255,255,255 });
    api.DrawRect(mousePos, scale * 1.1f);
  }
  if(SelectedOBJ.type == entity && SelectedOBJ.OBJ.e != nullptr)
    DrawSelectedInfo();
  


  if (!Selected && !inObjectMenu)
  {

    auto& entities = EntitySystem::GetActive().EditorGetAllActiveEntities().GetCollection();
    for (auto const& e : entities)
    {
      Transform* t = e->GetComponent<Transform>();
      glm::vec2 eScale = t->GetScale();
      glm::vec2 ePos = t->GetPosition();
      if (PointInRect(MouseOff, ePos, eScale))
      {
        api.SetColor({ 255, 255, 255, 255 });
        api.DrawRect(ePos + offset, eScale * 1.1f);
        if (InputSystem::MouseDown())
        {
          SelectedOBJ.OBJ.e = e;
          SelectedOBJ.type = entity;
          Selected = true;

        }

      }

    }

  }
  if (InputSystem::MouseDown() == false)
    Selected = false;

  //std::cout << Selected << "," << SelectedOBJ.OBJ.e << std::endl;
}

