#include "Enemy_Bazooka.h"

#include "Module.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"
#include "stdio.h"


Enemy_Bazooka::Enemy_Bazooka(int x, int y) : Enemy(x, y)
{
	enemydeath2.PushBack({ 20, 773, 41, 53 });
	enemydeath2.PushBack({ 61, 773, 41, 53 });
	enemydeath2.PushBack({ 102, 773, 41, 53 });
	enemydeath2.PushBack({ 143, 773, 41, 53 });
	enemydeath2.PushBack({ 184, 773, 41, 53 });
	enemydeath2.PushBack({ 225, 773, 41, 53 });
	enemydeath2.PushBack({ 266, 773, 41, 53 });
	enemydeath2.speed = 0.1f;
	enemydeath2.loop = false;

	enemyshot2down.PushBack({ 20, 647, 43, 47 });
	enemyshot2rightdown.PushBack({ 63, 647, 43, 47 });
	enemyshot2right.PushBack({ 106, 647, 43, 47 });
	enemyshot2rightup.PushBack({ 149, 647, 43, 47 });
	enemyshot2up.PushBack({ 192, 647, 43, 47 });
	enemyshot2upleft.PushBack({ 235, 647, 43, 47 });
	enemyshot2left.PushBack({ 278, 647, 43, 47 });
	enemyshot2downleft.PushBack({ 321, 647, 43, 47 });

	enemyDying.PushBack({ 1, 1237, 41, 53 });
	enemyDying.PushBack({ 43, 1237, 41, 53 });
	enemyDying.PushBack({ 85, 1237, 41, 53 });
	enemyDying.PushBack({ 127, 1237, 41, 53 });
	enemyDying.PushBack({ 169, 1237, 41, 53 });
	enemyDying.PushBack({ 211, 1237, 41, 53 });
	enemyDying.PushBack({ 253, 1237, 41, 53 });
	enemyDying.speed = 0.1f;
	enemyDying.loop = false;

	enemyBurning.PushBack({ 1, 1294, 57, 68 });
	enemyBurning.PushBack({ 59, 1294, 57, 68 });
	enemyBurning.PushBack({ 117, 1294, 57, 68 });
	enemyBurning.PushBack({ 175, 1294, 57, 68 });
	enemyBurning.PushBack({ 233, 1294, 57, 68 });
	enemyBurning.PushBack({ 291, 1294, 57, 68 });
	enemyBurning.PushBack({ 349, 1294, 57, 68 });
	enemyBurning.PushBack({ 407, 1294, 57, 68 });
	enemyBurning.PushBack({ 465, 1294, 57, 68 });
	enemyBurning.PushBack({ 523, 1294, 57, 68 });
	enemyBurning.PushBack({ 581, 1294, 57, 68 });
	enemyBurning.PushBack({ 639, 1294, 57, 68 });
	enemyBurning.PushBack({ 697, 1294, 57, 68 });
	enemyBurning.PushBack({ 755, 1294, 57, 68 });
	enemyBurning.PushBack({ 813, 1294, 57, 68 });
	enemyBurning.PushBack({ 871, 1294, 57, 68 });
	enemyBurning.speed = 0.1f;
	enemyBurning.loop = false;

	bazookaRight.PushBack({ 10, 1868, 41, 55 });

	bazookaLeft.PushBack({ 10, 1868, 41, 55 }, true);

	bazookaUp.PushBack({ 53, 1868, 41, 55 });

	bazookaUpLeft.PushBack({ 10, 1925, 41, 55 });

	bazookaUpRight.PushBack({ 10, 1925, 41, 55 }, true);

	bazookaDown.PushBack({ 53, 1925, 41, 55 });

	bazookaDownLeft.PushBack({ 16, 1982, 28, 54 });

	bazookaDownRight.PushBack({ 16, 1982, 28, 54 }, true);

	hp = 1;

	currentAnim = &flyAnim;

	collider = App->collisions->AddCollider({ 0, 0, 43, 43 }, Collider::Type::ENEMY, (Module*)App->enemies);
}



void Enemy_Bazooka::Update()
{

	shootCooldown++;

	dx = (App->player->position.x + App->player->collider->rect.w / 2 - position.x);
	dy = (App->player->position.y + App->player->collider->rect.h / 2 - position.y);

	if (hp <= 0 && deleting == false)
	{
		pendingToDelete = false;
		deleting = true;
		if (!isOnFire)
			currentAnim = &enemyDying;
		else
			currentAnim = &enemyBurning;
	}

	if (currentAnim->HasFinished() && hp <= 0)
	{
		die = true;
	}

	if (shootCooldown > 233 && deleting == false)
	{


		float dir = Dircalculation(dx, dy);

		float dirx = (dx * 1.5f / dir);
		float diry = (dy * 1.5f / dir);

		

		switch (GetTargetDir(dx, dy))
		{
		case LEFT:
			App->particles->AddParticle(App->particles->missileLeft, position.x, position.y, dirx, diry, false, Collider::Type::MISSILE,0,true, 20,20);
			break;
		case RIGHT:
			App->particles->AddParticle(App->particles->missileRight, position.x, position.y, dirx, diry, false, Collider::Type::MISSILE, 0, true, 20, 20);
			break;
		case DOWN:
			App->particles->AddParticle(App->particles->missileDown, position.x, position.y, dirx, diry, false, Collider::Type::MISSILE, 0, true, 20, 20);
			break;
		case UP:
			App->particles->AddParticle(App->particles->missileUp, position.x, position.y, dirx, diry, false, Collider::Type::MISSILE, 0, true, 20, 20);
			break;
		case DOWNLEFT:
			App->particles->AddParticle(App->particles->missileDownLeft, position.x, position.y, dirx, diry, false, Collider::Type::MISSILE, 0, true, 20, 23,0,30);
			break;
		case DOWNRIGHT:
			App->particles->AddParticle(App->particles->missileDownRight, position.x, position.y, dirx, diry, false, Collider::Type::MISSILE, 0, true, 20, 23,35,30);
			break;
		case UPLEFT:
			App->particles->AddParticle(App->particles->missileUpLeft, position.x, position.y, dirx, diry, false, Collider::Type::MISSILE, 0, true, 20, 20);
			break;
		case UPRIGHT:
			App->particles->AddParticle(App->particles->missileUpRight, position.x, position.y, dirx, diry, false, Collider::Type::MISSILE, 0, true, 20, 20);
			break;
		}
		

		shootCooldown = 0;
	}

	if (deleting == false)
		switch (GetTargetDir(dx, dy))
		{
		case LEFT:
			currentAnim = &bazookaLeft;
			break;
		case RIGHT:
			currentAnim = &bazookaRight;
			break;
		case DOWN:
			currentAnim = &bazookaDown;
			break;
		case UP:
			currentAnim = &bazookaUp;
			break;
		case DOWNLEFT:
			currentAnim = &bazookaDownLeft;
			break;
		case DOWNRIGHT:
			currentAnim = &bazookaDownRight;
			break;
		case UPLEFT:
			currentAnim = &bazookaUpLeft;
			break;
		case UPRIGHT:
			currentAnim = &bazookaUpRight;
			break;
		}

	collider->SetPos(position.x, position.y);

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
