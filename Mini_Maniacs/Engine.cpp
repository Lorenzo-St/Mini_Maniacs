#include "Engine.h"
#define STEPTHROUGH 0
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
    const_cast<System*>(system)->Init();
  }

}

void Engine::Update(void)
{
  SDL_Event event;
  bool contin = true;
  while (running)
  {
#if _DEBUG && STEPTHROUGH
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
#if _DEBUG && STEPTHROUGH
  }
#endif

    api.Update();
    for (auto& system : Systems)
      const_cast<System*>(system)->Update();
  
    for (auto& system : Systems)
      const_cast<System*>(system)->Render();
  
    contin = false;
#if STEPTHROUGH
    std::cout << "FR: " << 1.0 / Time.deltaTime() << " DT: " << Time.deltaTime() << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
#endif
  }
}

void Engine::Exit(void) 
{


  for (auto& system : Systems)
  {
    const_cast<System*>(system)->Exit();
  }
  api.Shutdown();
}

errState Engine::GetErr(void)
{
  return error;
}


