#include "PlayerController.h"
#include "Backend.h"
#include "Entity.h"
#include "InputSystem.h"
#include "Physics.h"
#include "Transform.h"



void PlayerController::OnInit() 
{
  isGrounded = false;
}

void PlayerController::OnUpdate() 
{
  glm::vec2 velo = this->GetParent()->GetComponent<Physics>()->GetVelocity();
  if (isGrounded)
    velo.y = 0;

  if (InputSystem::isPressed(Jump) && isGrounded)
  {
    this->GetParent()->GetComponent<Physics>()->setGravity(gravity);
    isGrounded = false;
    velo.y = jumpSpeed;
  }
  else if (!InputSystem::isPressed(Jump) && !isGrounded)
  {
    glm::vec2 grav = this->GetParent()->GetComponent<Physics>()->getGravity();
    grav *= (1.0f + std::abs((fallSpeed * Time.deltaTime())));
    this->GetParent()->GetComponent<Physics>()->setGravity(grav);
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
  this->GetParent()->GetComponent<Physics>()->SetVelocity(velo);

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
    else if (token == "<fallSpeed>")
      fallSpeed = s->ReadFloat();
    else if (token == "<gravity>")
      gravity = s->ReadVector();
    else if (token == "</PlayerController>")
      break;
  }
}

void PlayerController::OnCollision(Entity* other) 
{
  if (other->Tag() == Ground)
    isGrounded = true;
  if (other->Tag() == Tile) 
  {
    glm::vec2 dir = other->GetComponent<Transform>()->GetPosition() - this->GetParent()->GetComponent<Transform>()->GetPosition();
    if (dir.y < 0 && std::abs(dir.y) > std::abs(dir.x))
      isGrounded = true;
  }
}


