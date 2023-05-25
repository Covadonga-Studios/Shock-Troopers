#include "Enemy_ThreeBarrels.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_ThreeBarrels::Enemy_ThreeBarrels(int x, int y) : Enemy(x, y)
{

	boxidle.PushBack({ 1809, 339, 56, 65 });


	box.speed = 0.15f;
	box.loop = false;

	currentAnim = &boxidle;

	collider = App->collisions->AddCollider({ 20, 20, 56, 65 }, Collider::Type::ENEMY, (Module*)App->enemies);
	hp = 1;

}

void Enemy_ThreeBarrels::Update()
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

	collider->SetPos(position.x, position.y);
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
