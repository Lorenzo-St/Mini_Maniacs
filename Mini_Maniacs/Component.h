#pragma once
#include "Object.hpp"
#include "EnumMacros.h"
#include <typeinfo>
#include <string>
CREATE_ENUM(ComponentType, Transform, PlayerController, Physics,  RectCollider, EllipCollider, Mesh, Collider,  Sprite, Animation,  Behavior, GameManager, StagePallet);

class Entity;

class Component : public Object
{
public:
  virtual void Read(Stream* s) = 0;
  virtual Component* Clone() = 0;
  virtual void Awake (void) { return; }
  virtual void Init  (void) { return; }
  virtual void Update(void) { return; }
  virtual void Render(void) { return; }
  virtual void Exit  (void) { return; }

  void SetParent(Entity* e) { Parent = e; }
  Entity* GetParent  (void) { return Parent; }

  ComponentTypeEnum::ComponentType getType(void) { return type; }
  
  virtual constexpr bool set() = 0;

  virtual void OnCollision(Entity* other) { return; };

  constexpr bool setType(std::string s) { name = s; type = ComponentTypeEnum::toEnum(s); return true; }
  
  static inline constexpr std::string className(const std::string& prettyFunction)
  {
    size_t colons = prettyFunction.find("::");
    if (colons == std::string::npos)
      return "::";
    size_t begin = prettyFunction.substr(0, colons).rfind(" ") + 1;
    size_t end = colons - begin;

    return prettyFunction.substr(begin, end);
  }



#define __CLASS_NAME__ className(__PRETTY_FUNCTION__)
  
  std::string const& GetName() { return name; }

  friend bool operator< (Component const& lhs, Component const& rhs);
private:
  Entity* Parent = nullptr;
  ComponentTypeEnum::ComponentType type = ComponentTypeEnum::reserved;
  std::string name;
};

typedef struct sorter
{
  bool operator() (Component const* lhs, Component const* rhs)
  {
    return *lhs < *rhs;
  }

}sorter;