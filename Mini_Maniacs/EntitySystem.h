#pragma once
#include <vector>
#include <stdexcept>
#include "system.h"
#include "Entity.h"
#include "Container.h"
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
  //void AddEntity(Entity* e) const;

  Entity* CreateEntity(const char* file);
  Entity* CreatePrefab(const char* file);
  Entity* CloneEntity(Entity* e);

  Container<Entity>& FindAllWithTag(Tags tag);

  Entity* FindWithName(const char* name);
  Entity* FindWithTag( Tags tag);

#ifdef EDITOR
  Container<Entity>& EditorGetAllActiveEntities() { return activeScene; }
  Container<Entity>& EditorGetAllPrototypeEntities() { return activeScene; };
#endif

  void DestroyAll(void);
  static constexpr EntitySystem& GetActive(void) { return *active; }

private:
  EntitySystem* Clone() { throw std::runtime_error("no"); }
  Container<Entity> activeScene;
  Container<Entity> prototypes;
  Container<Entity> searchResult;
  static inline EntitySystem* active;

};