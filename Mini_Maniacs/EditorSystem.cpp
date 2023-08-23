#include "EditorSystem.h"
#include "Entity.h"
#include "Transform.h"
#include "Backend.h"
#include "EntitySystem.h"
#include "Container.h"


bool PointInRect(glm::vec2& point, glm::vec2& rectPos, glm::vec2& scale)
{

  if (std::abs(point.x - rectPos.x) >= scale.x / 2.0f) return false;
  if (std::abs(point.y - rectPos.y) >= scale.y / 2.0f) return false;
  return true;
}

void EditorSystem::Update() 
{

  glm::vec2 location = {};
  glm::vec2 scale = {};
  glm::vec2 mousePos = api.ConvertToWorldSpace({ InputSystem::GetMouseX(), InputSystem::GetMouseY() });
  if (Selected)
  {
    switch (SelectedOBJ.type)
    {
    case entity:
      location = SelectedOBJ.OBJ.e->GetComponent<Transform>()->GetPosition();
      scale = SelectedOBJ.OBJ.e->GetComponent<Transform>()->GetScale();
      SelectedOBJ.OBJ.e->GetComponent<Transform>()->SetPosition(mousePos);
      break;

    default:
      break;
    }
        
    api.DrawRect(location, scale * 1.1f);
  }

  auto entities = EntitySystem::GetActive().EditorGetAllActiveEntities().GetCollection();
  std::cout << mousePos << std::endl;
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

