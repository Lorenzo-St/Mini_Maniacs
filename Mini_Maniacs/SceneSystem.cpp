#if _DEBUG
#include <iostream>
#endif
#include "SceneSystem.h"
#include "Scene.h"
#include "Temp.h"


void SceneSystem::Init(void) 
{
  SetNextScene(new TempScene());
}

void SceneSystem::Update(void) 
{

  if (changing) 
  {
#if _DEBUG && 0
    std::cout << "Changing Scene" << std::endl;
#endif
    if (Active) 
    {
      Active->Exit();
      if (!restarting)
        delete Active;
      Active = nullptr;
    }

    Active = nextScene;
    nextScene = nullptr;
    
    if (Active) 
    {
      Active->Read();
      Active->Init();
    }
    
    changing = false;
    restarting = false;
  }
  if (Active == nullptr)
    return;

#if _DEBUG && 0
  std::cout << "Updating Scene" << std::endl;
#endif
  Active->Update();


}

void SceneSystem::Exit(void) 
{
  if (Active) 
  {
    Active->Exit();
    delete Active;
    Active = nullptr;
  }
  if(nextScene)
  {
    nextScene->Exit();
    delete nextScene;
    nextScene = nullptr;
  }

  
  
}

void SceneSystem::SetNextScene(Scene* s)
{
  if(s == Active)
    restarting = true;
  s->SetSceneSystem(this); 
  nextScene = s;
  changing = true;
}
