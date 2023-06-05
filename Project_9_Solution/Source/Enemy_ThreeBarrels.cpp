#include "Enemy_ThreeBarrels.h"
#include "ModulePlayer.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
Enemy_ThreeBarrels::Enemy_ThreeBarrels(int x, int y) : Enemy(x, y)
{
	peekyDownRight.PushBack({ 1020, 1231, 33, 28 });

	peekyDown.PushBack({ 1054, 1231, 33, 28 });

	peekyDownLeft.PushBack({ 1088, 1231, 33, 28 });

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
	int offsetx = 35;
	int offsety = 10;
	dx = (App->player->position.x + App->player->collider->rect.w / 2 - position.x - offsetx);
	dy = (App->player->position.y + App->player->collider->rect.h / 2 - position.y - offsety);
	shootCooldown++;
	switch (enemyMode)
	{
	case 0:
		currentAnim = &boxidle;
		break;
	case 1:
		currentAnim = &box;
		break;
	case 2:
		currentAnim2 = &box;
		offsettexture1x = 35;
		offsettexture1y = -9;
		if (shootCooldown > 120 && deleting == false)
		{

			float dir = Dircalculation(dx, dy);

			float dirx = (dx * 1.5f / dir);
			float diry = (dy * 1.5f / dir);


			App->particles->AddParticle(App->particles->laser, position.x + offsetx, position.y + offsety, dirx * 2, diry * 2, false, Collider::Type::ENEMY_SHOT);

			shootCooldown = 0;
		}

		if (deleting == false)
			switch (GetTargetDir(dx, dy))
			{
			case LEFT:
				currentAnim = &peekyDownLeft;
				break;
			case RIGHT:
				currentAnim = &peekyDownRight;
				break;
			case DOWN:
				currentAnim = &peekyDown;
				break;

			case DOWNLEFT:
				currentAnim = &peekyDownLeft;
				break;
			case DOWNRIGHT:
				currentAnim = &peekyDownRight;
				break;

			}

		break;
	}



	if (hp <= 0 && deleting == false)
	{
		pendingToDelete = false;
		deleting = true;
		switch (enemyMode)
		{
		case 0: //lateral
			App->particles->AddParticle(App->particles->explosionDefault, position.x + 2, position.y + -10, 0, 0, false, Collider::Type::NONE);
			App->particles->AddParticle(App->particles->explosionDefault, position.x + 2, position.y + 20, 0, 0, false, Collider::Type::NONE, 5);
			break;
		case 1: //pa abajo
			App->particles->AddParticle(App->particles->explosionDefault, position.x + 4, position.y + -10, 0, 0, false, Collider::Type::NONE);
			App->particles->AddParticle(App->particles->explosionDefault, position.x + 4, position.y + 20, 0, 0, false, Collider::Type::NONE, 5);
			break;
		case 2:
			App->particles->AddParticle(App->particles->explosionDefault, position.x + 4, position.y + -10, 0, 0, false, Collider::Type::NONE);
			App->particles->AddParticle(App->particles->explosionDefault, position.x + 4, position.y + 20, 0, 0, false, Collider::Type::NONE, 5);
			break;
		}


	}

	

	if (deleting == true) 
	{
		deathTimer++;
	}

	if (deathTimer > 25)
	{

		die = true;
	}

	collider->SetPos(position.x, position.y);
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
