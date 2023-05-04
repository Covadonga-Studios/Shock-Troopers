#include "Enemy_Mech.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Mech::Enemy_Mech(int x, int y) : Enemy(x, y)
{
	
	boxidle.PushBack({ 1328, 453, 65, 65 });
	box.PushBack({ 1394, 453, 65, 65 });
	box.PushBack({ 1460, 453, 65, 65 });
	box.PushBack({ 1526, 453, 65, 65 });
	box.PushBack({ 1592, 453, 65, 65 });
	box.PushBack({ 1658, 453, 65, 65 });
	box.PushBack({ 1724, 453, 65, 65 });
	box.PushBack({ 1790, 453, 65, 65 });
	box.PushBack({ 1856, 453, 65, 65 });
	box.speed = 0.15f;
	box.loop = false;

	currentAnim = &boxidle;

	collider = App->collisions->AddCollider({0, 0, 40, 40}, Collider::Type::ENEMY, (Module*)App->enemies);
	

}

void Enemy_Mech::Update()
{
	

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
	 

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
