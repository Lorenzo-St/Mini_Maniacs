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
  // Ctors and Dtors
  Entity(Object* p) {  SetParent(p); SetRoot(false); const_cast<EntitySystem&>(es).AddEntity(this); };
  Entity(Entity const* e);
  Entity* Clone() { return new Entity(this); }
  Entity() {};

  void Read(Stream* s);

  void Awake(void);
  void Init(void);
  void Update(void);
  void Render(void);
  void Exit(void);

  void SetName(std::string s) { name = std::string(s); }
  bool isNamed(std::string s) { return name == s; }

  void SetActive(bool b);

  void AddComponent(Component* c) 
  {
    components.push_back(c);
    std::sort(components.begin(), components.end(), sorter());
  }
  template<typename g>
  g* GetComponent() 
  {
    ComponentTypeEnum::ComponentType t = ComponentTypeEnum::typeToEnum<g>();
    size_t start = 0;
    size_t end = components.size();
    while(end > start)
    {
      size_t midPoint = (start + end) / 2;
      ComponentTypeEnum::ComponentType c = components[midPoint]->getType();
      if (c < t)
        start = midPoint;
      else if (c > t)
        end = midPoint;
      else if (c == t)
        return static_cast<g*>(components[midPoint]);
        
    }
    if (components[end]->getType() == t)
      return static_cast<g*>(components[end]);
    return nullptr;
  };

private:
  std::string name;
  std::vector<Component*> components;
  static const inline EntitySystem& es = EntitySystem::GetActive();
};