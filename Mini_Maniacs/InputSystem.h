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
  Action action;
  bool triggered;

}Binding;


class InputSystem
{
public:
  
  void Update(void);

  bool isPressed(Action a);
  bool isTriggered(Action a);

  void addBinding(Action a, Binding b);

private:

};