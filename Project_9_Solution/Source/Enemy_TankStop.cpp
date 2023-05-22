#include "Enemy_TankStop.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"

Enemy_TankStop::Enemy_TankStop(int x, int y) : Enemy(x, y)
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

	collider = App->collisions->AddCollider({ 20, 20, 28, 36 }, Collider::Type::ENEMY, (Module*)App->enemies);
	hp = 10;

}

void Enemy_TankStop::Update()
{
	shootCooldown++;

	if (shootCooldown > 60) 
	{
		App->particles->AddParticle(App->particles->PlayerShotLeft, position.x, position.y, -5, 0, false, Collider::Type::ENEMY_SHOT);
		shootCooldown = 0;
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

	collider->SetPos(position.x + 20, position.y + 24);
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
