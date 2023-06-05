#include "Enemy_BlackSoldier.h"
#include "Module.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"
#include "stdio.h"
#include "math.h"

Enemy_BlackSoldier::Enemy_BlackSoldier(int x, int y) : Enemy(x, y)
{

	boxidle.PushBack({ 686, 1798, 108, 80 });

	greyEnemyMeleeDown.PushBack({ 1, 1157, 83, 78 });
	greyEnemyMeleeDown.PushBack({ 85, 1157, 83, 78 });
	greyEnemyMeleeDown.PushBack({ 169, 1157, 83, 78 });
	greyEnemyMeleeDown.PushBack({ 253, 1157, 83, 78 });
	greyEnemyMeleeDown.PushBack({ 337, 1157, 83, 78 });
	greyEnemyMeleeDown.PushBack({ 421, 1157, 83, 78 });
	greyEnemyMeleeDown.PushBack({ 505, 1157, 83, 78 });
	greyEnemyMeleeDown.PushBack({ 589, 1157, 83, 78 });
	greyEnemyMeleeDown.PushBack({ 673, 1157, 83, 78 });
	greyEnemyMeleeDown.PushBack({ 757, 1157, 83, 78 });
	greyEnemyMeleeDown.speed = 0.2f;

	blackSoldierDeath.PushBack({ 1, 1363, 53, 57 });
	blackSoldierDeath.PushBack({ 55, 1363, 53, 57 });
	blackSoldierDeath.PushBack({ 109, 1363, 53, 57 });
	blackSoldierDeath.PushBack({ 163, 1363, 53, 57 });
	blackSoldierDeath.PushBack({ 217, 1363, 53, 57 });
	blackSoldierDeath.PushBack({ 271, 1363, 53, 57 });
	blackSoldierDeath.PushBack({ 325, 1363, 53, 57 });
	blackSoldierDeath.speed = 0.1f;
	blackSoldierDeath.loop = false;

	idle.PushBack({ 137, 1739, 32, 50 });
	idle.PushBack({ 170, 1739, 32, 50 });
	idle.PushBack({ 203, 1739, 32, 50 });
	idle.PushBack({ 236, 1739, 32, 50 });
	idle.speed = 0.1f;

	shooting.PushBack({ 137, 1688, 32, 50 });
	shooting.PushBack({ 170, 1688, 32, 50 });
	shooting.PushBack({ 203, 1688, 32, 50 });
	shooting.speed = 0.1f;

	fogonazo.PushBack({ 1021, 1202, 36, 29 });
	fogonazo.PushBack({ 1058, 1202, 36, 29 });
	fogonazo.PushBack({ 1095, 1202, 36, 29 });

	currentAnim = &idle;

	collider = App->collisions->AddCollider({ 20, 20, 32, 50 }, Collider::Type::ENEMY, (Module*)App->enemies);
	collider2 = App->collisions->AddCollider({ 20, 20, 72, 75 }, Collider::Type::ENEMY_SHOT, (Module*)App->enemies);
	hp = 10;

}




void Enemy_BlackSoldier::Update()
{
	moveCooldown++;
	shootCooldown++;
	offsettexture1x = 0;
	offsettexture1y = 0;
	isMelee = false;


	int offsetx = 0;
	int offsety = 20;

	dx = (App->player->position.x + App->player->collider->rect.w / 2 - position.x - offsetx);
	dy = (App->player->position.y + App->player->collider->rect.h / 2 - position.y - offsety);


	if (Dircalculation(dx, dy) < 70 && deleting == false)
	{
		currentAnim = &greyEnemyMeleeDown;
		offsettexture1x = -22;
		offsettexture1y = -22;
		isMelee = true;
		shootCooldown = 0;
		collider2->SetPos(position.x - 15, position.y - 20);
	}

	if (isMelee == false && deleting == false)
	{
		currentAnim = &idle;
	}

	if (moveCooldown > 50 && isMelee == false && deleting == false)
	{
		if (position.x  - App->player->position.x < 0)
		{
			position.x++;
			if (moveCooldown > 100 || abs(position.x - App->player->position.x) < 5)
			{
				moveCooldown = 0;
			}
		}
		else
		{
			position.x--;
			if (moveCooldown > 100 || abs(position.x - App->player->position.x) < 5)
			{
				moveCooldown = 0;
			}
		}
	}

	if (shootCooldown > 90 && shootCooldown < 120 && isMelee == false && deleting == false)
	{
		currentAnim = &shooting;
	}

	if (shootCooldown > 120 && isMelee == false && deleting == false)
	{
	
		float dir = Dircalculation(dx, dy);

		float dirx = (dx * 1.5f / dir);
		float diry = (dy * 1.5f / dir);


		App->particles->AddParticle(App->particles->blueBullet, position.x + offsetx, position.y + offsety, 0, 2, false, Collider::Type::ENEMY_SHOT);
		
		currentAnim = &idle;
		shootCooldown = 0;
	}



	if (hp <= 0 && deleting == false)
	{
		pendingToDelete = false;
		deleting = true;
		currentAnim = &blackSoldierDeath;
		
	}

	if (currentAnim->HasFinished() == true)
	{
		die = true;
		collider2->pendingToDelete = true;
	}

	if (!isMelee && deleting == false)
	collider2->SetPos(2000, 2000);

	if (isMelee && deleting == true)
		collider2->SetPos(2000, 2000);
	collider->SetPos(position.x, position.y);
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
