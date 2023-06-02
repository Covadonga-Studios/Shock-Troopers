#include "Enemy_Door.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Door::Enemy_Door(int x, int y) : Enemy(x, y)
{


	door.PushBack({ 620, 1688, 153, 19 });
	door.PushBack({ 620, 1708, 153, 19 });
	door.PushBack({ 620, 1728, 153, 19 });
	door.PushBack({ 620, 1748, 153, 19 });
	door.PushBack({ 620, 1768, 153, 19 });
	door.PushBack({ 620, 1788, 153, 19 });
	door.PushBack({ 620, 1808, 153, 19 });
	door.PushBack({ 620, 1828, 153, 19 });
	door.speed = 0.05f;
	door.loop = false;

	currentAnim = &door;

	collider = App->collisions->AddCollider({ 0, 0, 0, 0 }, Collider::Type::NONE, (Module*)App->enemies);
	hp = 1;

}

void Enemy_Door::Update()
{


	if (pendingToDelete == true && deleting == false)
	{
		pendingToDelete = false;
		deleting = true;
		currentAnim = &box;
	}

	
	collider->SetPos(position.x, position.y );
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
