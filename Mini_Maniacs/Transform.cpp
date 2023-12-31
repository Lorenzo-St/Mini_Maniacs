#include "Transform.h"
#include "Time.h"
#include "Stream.h"
#include "Entity.h"
#include <vector>
void Transform::Read(Stream* s)
{
  // In file order, 
  // <Transform>
  //   <Position>
  //     3.14159
  //     0.5772156649
  //   <Velocity>
  //     1.0
  //     2.5
  //   <Acceleration>
  //     0.0
  //     0.0
  //   <Drag>
  //     0.0
  // <Next Component>
  while (true)
  {

    std::string token = s->ReadString();
    if (token == "<Position>")
      pos = s->ReadVector();

    else if (token == "<Scale>")
      scale = s->ReadVector();
    else if (token == "<Rotation>")
      rot = s->ReadFloat();

    else if (token == "</Transform>")
      break;
  }

#ifdef EDITOR
  startingPos = pos;
#endif 

}

void Transform::Write(std::ofstream* s) 
{
  *s << "<Transform>\n ";
  *s << "<Position>\n  ";
  *s << pos << "\n ";
  *s << "<Rotation>\n  ";
  *s << rot << "\n ";
  *s << "<Scale>\n  ";
  *s << scale << "\n ";
  *s << "</Transform>\n ";
};


void Transform::Update(void)
{

}

void Transform::UpdatePos()
{
  pos = dynamic_cast<Entity*>(GetParent()->Parent())->GetComponent<Transform>()->GetPosition() + localPos;
}

void Transform::SetPosition(glm::vec2 const& position) {
  pos = position + localPos;

  std::vector<Entity*>& chilen = GetParent()->GetChildren();
  for (auto& e : chilen) 
  {
    e->GetComponent<Transform>()->SetPosition(pos);
  }
}


