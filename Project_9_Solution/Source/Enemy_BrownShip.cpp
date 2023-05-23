#include "Enemy_BrownShip.h"
#include "Module.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"
#include "stdio.h"
#include "math.h"


Enemy_BrownShip::Enemy_BrownShip(int x, int y) : Enemy(x, y)
{
	fly.PushBack({5,72,21,22});
	enemydeath1.PushBack({ 20, 720, 41, 53 });
	enemydeath1.PushBack({ 61, 720, 41, 53 });
	enemydeath1.PushBack({ 102, 720, 41, 53 });
	enemydeath1.PushBack({ 143, 720, 41, 53 });
	enemydeath1.PushBack({ 184, 720, 41, 53 });
	enemydeath1.PushBack({ 225, 720, 41, 53 });
	enemydeath1.PushBack({ 266, 720, 41, 53 });
	enemydeath1.speed = 0.1f;
	enemydeath1.loop = false;
	currentAnim = &fly;
	
	enemyshot1down.PushBack({ 20, 600, 43, 47 });
	enemyshot1rightdown.PushBack({ 63, 600, 43, 47 });
	enemyshot1right.PushBack({ 106, 600, 43, 47 });
	enemyshot1rightup.PushBack({ 149, 600, 43, 47 });
	enemyshot1up.PushBack({ 192, 600, 43, 47 });
	enemyshot1upleft.PushBack({ 235, 600, 43, 47 });
	enemyshot1left.PushBack({ 278, 600, 43, 47 });
	enemyshot1downleft.PushBack({ 321, 600, 43, 47 });

	enemyBurning.PushBack({ 1133, 962, 60, 74 });
	enemyBurning.PushBack({ 1194, 962, 60, 74 });
	enemyBurning.PushBack({ 1255, 962, 60, 74 });
	enemyBurning.PushBack({ 1316, 962, 60, 74 });
	enemyBurning.PushBack({ 1377, 962, 60, 74 });
	enemyBurning.PushBack({ 1438, 962, 60, 74 });
	enemyBurning.PushBack({ 1133, 1037, 60, 74 });
	enemyBurning.PushBack({ 1194, 1037, 60, 74 });
	enemyBurning.PushBack({ 1255, 1037, 60, 74 });
	enemyBurning.PushBack({ 1316, 1037, 60, 74 });
	enemyBurning.PushBack({ 1377, 1037, 60, 74 });
	enemyBurning.PushBack({ 1438, 1037, 60, 74 });
	enemyBurning.PushBack({ 1133, 1112, 60, 74 });
	enemyBurning.PushBack({ 1194, 1112, 60, 74 });
	enemyBurning.PushBack({ 1255, 1112, 60, 74 });
	enemyBurning.PushBack({ 1316, 1112, 60, 74 });
	enemyBurning.PushBack({ 1377, 1112, 60, 74 });

	enemyRunning.PushBack({ 881, 971, 39, 55 });
	enemyRunning.PushBack({ 921, 971, 39, 55 });
	enemyRunning.PushBack({ 961, 971, 39, 55 });
	enemyRunning.PushBack({ 1001, 971, 39, 55 });

	enemyStopping.PushBack({ 821, 1026, 39, 55 });
	enemyStopping.PushBack({ 921, 1026, 39, 55 });
	enemyStopping.PushBack({ 961, 1026, 39, 55 });
	enemyStopping.PushBack({ 1001, 1026, 39, 55 });
	enemyStopping.PushBack({ 1041, 1026, 39, 55 });
	enemyStopping.PushBack({ 1081, 1026, 39, 55 });

	enemyLooking.PushBack({ 1625, 304, 33, 50 });
	enemyLooking.PushBack({ 1659, 304, 33, 50 });
	enemyLooking.PushBack({ 1693, 304, 33, 50 });
	enemyLooking.PushBack({ 1728, 304, 33, 50 });
	enemyLooking.PushBack({ 1763, 304, 33, 50 });
	enemyLooking.PushBack({ 1625, 355, 33, 50 });
	enemyLooking.PushBack({ 1659, 355, 33, 50 });
	enemyLooking.PushBack({ 1693, 355, 33, 50 });
	enemyLooking.PushBack({ 1728, 355, 33, 50 });
	enemyLooking.PushBack({ 1763, 355, 33, 50 });
	enemyLooking.PushBack({ 1625, 406, 66, 50 });
	enemyLooking.PushBack({ 1693, 406, 33, 50 });
	enemyLooking.PushBack({ 1728, 406, 33, 50 });


	hp = 1;

	
	collider = App->collisions->AddCollider({0, 0, 43, 43}, Collider::Type::ENEMY, (Module*)App->enemies);
}

float Dircalculation(float Dx, float Dy) 
{
	float dir = sqrt(Dx * Dx + Dy * Dy);
	return dir;
}

float abss(float value) 
{
	if (value < 0)
		return value * -1;
	else
		return value;
}

int GetTargetDir(float dx,float dy)
{
	float diagonal = abss(dx / dy);
	
	
	if (diagonal >= 0.5f && diagonal <= 1.5f) 
	{
		if (dx > 0 && dy > 0) 
			return DOWNRIGHT;
		else if (dx > 0 && dy < 0) 
			return UPRIGHT;
		else if (dx < 0 && dy > 0)
			return DOWNLEFT;
		else 
			return UPLEFT;
	}
	else 
	{
		if (abss(dx) > abss(dy)) 
		{
			if (dx >= 0)
				return RIGHT;
			else
				return LEFT;
			
		}
		else 
		{
			if (dy >= 0)
				return DOWN;
			else 
				return UP;
		}
	}
	
	
}

void Enemy_BrownShip::Update()
{
	shootCooldown++;

	dx = (App->player->position.x + App->player->collider->rect.w / 2 - position.x);
	dy = (App->player->position.y + App->player->collider->rect.h / 2 - position.y);

	if (pendingToDelete == true && deleting == false) 
	{
		pendingToDelete = false;
		deleting = true;
		currentAnim = &enemydeath1;
	}

	if (currentAnim->HasFinished() == true)
	{
		pendingToDelete = true;
	}

	if (shootCooldown > 150 && deleting == false)
	{

		 
		float dir = Dircalculation(dx, dy);

		float dirx = (dx * 1.5f / dir);
		float diry = (dy * 1.5f / dir);
		
		
		App->particles->AddParticle(App->particles->laser, position.x, position.y,dirx, diry, false, Collider::Type::ENEMY_SHOT);
		shootCooldown = 0;
	}


	if (deleting == false)
	switch (GetTargetDir(dx,dy))
	{
	case LEFT:
		currentAnim = &enemyshot1left;
		break;
	case RIGHT:
		currentAnim = &enemyshot1right;
		break;
	case DOWN:
		currentAnim = &enemyshot1down;
		break;
	case UP:
		currentAnim = &enemyshot1up;
		break;
	case DOWNLEFT:
		currentAnim = &enemyshot1downleft;
		break;
	case DOWNRIGHT:
		currentAnim = &enemyshot1rightdown;
		break;
	case UPLEFT:
		currentAnim = &enemyshot1upleft;
		break;
	case UPRIGHT:
		currentAnim = &enemyshot1rightup;
		break;
	}

	collider->SetPos(position.x, position.y);

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
