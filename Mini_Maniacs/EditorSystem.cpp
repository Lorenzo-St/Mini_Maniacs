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


bool PointInRect(glm::vec2 const& point, glm::vec2 const& rectPos, glm::vec2 const& scale)
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
  InputSystem::addBinding(Parents, { SDLK_p });
  InputSystem::addBinding(RemoveParent, { SDLK_o });
  InputSystem::addBinding(Naming, { SDLK_n });
  
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
  Entity* e = dynamic_cast<Entity*>(SelectedOBJ.OBJ.e->Parent());
  
  if(e != nullptr)
    e->RemoveChild(SelectedOBJ.OBJ.e);

  delete SelectedOBJ.OBJ.e;
  SelectedOBJ.OBJ.e = nullptr;
}

void EditorSystem::DrawSelectedInfo(void) 
{
  glm::vec2 topCorner = { api.GetWindowWidth() * .75f, api.GetWindowHeight() * .05f };
  glm::vec2 scale = { api.GetWindowWidth() * .14f, api.GetWindowHeight() * .5f };
  glm::vec2 pos = { api.GetWindowWidth() * .5f * .3f, 0 };
  api.SetColor({ 50, 50, 50, 200 });
  api.DrawRect(pos, scale);
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

void EditorSystem::DrawParentMenu(void)
{
  auto const& col = EntitySystem::GetActive().EditorGetAllActiveEntities().GetCollection();
  static const int xCount = 10;
  static const int yCount = 4;
  static int row = 0;
  
  glm::vec2 BGPos = { 0,0 };
  glm::vec2 BGScale = { api.GetWindowWidth() * .2f , api.GetWindowHeight() * .2f };
  
  api.SetColor({ 100, 100, 100, 175 });
  api.DrawRect(BGPos, BGScale);
  api.SetColor({ 255,255,255,255 });
  row -= InputSystem::WheelY();
  if (row < 1)
    row = 1;

  glm::vec2 startingPos = { BGPos.x - (BGScale.x * .41f), BGPos.y + (BGScale.y * .25f) };
  glm::vec2 BoxScale = { BGScale.x / static_cast<float>(xCount + 2), 0 };
  BoxScale.y = BoxScale.x;
  
  api.DrawText("Select Object to Parent Object to", api.ConvertToScreenSpace({ -50,  65 }), 50);

  glm::vec2 mousePos = api.ConvertToWorldSpace(glm::vec2(InputSystem::GetMouseX(), InputSystem::GetMouseY()));
  int i = (row - 1) * xCount;
  int j = 0;
  for (int k = 0; k < col.size(); ++k)
  {
    if (k < i)
      continue;
    Entity* e = col[k];

    if (i / xCount >= yCount + (row - 1))
      break;

    glm::vec2 pos = startingPos + glm::vec2(BoxScale.x * (j % (xCount)) * 1.1f, -BoxScale.y * (j / xCount) * 1.1f);
    if (PointInRect(mousePos, pos, BoxScale))
    {

      api.SetColor({ 255, 255, 255, 255 });
      if (InputSystem::MouseDown())
      {
        SelectedOBJ.OBJ.e->SetParent(e);
        inParentMenu = false;
        if (e->isPrefabRoot())
          SelectedOBJ.OBJ.e->isPrefabChild(true);
        return;
      }
    }
    else
      api.SetColor({ 155, 155, 155, 255 });
    api.DrawRect(pos, BoxScale);
    
    api.SetColor({ 0, 0, 0, 255 });
    api.DrawTextCentered(e->getName().c_str(), api.ConvertToScreenSpace(pos), 15);

    //api.DrawText(std::to_string(i).c_str(), api.ConvertToScreenSpace(pos + glm::vec2(-BoxScale.x / 3.0f, BoxScale.y / 2.0f)), 15);
    //api.DrawText(std::to_string(j).c_str(), api.ConvertToScreenSpace(pos + glm::vec2(BoxScale.x / 3.0f, BoxScale.y / 2.0f)), 15);

    ++i, ++j;
  }


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
  glm::vec2 startingPos = { BGPos.x - (BGScale.x*.4f), BGPos.y + (BGScale.y * .25f)};
  glm::vec2 BoxScale = { BGScale.x / static_cast<float>(xCount + 1), 0};
  BoxScale.y = BoxScale.x;
  api.DrawText("Objects",    api.ConvertToScreenSpace({ -30,  65 }), 50);
  int i = 0;
  glm::vec2 mousePos = api.ConvertToWorldSpace(glm::vec2(InputSystem::GetMouseX(), InputSystem::GetMouseY()));
  
  for (auto const& e : col) 
  {

    glm::vec2 pos = startingPos + glm::vec2(BoxScale.x * (i % xCount) * 1.1f, BoxScale.y * (i / xCount) * 1.1f);
    if (PointInRect(mousePos, pos, BoxScale)) 
    {
    
      api.SetColor({ 255, 255, 255, 255 });
      if (InputSystem::MouseDown())
      {
        Entity* el = EntitySystem::GetActive().CreateEntity(e->getProto().c_str());
        SelectedOBJ.type = entity;
        Selected = true;
        SelectedOBJ.OBJ.e = el;
        inObjectMenu = false;
        return;
      }
    }
    else
      api.SetColor({ 155, 155, 155, 255 });
    api.DrawRect(pos, BoxScale);
    api.SetColor({ 10, 10, 10, 255 });

    api.DrawTextCentered(e->getName().c_str(), api.ConvertToScreenSpace(pos + glm::vec2(0.0f, -BoxScale.y / 3.5f)), 15);
    ++i;
  }
  

  api.SetColor({ 255, 255, 255, 255 });
  glm::vec2 pos = { 0 , -60 };
  glm::vec2 scale = { 60, 20 };
  if (PointInRect(mousePos, pos, scale))
  {
    api.SetColor({ 255, 255, 255, 255 });
    if (InputSystem::MouseDown()) 
    {
      Selected = true;
      SelectedOBJ.type = entity;
      SelectedOBJ.OBJ.e = new Entity;
      Entity*& e = SelectedOBJ.OBJ.e;
      e->AddComponent(new Transform());
      e->setProto("New Object");
      e->SetName("New Object");
      inObjectMenu = false;

    }
  }
  else
    api.SetColor({ 175, 175, 175, 255 });
  api.DrawRect(pos, scale);
  api.SetColor({ 10, 10, 10, 255 });
  api.DrawTextCentered("Create New", api.ConvertToScreenSpace(pos), 20);


}

void EditorSystem::NameMenu(void) 
{
  glm::vec2 BGPos = { 0,0 };
  glm::vec2 BGScale = { api.GetWindowWidth() * .2f , api.GetWindowHeight() * .2f };
  api.SetColor({ 100, 100, 100, 175 });
  api.DrawRect(BGPos, BGScale);
  api.SetColor({ 10, 10, 10, 255 });

  api.DrawTextCentered("Change Selected Name", api.ConvertToScreenSpace({ 0, 60 }), 40);
  std::string& s = const_cast<std::string&>(SelectedOBJ.OBJ.e->getName());


}


void EditorSystem::PostUpdate(void) 
{
  if (SelectedOBJ.type == entity && SelectedOBJ.OBJ.e != nullptr)
    DrawSelectedInfo();

  if (inObjectMenu)
    DrawObjectMenu();

  if (inParentMenu)
    DrawParentMenu();

  if (inNameMenu)
    NameMenu();
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

  if (Selected && SelectedOBJ.type == entity) 
  {
  
  if (InputSystem::isTriggered(Parents))
    inParentMenu = !inParentMenu;

  if (InputSystem::isTriggered(Naming))
    inNameMenu = !inNameMenu;

  if (InputSystem::isTriggered(RemoveParent))
  {
    SelectedOBJ.OBJ.e->SetParent(nullptr);
    SelectedOBJ.OBJ.e->isPrefabChild(false);
    SelectedOBJ.OBJ.e->isPrefabRoot(false);
  }

  }

  if (inObjectMenu)
    Selected = false;

  if (GridLocked) 
    mousePos = glm::roundEven(mousePos / 16.0f) * 16.0f;

  if (InputSystem::isTriggered(Save)) 
    SaveData();

  if (InputSystem::isTriggered(Delete) && Selected)
    DeleteEntity();

  if (InputSystem::isTriggered(Duplicate) && Selected && SelectedOBJ.type == entity && !inNameMenu) 
    DuplicateEntity();
  
  glm::vec2 MouseOff = mousePos - offset;

  if (Selected && !inParentMenu)
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



  if (!Selected && !inObjectMenu && !inParentMenu)
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
  if (InputSystem::MouseDown() == false && !inParentMenu)
    Selected = false;

  //std::cout << Selected << "," << SelectedOBJ.OBJ.e << std::endl;
}

