#pragma once
#include "Object.hpp"

class SceneSystem;

class Scene : public Object 
{
public:
  Scene() = default;
  Scene(Scene const& s) { sceneSystem = s.sceneSystem; };
  virtual void Init(void)   { return; };
  virtual void Update(void) { return; };
  virtual void Exit(void)   { return; };
  void SetSceneSystem(SceneSystem* s) { sceneSystem = s; };
  SceneSystem* getSceneSystem(void) { return sceneSystem; };
private:
  void Render(void) {};
  void Awake(void) {};
  void OnDestroy(void) {};
  void OnAwake(void) {};
  Scene* Clone() { return new Scene(); }
  static inline SceneSystem* sceneSystem;
};
