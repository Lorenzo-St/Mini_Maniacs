#pragma once
#include "system.h"

class Scene;

class SceneSystem : public System
{
public:

  void Init(void);
  void Update(void);
  void Exit(void);

  void SetNextScene(Scene* s);

private:
  Scene* Active = nullptr;
  Scene* nextScene = nullptr;
  bool restarting = false;
  bool changing = false;
  SceneSystem* Clone() { return nullptr; };
  
};