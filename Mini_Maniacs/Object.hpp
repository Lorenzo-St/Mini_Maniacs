#pragma once
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
  virtual Object* Clone() = 0;
private:

};