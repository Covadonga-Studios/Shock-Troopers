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

	path.PushBack({-1.0f, -0.5f}, 100);
	path.PushBack({-1.0f, 0.5f}, 80);
	path.PushBack({-1.0f, 1.0f}, 80);

	

	
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
		
		
		App->particles->AddParticle(App->particles->laser, position.x, position.y,dirx, diry, Collider::Type::ENEMY_SHOT);
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

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
