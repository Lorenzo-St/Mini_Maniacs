#pragma once
#include "system.h"
#include <vector>
class Entity;

class EntitySystem : public System 
{
public:

  void Init(void);
  void Update(void);
  void Render(void);
  void Exit(void);

  Entity* CreateEntity(void);
  Entity* CreateEntity(const char* file);


private:
  std::vector<Entity*> entities;
};