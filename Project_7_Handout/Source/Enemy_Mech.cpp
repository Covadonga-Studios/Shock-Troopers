#include "Enemy_Mech.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Mech::Enemy_Mech(int x, int y) : Enemy(x, y)
{
	walk.PushBack({ 5,106,31,31 });
	walk.PushBack({ 39,106,31,31 });
	walk.PushBack({ 73,106,31,31 });
	walk.speed = 0.2f;
	currentAnim = &walk;
	path.PushBack({ -0.5f, 0}, 100, &walk);
	path.PushBack({ 1, 0}, 100, &walk);

	// TODO 3: Have the Brown Cookies describe a path in the screen

	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Mech::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();



	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
