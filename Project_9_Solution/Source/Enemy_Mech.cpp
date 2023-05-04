#include "Enemy_Mech.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Mech::Enemy_Mech(int x, int y) : Enemy(x, y)
{
	enemydeath2.PushBack({ 20, 773, 41, 53 });
	enemydeath2.PushBack({ 61, 773, 41, 53 });
	enemydeath2.PushBack({ 102, 773, 41, 53 });
	enemydeath2.PushBack({ 143, 773, 41, 53 });
	enemydeath2.PushBack({ 184, 773, 41, 53 });
	enemydeath2.PushBack({ 225, 773, 41, 53 });
	enemydeath2.PushBack({ 266, 773, 41, 53 });

	collider = App->collisions->AddCollider({0, 0, 24, 24}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Mech::Update()
{
	
	

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
