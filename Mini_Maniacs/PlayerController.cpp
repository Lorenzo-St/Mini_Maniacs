#include "PlayerController.h"
#include "Backend.h"
#include "Entity.h"
#include "InputSystem.h"
#include "Physics.h"
#include "Transform.h"



void PlayerController::OnInit() 
{
  isGrounded = true;
}

void PlayerController::OnUpdate() 
{
  glm::vec2 velo = this->GetParent()->GetComponent<Physics>()->GetVelocity();
  if(isGrounded)
    this->GetParent()->GetComponent<Physics>()->setGravity({0,0});
  else if (this->GetParent()->GetComponent<Physics>()->getGravity() == glm::vec2(0,0))
    this->GetParent()->GetComponent<Physics>()->setGravity(gravity);

  if (InputSystem::isPressed(Jump) && isGrounded)
  {
    this->GetParent()->GetComponent<Physics>()->setGravity(gravity);
    velo.y = jumpSpeed;
  }
  else if (!InputSystem::isPressed(Jump) && !isGrounded)
  {
    glm::vec2 grav = this->GetParent()->GetComponent<Physics>()->getGravity();
    grav *= (1.0f + std::abs((fallSpeed * Time.deltaTime())));
    this->GetParent()->GetComponent<Physics>()->setGravity(grav);
  }
  else if (!InputSystem::isPressed(Jump))
    isGrounded = false;
  
  
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

  if (std::abs(velo.y) > 100)
    velo.y = 100 * velo.y / std::abs(velo.y);
  if (std::abs(velo.x) > 100)
    velo.x = 100 * velo.x / std::abs(velo.x);

  this->GetParent()->GetComponent<Physics>()->SetVelocity(velo);
  api.MoveCamera(glm::vec2( 0,this->GetParent()->GetComponent<Transform>()->GetPosition().y ));
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
    if (dir.y <= 0 && std::abs(dir.y) >= std::abs(dir.x))
      isGrounded = true;
  }
}


