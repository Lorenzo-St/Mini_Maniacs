#include "Engine.h"

static errState error;

void Engine::Init(void)
{
  api.Init();
  if (api.GetError() != 0)
  {
    api.Shutdown();
    error = 100;
    return;
  }

  for (auto& system : Systems) 
  {
    system->Init();
  }

}

void Engine::Update(void)
{
  api.Update();
  for (auto& system : Systems)
  {
    system->Update();
  }
}

void Engine::Exit(void) 
{
  for (auto& system : Systems)
  {
    system->Exit();
  }
  api.Shutdown();
}

errState Engine::GetErr(void)
{
  return error;
}


