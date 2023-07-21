#pragma once
#include <vector>
#include "system.h"
#include "Backend.h"
typedef long errState;

class Engine : Object
{
public:
  void Init(void);
  void Update(void);
  void Exit(void);

  void addSystem(System* s) { Systems.push_back(s); }

  errState GetErr(void);

private:
  Engine* Clone() {};
  std::vector<System*> Systems;
  RenderFront api;
};