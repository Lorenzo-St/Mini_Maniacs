#include "GameManager.h"

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
    if (token == "</GameManger>")
      break;
  }
}

void GameManager::CreateRoom(const char* prefabName) 
{

}