#pragma once
class Object 
{
public:
  Object(void) {};
  Object(Object const& o) {};

  void Awake(void) { return; };
  void Init(void) { return; };
  void Update(void) { return; };
  void Render(void) { return; };
  void Exit(void) { return; };

  void OnDestroy(void) { return; };
  void OnAwake(void) { return; };
  
  virtual Object* Clone() = 0;
private:

};