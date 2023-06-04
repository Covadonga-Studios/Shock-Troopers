#include "Enemy_ThreeBarrels.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
Enemy_ThreeBarrels::Enemy_ThreeBarrels(int x, int y) : Enemy(x, y)
{

	boxidle.PushBack({ 112, 1964, 56, 65 });

	box.PushBack({176, 1971,72,56});
	box.speed = 0.15f;
	box.loop = false;

	currentAnim = &boxidle;

	collider = App->collisions->AddCollider({ 20, 20, 56, 65 }, Collider::Type::ENEMY, (Module*)App->enemies);
	hp = 1;

}

void Enemy_ThreeBarrels::Update()
{

	switch (enemyMode)
	{
	case 0:
		currentAnim = &boxidle;
		break;
	case 1:
		currentAnim = &box;
		break;
	}


	if (pendingToDelete == true && deleting == false)
	{
		pendingToDelete = false;
		deleting = true;
		App->particles->AddParticle(App->particles->explosionDefault, position.x + 5, position.y + 6, 0, 0, false, Collider::Type::NONE);
		App->particles->AddParticle(App->particles->explosionDefault, position.x + 5, position.y + 6, 0, 0, false, Collider::Type::NONE,5);

	}

	if (deleting == true) 
	{
		deathTimer++;
	}

	if (deathTimer > 60)
	{

		pendingToDelete = true;
	}

	collider->SetPos(position.x, position.y);
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
