#include "PlayerController.h"
#include "Backend.h"
#include "Entity.h"
#include "InputSystem.h"
#include "Transform.h"

std::ostream& operator<<(std::ostream& o, glm::vec2 vec) 
{
  o << "( " << vec.x << " ," << vec.y << " )";
  return o;
}




void PlayerController::OnInit() 
{
}

void PlayerController::OnUpdate() 
{
  glm::vec2 velo = this->GetParent()->GetComponent<Transform>()->GetVelocity();
  if (InputSystem::isPressed(Jump) && isGrounded)
  {
    isGrounded = false;
    velo.y = jumpSpeed;
  }
  if (InputSystem::isPressed(PosX)) 
  {
    velo.x = moveSpeed;
  }
  else if (InputSystem::isPressed(NegX)) 
  {
    velo.x = -moveSpeed;
  }
  else
    velo.x = 0;
  this->GetParent()->GetComponent<Transform>()->SetVelocity(velo);
  this->GetParent()->GetComponent<Transform>()->Update();

}

void PlayerController::OnExit() 
{

}

void PlayerController::Read(Stream* s) 
{
  while (true) 
  {
    std::string token = s->ReadString();
    if (token == "<JumpSpeed>")
      jumpSpeed = s->ReadFloat();
    else if (token == "<MoveSpeed>")
      moveSpeed = s->ReadFloat();
    else if (token == "</PlayerController>")
      break;
  }
}

void PlayerController::OnCollision(Entity* other) 
{
  if (other->Tag() == Ground)
    isGrounded = true;
}


