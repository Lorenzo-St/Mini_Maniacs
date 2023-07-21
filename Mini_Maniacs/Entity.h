#pragma once
#include <vector>
#include "Object.hpp"
#include "Component.h"
class Entity : public Object 
{
public:
  void Awake(void);
  void Init(void);
  void Update();
  void Exit();

private:
  Object* parent;
  std::vector<Component*> components;
};