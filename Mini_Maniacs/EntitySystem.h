#pragma once
#include <vector>
#include <stdexcept>
#include "system.h"
#include "EntityContainer.h"
class Entity;

class EntitySystem : public System 
{
public:
  EntitySystem()
  {
    if (active != nullptr)
      throw std::runtime_error("Cannot create more than one EntitySystem. Kill the first one before making another");
    active = this;
  }
  
  void Init(void);
  void Update(void);
  void Render(void);
  void Exit(void);

  void AddEntity(Entity* e);

  Entity* CreateEntity(const char* file);
  Entity* CloneEntity(Entity* e);
  void DestroyAll(void);
  EntitySystem* GetActive(void) { return active; }

private:
  EntityContainer activeScene;
  EntityContainer prototypes;
  static EntitySystem* active;

};