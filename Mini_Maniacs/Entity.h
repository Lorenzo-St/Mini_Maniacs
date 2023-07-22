#pragma once
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "Object.hpp"
#include "EntitySystem.h"
#include "Component.h"
typedef struct sorter sorter;

class Entity : public Object 
{
public:
  void Awake(void);
  void Init(void);
  void Update(void);
  void Render(void);
  void Exit(void);

  void SetActive(bool b);

  void AddComponent(Component* c) 
  {
    components.push_back(c);
    std::sort(components.begin(), components.end(), sorter());
  }
  template<typename t>
  Component* GetComponent() 
  {
    
  };
  Entity(Object* p) { if (es == nullptr)throw std::runtime_error("You need to create at least 1 entity from the entity system"); SetParent(p); SetRoot(false); };
  Entity(EntitySystem* e) { SetParent(nullptr); es = e; SetRoot(true); };
  Entity(Entity const* e);
  Entity* Clone() { return new Entity(this); }
private:
  std::vector<Component*> components;
  static inline EntitySystem* es;
};