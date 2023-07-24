#pragma once
#include <vector>
#include "Object.hpp"
class Entity;


class EntityContainer : public Object
{
public:
  EntityContainer() = default;
  ~EntityContainer();
  EntityContainer* Clone() { return new EntityContainer(this); }
  EntityContainer(EntityContainer const* other) { entities = other->entities; }

  void add(Entity* e) { entities.push_back(e); }

  void destroyAll(void);
  void remove(Entity* e);
  void Update();
  void Render();
private:
  std::vector<Entity*> entities;
};