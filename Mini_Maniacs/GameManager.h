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
  // -------------------------
  // Required Component things
  // -------------------------
  constexpr bool set() { setType(__CLASS_NAME__); return true; };
  const bool s = set();
  // -------------------------

  void CreateRoom(const char* prefabName);
  int currentPallet = 0;
  std::vector<std::string> roomPrefabs;

};