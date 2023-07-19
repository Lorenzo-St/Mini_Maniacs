#pragma once
#include "SDL.h"
#include <vector>
typedef enum InputActions 
{

}Action;

typedef union input 
{
  SDL_KeyCode key;
  Uint8 button;
}input;

typedef struct Binding 
{
  bool triggered;
  bool pressed;
  char type;
  Action action;
  input binding;

  Binding(Action a, input b) : action(a), binding(b), triggered(false), pressed(false), type(0) {};
  Binding(Action a, input b, char t) : action(a), binding(b), triggered(false), pressed(false), type(t) {};

}Binding;


class InputSystem
{
public:
  
  void Update(void);

  bool isPressed(Action a);
  bool isTriggered(Action a);

  void addBinding(Action a, char type,input b);
  void addBinding(Action a, input b);

private:
  std::vector<Binding> bindings;
};

extern InputSystem Input;