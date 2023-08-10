#pragma once
#include <vector>
#include "system.h"
class Entity;


class CollisionLedger : public System // Singlton
{
private:
  struct Interaction
  {
    Entity* e1;
    Entity* e2;
  };
public:
  CollisionLedger(CollisionLedger const&) = delete;
  CollisionLedger operator=(CollisionLedger const&) = delete;

  static CollisionLedger const* GetInstance() { if (instance == nullptr) instance = new CollisionLedger();  return instance; };

  void Init();
  void Update();
  void Exit();

  static void AddInteraction(Interaction i) { instance->collisions.push_back(i); };

private:
  CollisionLedger() = default;
  CollisionLedger* Clone() { throw std::runtime_error("no"); };
  static inline CollisionLedger* instance;
  std::vector<Interaction> collisions;
};