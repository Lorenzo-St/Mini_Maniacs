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
  SDL_Event event;
  while (running)
  {
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT || event.type == SDL_APP_TERMINATING)
      {
        running = false;
      }
      else
      {
        ProcessEvent(event);
      }

    }
    api.Update();
    for (auto& system : Systems)
      system->Update();
  
    for (auto& system : Systems)
      system->Render();
  
  
#if 0
    std::cout << "FR: " << 1.0 / Time.deltaTime() << " DT: " << Time.deltaTime() << std::endl;
#endif
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


