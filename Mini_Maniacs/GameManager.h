#pragma once
#include <vector>

#include "Behavior.h"
#include "Stream.h"

class GameManager : public Behavior
{
private:
  enum States
  {

  };
public:
  GameManager() = default;
  GameManager(GameManager const* b)
    : Behavior(b)
  {}
  GameManager* Clone() { return new GameManager(this); }


public:
  void OnInit();
  void OnUpdate();
  void OnExit();

  void Read(Stream* s);
private:
  void CreateRoom(const char* prefabName);

  std::vector<std::string> roomPrefabs;

};