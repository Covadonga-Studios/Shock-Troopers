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

	tankStop.PushBack({ 28, 971, 65, 41 });
	tankStop.PushBack({ 94, 971, 65, 41 });
	tankStop.PushBack({ 160, 971, 65, 41 });
	tankStop.PushBack({ 226, 971, 65, 41 });
	tankStop.PushBack({ 28, 1013, 65, 41 });
	tankStop.PushBack({ 94, 1013, 65, 41 });
	tankStop.PushBack({ 160, 1013, 65, 41 });
	tankStop.speed = 0.05f;
	
	bullet.PushBack({ 28, 925, 35, 32 });
	bullet.PushBack({ 64, 925, 35, 32 });
	bullet.PushBack({ 100, 925, 35, 32 });
	bullet.PushBack({ 136, 925, 35, 32 });

	tankStopbase.PushBack({ 27,840,110,77 });
	currentAnim = &tankStop;
	currentAnim2 = &tankStopbase;
	collider = App->collisions->AddCollider({ 20, 20, 110, 89 }, Collider::Type::ENEMY, (Module*)App->enemies);
	hp = 10;

	offsettexture2y = 12;
	offsettexture2x = -22;
}

void Enemy_TankStop::Update()
{
	shootCooldown++;

	if (shootCooldown > 140) 
	{
		App->particles->AddParticle(App->particles->PlayerShotLeft, position.x, position.y + 20, -5, 0, false, Collider::Type::ENEMY_SHOT);
		shootCooldown = 0;
	}
	

	if (pendingToDelete == true && deleting == false)
	{
		pendingToDelete = false;
		deleting = true;
		currentAnim = &box;
	}



	collider->SetPos(position.x -22, position.y );
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
