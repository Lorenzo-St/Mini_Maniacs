#include "GameManager.h"
#include "Entity.h"
#include "EntitySystem.h"
#include "Animation.h"
#include "StagePallet.h"
#include "Transform.h"

void GameManager::OnInit() 
{
  CreateRoom("room", {0,0});

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

void GameManager::Write(std::ofstream* s) 
{
  *s << "<GameManager>\n  ";
  *s << "<ActivePallet>\n   ";
  *s << currentPallet << "\n  ";
  *s << "</GameManager>\n ";
}

void GameManager::CreateRoom(const char* prefabName, glm::vec2 pos) 
{
  Entity* e = EntitySystem::GetActive().CreatePrefab(prefabName);
  e->GetComponent<Transform>()->SetPosition(pos);
  StagePallet* sp = this->GetParent()->GetComponent<StagePallet>();
  auto& children = e->FindChildrenWithTag(Tile);
  
  for (auto& e : children.GetCollection()) 
  {
    Animation* a = e->GetComponent<Animation>();
    sp->SetPallet(currentPallet, a);
  }
}