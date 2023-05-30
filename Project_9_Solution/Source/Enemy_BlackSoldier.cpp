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

	helicopterArriving.PushBack({ 1515, 1056, 55, 38 });
	helicopterArriving.PushBack({ 1571, 1056, 55, 38 });

	helicopterFight.PushBack({ 1515, 1095, 110, 98 });
	helicopterFight.PushBack({ 1626, 1095, 110, 98 });
	helicopterFight.PushBack({ 1737, 1095, 110, 98 });

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

	currentAnim = &greyEnemyMeleeDown;

	collider = App->collisions->AddCollider({ 20, 20, 83, 78 }, Collider::Type::ENEMY, (Module*)App->enemies);
	hp = 1;

}




void Enemy_BlackSoldier::Update()
{
	moveCooldown++;
	shootCooldown++;

	int offsetx = 54;
	int offsety = 80;

	dx = (App->player->position.x + App->player->collider->rect.w / 2 - position.x - offsetx);
	dy = (App->player->position.y + App->player->collider->rect.h / 2 - position.y - offsety);

	if (moveCooldown > 50)
	{
		if (position.x + 50 - App->player->position.x < 0)
		{
			position.x++;
			if (moveCooldown > 100 || abs(position.x + 50 - App->player->position.x) < 5)
			{
				moveCooldown = 0;
			}
		}
		else
		{
			position.x--;
			if (moveCooldown > 100 || abs(position.x + 50 - App->player->position.x) < 5)
			{
				moveCooldown = 0;
			}
		}
	}

	if (shootCooldown > 120)
	{
	
		float dir = Dircalculation(dx, dy);

		float dirx = (dx * 1.5f / dir);
		float diry = (dy * 1.5f / dir);


		App->particles->AddParticle(App->particles->blueBullet, position.x + offsetx, position.y + offsety, 0, 2, false, Collider::Type::ENEMY_SHOT);
		
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

	collider->SetPos(position.x, position.y);
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
