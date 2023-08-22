#include "StagePallet.h"
#include "Animation.h"
#include "Stream.h"

void StagePallet::SetPallet(int pallet, Animation* s) 
{
  pallets[pallet].lastTile = (pallets[pallet].lastTile + 1) % pallets[pallet].totalTiles;

  int tile = pallets[pallet].lastTile;
  
  glm::vec2 newOffset = { tile % s->rows(), static_cast<int>(tile / s->rows()) };
  newOffset += pallets[pallet].spriteOffset;
  s->Offset(newOffset);
}

void StagePallet::Read(Stream* s) 
{


  std::string token;
  while (true) 
  {
    token = s->ReadString();
    if (token == "<tileMap>")
      tileMap = Textures.LoadTexture(s->ReadString());
    else if (token == "<PalletInfo>")
    {
      PalletInfo pi = {};
      pi.spriteOffset = s->ReadVector();
      pi.totalTiles = s->ReadInt();
      pallets.push_back(pi);
    }
    else if (token == "</StagePallet>")
      break;
  }

}

