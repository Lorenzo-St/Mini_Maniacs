#pragma once
#include "SDL.h"
#include <vector>
typedef enum InputActions 
{
  Any,
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
  Create,
  Parents,
  RemoveParent,
  Naming
#endif

}Action;

typedef union input 
{
  SDL_Keycode key;
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

typedef struct AnyKey : Binding
{
  AnyKey() : Binding(Any, { SDLK_DELETE }), pressedKey() {}
  input pressedKey;
}AnyKey;

class InputSystem
{
public:
  InputSystem(InputSystem const&) = delete;
  InputSystem operator=(InputSystem) = delete;
  
  static void Update(void);

  static bool isPressed(Action a);
  static bool isTriggered(Action a);

  static SDL_Keycode isPressedAny(void);
  static SDL_Keycode isTriggeredAny(void);

  static bool MouseDown(void) {return instance->LMouseDown;}
  static bool MouseDown(bool left) { if (left)return instance->LMouseDown; else return instance->RMouseDown; }
  static float GetMouseX(void) { return instance->mouseX; }
  static float GetMouseY(void) { return instance->mouseY; }

  static int WheelX(void) { return instance->wheelX; }
  static int WheelY(void) { return instance->wheelY; }

  static void addBinding(Action a, char type,input b);
  static void addBinding(Action a, input b);
  static void inputEvent(SDL_Event event);
  static InputSystem* GetInstance();

  static void MouseEvent(SDL_Event event);

private:
  InputSystem() = default;
  std::vector<Binding> bindings;
  bool LMouseDown = false;
  bool RMouseDown = false;
  


  AnyKey activeAny;
  float mouseX = false;
  float mouseY = false;

  int wheelX = 0;
  int wheelY = 0;

  static inline InputSystem* instance;
};
