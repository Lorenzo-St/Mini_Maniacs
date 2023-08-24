#pragma once
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "Object.hpp"
#include "Component.h"
template<typename t>
class Container;

typedef struct sorter sorter;
class EntitySystem;
CREATE_ENUM_NOTYPE(Tags, Standard, Ground, Player, Enemy, Tile, Room, Game_Manager);


class Entity : public Object 
{
public:


  // Ctors and Dtors
  Entity(Object* p);
  Entity(Entity const* e);
  Entity();
  Entity* Clone() { return new Entity(this); }
  ~Entity() { for (auto& e : components) { delete e; } components.clear(); }
  
  void Read(Stream* s);
  void Awake(void);
  void Init(void);
  void Update(void);
  void Render(void);
  void Exit(void);

  void Write(std::ofstream* s);


  void OnCollison(Entity* other) { for (auto c : components) { c->OnCollision(other); } }

  void SetName(std::string s) { name = std::string(s); }
  bool isNamed(std::string s) { return name == s; }
  std::string const& getName() { return name; }

  void setProto(std::string s) { protoType = std::string(s); }
  bool isProto(std::string s) { return protoType == s; }
  std::string const& getProto() { return protoType; }

  bool isStatic(void);

  void AddChild(Entity* e) { Children.push_back(e); }
  void RemoveChild(Entity* e);
  std::vector<Entity*>& GetChildren() { return Children; }

  Container<Entity>& FindChildrenWithTag(Tags tag);

  void SetActive(bool b);

  void Tag(Tags t) { tag = t; }
  Tags Tag() { return tag; }


  void AddComponent(Component* c) 
  {
    components.push_back(c);
    c->SetParent(this);
    std::sort(components.begin(), components.end(), sorter());
  }
  template<typename g>
  g* GetComponent() 
  {
    std::string name = g().GetName();
    ComponentTypeEnum::ComponentType t = ComponentTypeEnum::toEnum(name);
    size_t start = 0;
    size_t end = components.size();
    while(end > start)
    {
      size_t midPoint = (start + end) / 2;
      ComponentTypeEnum::ComponentType c = components[midPoint]->getType();
      if (c < t)
        start = midPoint + 1;
      else if (c > t)
        end = midPoint - 1;
      else if (c == t)
        return static_cast<g*>(components[midPoint]);
        
    }
    if (end >= components.size())
      return nullptr;
    if (components[end]->getType() == t)
      return static_cast<g*>(components[end]);
    return nullptr;
  };
  template<typename g>
  g* GetComponent() const
  {
    std::string name = g().GetName();
    ComponentTypeEnum::ComponentType t = ComponentTypeEnum::toEnum(name);
    size_t start = 0;
    size_t end = components.size();
    while (end > start)
    {
      size_t midPoint = (start + end) / 2;
      ComponentTypeEnum::ComponentType c = components[midPoint]->getType();
      if (c < t)
        start = midPoint + 1;
      else if (c > t)
        end = midPoint - 1;
      else if (c == t)
        return static_cast<g*>(components[midPoint]);

    }    
    if (end >= components.size())
      return nullptr;
    if (components[end]->getType() == t)
      return static_cast<g*>(components[end]);
    return nullptr;
  };

  void isPrefabRoot(bool f) { PrefabRoot = f; };
  bool isPrefabRoot(void) { return PrefabRoot; }
 
  void isPrefabChild(bool f) { PrefabChild = f; };
  bool isPrefabChild(void) { return PrefabChild; }


private:
  std::string name;
  std::string protoType;
  std::vector<Component*> components;
  std::vector<Entity*> Children;
  bool PrefabRoot = false;
  bool PrefabChild = false;
  static const inline EntitySystem* es;
  Tags tag;
};
