#pragma once
#include "Object.hpp"

class SceneSystem;
#ifdef EDITOR
class Entity;
#include <vector>
#endif
class Scene : public Object 
{
public:
  enum ReadSection
  {
    Default,
    Entities,
    Prefabs,

  
  };
  
  Scene() = default;
  Scene(Scene const& s) { sceneSystem = s.sceneSystem; };
  virtual void Init(void)   { return; };
  virtual void Update(void) { return; };
  virtual void Exit(void)   { return; };
  virtual void Read(void) { return; };
  void SetSceneSystem(SceneSystem* s) { sceneSystem = s; };
  SceneSystem* getSceneSystem(void) { return sceneSystem; };
  void name(std::string nl) { n = nl; }
  std::string const& name(void) { return n; }
#ifdef EDITOR

  void Write(std::ofstream* s);
#else
  void Write(std::ofstream* s) { return; }
#endif
  void ReadFile(const char* c);
private:
  void Render(void) {};
  void Awake(void) {};
  void OnDestroy(void) {};
  void OnAwake(void) {};
#ifdef EDITOR
  std::vector<Entity*> entities;
  std::vector<Entity*> prefabs;
#endif

  Scene* Clone() { return new Scene(); }
  std::string n;
  static inline SceneSystem* sceneSystem;
};
