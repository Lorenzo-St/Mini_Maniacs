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

  constexpr void addSystem(const System* s) { Systems.push_back(s); }

  errState GetErr(void);

private:
  Engine* Clone() { return nullptr; };
  std::vector<System const*> Systems;
  bool running = true;

};