#pragma once
#include <vector>
#include "Backend.h"
#include "Behavior.h"
#include "glm.hpp"
class Animation;

typedef struct PalletInfo 
{
  glm::vec2 spriteOffset;
  int totalTiles;
  int lastTile;
}PalletInfo;


class StagePallet : public Behavior
{
private:
  enum States
  {

  };
public:
  StagePallet() = default;
  StagePallet(StagePallet const* b)
    : Behavior(b)
    , pallets(b->pallets)
  {}
  StagePallet* Clone() { return new StagePallet(this); }


public:

  void SetPallet(int pallet, Animation* s);

  void Read(Stream* s);
private:
  std::vector<PalletInfo> pallets;
};