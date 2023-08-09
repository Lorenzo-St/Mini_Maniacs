#pragma once
#include "Component.h"
#include "glm.hpp"
class Animation : public Component
{
public:
  Animation() = default;
  Animation(Animation const* ml);
  Animation* Clone() { return new Animation(this); };
  void Read(Stream* s);
  void Update(void);


  int MaxFrames() { return maxFrame; }
  void MaxFrames(int i) { maxFrame = i; }

  void Frame(int i) { frame = i; }
  int Frame(void) { return frame; }

  float FrameTime(void) { return frameTime; }

  float FrameLength(void) { return frameLength; }
  void FrameLength(float f) { frameLength = f; }

private:
  // -------------------------
  // Required Component things
  // -------------------------
  constexpr bool set() { setType(__CLASS_NAME__); return true; };
  const bool s = set();
  // -------------------------
  int frame = 0; 
  int maxFrame = 0;
  float frameTime = 0;
  float frameLength = 0;

  int Columns = 0;
  int Rows = 0;
  glm::vec2 frameOffset = { 0,0 };
  bool looping = true;

  void UpdateMesh();

};

