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
  int lastTile = 0;
  PalletInfo(PalletInfo const& p)
    : spriteOffset(p.spriteOffset)
    , totalTiles(p.totalTiles)
  {}
  PalletInfo() = default;
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
  {
    for (auto const& a : b->pallets)
      pallets.push_back(a);
  }
  StagePallet* Clone() { return new StagePallet(this); }


public:
  void SetPallet(int pallet, Animation* s);
  void Write(std::ofstream* s);
  void Read(Stream* s);
private:
  // -------------------------
  // Required Component things
  // -------------------------
  constexpr bool set() { setType(__CLASS_NAME__); return true; };
  const bool s = set();
  // -------------------------
  std::vector<PalletInfo> pallets = {};
};