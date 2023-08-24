#pragma once
#include "SDL.h"
#include <vector>
typedef enum InputActions 
{
  Enter, 
  Back,
  PosX,
  NegX,
  Jump,
#ifdef EDITOR
  Save,
  GridLock,
  Duplicate,
  Delete,
#endif

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
  
  static void Update(void);

  static bool isPressed(Action a);
  static bool isTriggered(Action a);
  static bool MouseDown(void) {return instance->LMouseDown;}
  static bool MouseDown(bool left) { if (left)return instance->LMouseDown; else return instance->RMouseDown; }
  static float GetMouseX(void) { return instance->mouseX; }
  static float GetMouseY(void) { return instance->mouseY; }

  static void addBinding(Action a, char type,input b);
  static void addBinding(Action a, input b);
  static void inputEvent(SDL_Event event);
  static InputSystem* GetInstance();

  static void MouseEvent(SDL_Event event);

private:
  InputSystem() = default;
  std::vector<Binding> bindings;
  bool LMouseDown;
  bool RMouseDown;
  float mouseX;
  float mouseY;

  static inline InputSystem* instance;
};
