#pragma once
#include "Object.hpp"
#include "EnumMacros.h"

CREATE_ENUM(ComponentType, Transform, Physics, Mesh);



class Component : Object
{
public:
  virtual void Awake();
  virtual void Init();
  virtual void Update();
  virtual void Exit();
private:
  Object* Parent;

};