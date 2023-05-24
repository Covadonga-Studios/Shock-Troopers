#include "Enemy_Helicopter.h"
#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Helicopter::Enemy_Helicopter(int x, int y) : Enemy(x, y)
{

	boxidle.PushBack({ 686, 1798, 108, 80 });
	


	currentAnim = &boxidle;

	collider = App->collisions->AddCollider({ 20, 20, 108, 80}, Collider::Type::ENEMY, (Module*)App->enemies);
	hp = 1;

}

void Enemy_Helicopter::Update()
{
	moveCooldown++;

	if (moveCooldown < 120) 
	{
		
	}




	if (pendingToDelete == true && deleting == false)
	{
		pendingToDelete = false;
		deleting = true;
		currentAnim = &box;
	}

	if (currentAnim->HasFinished() == true)
	{
		pendingToDelete = true;
	}

	collider->SetPos(position.x, position.y);
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
