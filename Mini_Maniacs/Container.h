#pragma once
#include <vector>
#include "Object.hpp"

template<typename t>
class Container : public Object
{
public:
  Container() = default;
  ~Container()
  {
    for (auto& e : entities)
    {
      delete e;
    }
    entities.clear();
  }

  Container* Clone() { return new Container(this); }
  Container(Container const* other) { entities = other->entities; }

  t* FindFind(const char* name)
  {
    for (auto& e : entities)
    {
      if (e->isNamed(std::string(name)))
        return e;
    }
    return nullptr;
  }

  t* FindProto(const char* name)
  {
    for (auto& e : entities)
    {
      if (e->isProto(std::string(name)))
        return e;
    }
    return nullptr;
  }



  void add(t* e) { entities.push_back(e); }
  void destroyAll()
  {
    for (auto& e : entities)
      delete e;
    entities.clear();

  }

  void remove(t* e)
  {
    int i = 0;
    for (auto& el : entities)
    {
      if (e == el)
        entities.erase(entities.begin() + i);
      ++i;
    }

  };

  void Update()
  {
    for (auto& e : entities)
      e->Update();
  }

  void Render()
  {
    for (auto& e : entities)
      e->Render();
  }
private:
  std::vector<t*> entities;
};