#include "Behavior.h"
#include "Time.h"

void Behavior::Init() 
{
  OnInit();
};

void Behavior::Update() 
{
  if (nextState != currentState)
  {
    OnExit();

    currentState = nextState;

    OnInit();
  }

  OnUpdate();
};


void Behavior::Exit() 
{
  OnExit();
};

