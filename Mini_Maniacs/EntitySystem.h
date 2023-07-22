#pragma once
#include <vector>
#include <stdexcept>
#include "system.h"
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

  Entity* CreateEntity(void);
  Entity* CreateEntity(const char* file);

  void DestroyAll(void);
  EntitySystem* GetActive(void) { return active; }

private:
  std::vector<Entity*> entities;
  static EntitySystem* active;
};