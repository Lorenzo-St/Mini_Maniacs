#pragma once
#include "Component.h"


class Transform : public Component
{
public:
  Transform() 
  {

  }
  Transform* Clone() { return nullptr; };
  void Read() { };
private:
  constexpr bool set() { setType(__CLASS_NAME__); return true; };
};

class mesh : public Component
{
public:
  mesh()
  {

  }
  mesh* Clone() { return nullptr; };
  void Read() { };
private:
  constexpr bool set() { setType(__CLASS_NAME__); return true; };
};

class Animation : public Component
{
public:
  Animation()
  {

  }
  Animation* Clone() { return nullptr; };
  void Read() { };
private:
  constexpr bool set() { setType(__CLASS_NAME__); return true; };
};
class Ai : public Component
{
public:
  Ai()
  {

  }
  Ai* Clone() { return nullptr; };
  void Read() { };
private:
  constexpr bool set() { setType(__CLASS_NAME__); return true; };
};
class Door : public Component
{
public:
  Door()
  {

  }
  Door* Clone() { return nullptr; };
  void Read() { };
private:
  constexpr bool set() { setType(__CLASS_NAME__); return true; };
};

class Physics : public Component
{
public:
  Physics()
  {

  }
  Physics* Clone() { return nullptr; };
  void Read() { };
private:
  constexpr bool set() { setType(__CLASS_NAME__); return true; };
};

class Sprite : public Component
{
public:
  Sprite()
  {

  }
  Sprite* Clone() { return nullptr; };
  void Read() { };
private:
  constexpr bool set() { setType(__CLASS_NAME__); return true; };
};




