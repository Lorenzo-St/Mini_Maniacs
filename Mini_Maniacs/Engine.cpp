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
  bool contin = true;
  while (running)
  {
#if _DEBUG && 1
    while (contin == false){
#endif
      while (SDL_PollEvent(&event))
      {
        if (event.type == SDL_QUIT || event.type == SDL_APP_TERMINATING)
        {
          running = false;
        }
        else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
          contin = true;
        else
        {
          ProcessEvent(event);
        }
      }
#if _DEBUG && 1
  }
#endif

    api.Update();
    for (auto& system : Systems)
      system->Update();
  
    for (auto& system : Systems)
      system->Render();
  
    contin = false;
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


