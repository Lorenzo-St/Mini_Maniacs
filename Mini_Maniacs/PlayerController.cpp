#include "PlayerController.h"
#include "Backend.h"
#include "Entity.h"
#include "InputSystem.h"

void PlayerController::OnInit() 
{
  
}

void PlayerController::OnUpdate() 
{

}

void PlayerController::OnExit() 
{

}

void PlayerController::Read(Stream* s) 
{

}

void PlayerController::OnCollision(Entity* other) 
{
  if (other->Tag() == Ground)
    isGrounded = true;
}


