#include "GameManager.h"
#include "Entity.h"
#include "EntitySystem.h"
#include "Animation.h"
#include "StagePallet.h"

void GameManager::OnInit() 
{
  CreateRoom("room");
}

void GameManager::OnUpdate() 
{

}

void GameManager::OnExit() 
{

}

void GameManager::Read(Stream* s) 
{
  std::string token;
  while (true) 
  {
    token = s->ReadString();
    if (token == "<ActivePallet>")
      currentPallet = s->ReadInt();
    else if (token == "</GameManager>")
      break;
  }
}

void GameManager::CreateRoom(const char* prefabName) 
{
  Entity* e = EntitySystem::GetActive().CreatePrefab(prefabName);
  StagePallet* sp = this->GetParent()->GetComponent<StagePallet>();
  auto& children = e->FindChildrenWithTag(Tile);
  
  for (auto& e : children.GetCollection()) 
  {
    Animation* a = e->GetComponent<Animation>();
    sp->SetPallet(currentPallet, a);
  }
}