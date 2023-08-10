#include "PlayerController.h"
#include "Backend.h"
#include "Entity.h"
#include "InputSystem.h"
#include "Transform.h"



void PlayerController::OnInit() 
{
}

void PlayerController::OnUpdate() 
{
  if (InputSystem::isPressed(Jump) && isGrounded)
  {
    isGrounded = false;
    this->GetParent()->GetComponent<Transform>()->AddVelocity({ 0, jumpSpeed });
  }
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
    else if (token == "</PlayerController>")
      break;
  }
}

void PlayerController::OnCollision(Entity* other) 
{
  if (other->Tag() == Ground)
    isGrounded = true;
}


