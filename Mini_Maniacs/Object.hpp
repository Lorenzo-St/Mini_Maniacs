#pragma once
#include <iostream>
class Stream;

class Object 
{
public:
  Object(void) {};
  Object(Object const& o) {};

  virtual void Awake(void) { return; };
  virtual void Init(void) { return; };
  virtual void Update(void) { return; };
  virtual void Render(void) { return; };
  virtual void Exit(void) { return; };

  virtual void OnDestroy(void) { return; };
  virtual void OnAwake(void) { return; };
  virtual void Read(Stream* s) {};
  virtual void Write(std::ofstream* s) { return; };
  
  virtual Object* Clone() = 0;
  virtual void CheckClass() { std::cout << typeid(*this).name() << std::endl; }

  void SetActive(bool b) { Active = b; }
  bool isActive(void) { return Active; }
  bool isRoot(void) { return rootObject; }
  void SetRoot(bool b) { rootObject = b; }
  Object* Parent(void) { return parent; }
  void SetParent(Object* p) { parent = p; }

private:
  bool rootObject = false;
  bool Active = true;
  Object* parent = nullptr;

};