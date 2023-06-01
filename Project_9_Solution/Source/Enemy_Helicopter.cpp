#include "Enemy_Helicopter.h"
#include "Module.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"
#include "stdio.h"
#include "math.h"
#include "SceneLevel1.h"

Enemy_Helicopter::Enemy_Helicopter(int x, int y) : Enemy(x, y)
{

	boxidle.PushBack({ 686, 1798, 108, 80 });
	
	helicopterFight.PushBack({ 1515, 1095, 110, 98 });
	helicopterFight.PushBack({ 1626, 1095, 110, 98 });
	helicopterFight.PushBack({ 1737, 1095, 110, 98 });
	helicopterFight.speed = 0.1f;

	helicopterBullet.PushBack({ 767, 539, 4, 4 });
	helicopterBullet.PushBack({ 767, 543, 4, 4 });

	fogonazoLeft.PushBack({ 772, 539, 27, 29 });
	fogonazoLeft.PushBack({ 800, 539, 27, 29 });
	fogonazoLeft.PushBack({ 828, 539, 27, 29 });

	fogonazoRight.PushBack({ 772, 539, 27, 29 }, true);
	fogonazoRight.PushBack({ 800, 539, 27, 29 }, true);
	fogonazoRight.PushBack({ 828, 539, 27, 29 }, true);

	fogonazoDown.PushBack({ 772, 569, 27, 29 });
	fogonazoDown.PushBack({ 800, 569, 27, 29 });
	fogonazoDown.PushBack({ 828, 569, 27, 29 });
	
	currentAnim = &helicopterFight;

	collider = App->collisions->AddCollider({ 20, 20, 108, 80}, Collider::Type::ENEMY, (Module*)App->enemies);
	hp = 40;

}




void Enemy_Helicopter::Update()
{
	moveCooldown++;
	shootCooldown++;
	startCooldown++;
	int offsetx = 54;
	int offsety = 80;
		
	dx = (App->player->position.x  + App->player->collider->rect.w / 2 - position.x - offsetx);
	dy = (App->player->position.y + App->player->collider->rect.h / 2 - position.y - offsety);

	if ( startCooldown < 120) 
	{
		position.y++;
	}

	if (moveCooldown > 250 && startCooldown > 120)
	{
		if (position.x + 50 - App->player->position.x < 0)
		{
			position.x++;
			if (abs(position.x + 50 - App->player->position.x) < 5 ) 
			{
				moveCooldown = 0;
			}
		}
		else
		{
			position.x--;
			if (abs(position.x + 50 - App->player->position.x) < 5)
			{
				moveCooldown = 0;
			}
		}
	}

	if (shootCooldown > 120 && startCooldown > 120)
	{

		float dir = Dircalculation(dx, dy);
		
		float dirx = (dx * 1.5f / dir);
		float diry = (dy * 1.5f / dir);


		App->particles->AddParticle(App->particles->laser, position.x + offsetx , position.y +offsety, dirx * 2, diry * 2, false, Collider::Type::ENEMY_SHOT);
		App->particles->AddParticle(App->particles->laser, position.x + offsetx, position.y + offsety, dirx * 2, diry * 2, false, Collider::Type::ENEMY_SHOT, 10);
		App->particles->AddParticle(App->particles->laser, position.x + offsetx, position.y + offsety, dirx * 2, diry * 2, false, Collider::Type::ENEMY_SHOT, 20);
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

	if (startCooldown > 120)
		collider->SetPos(position.x, position.y);
	else
		collider->SetPos(5000, 5000);
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
