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

	hp = 1;

	currentAnim = &flyAnim;

	collider = App->collisions->AddCollider({ 0, 0, 43, 43 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

float Dircalculation4(float Dx, float Dy)
{
	float dir = sqrt(Dx * Dx + Dy * Dy);
	return dir;


}

float abss4(float value)
{
	if (value < 0)
		return value * -1;
	else
		return value;
}

int GetTargetDir4(float dx, float dy)
{
	float diagonal = abss4(dx / dy);


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
		if (abss4(dx) > abss4(dy))
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

void Enemy_Bazooka::Update()
{

	shootCooldown++;

	dx = (App->player->position.x + App->player->collider->rect.w / 2 - position.x);
	dy = (App->player->position.y + App->player->collider->rect.h / 2 - position.y);

	if (pendingToDelete == true && deleting == false)
	{
		pendingToDelete = false;
		deleting = true;
		currentAnim = &enemydeath2;
	}

	if (currentAnim->HasFinished() == true)
	{
		pendingToDelete = true;
	}

	if (shootCooldown > 233 && deleting == false)
	{


		float dir = Dircalculation4(dx, dy);

		float dirx = (dx * 1.5f / dir);
		float diry = (dy * 1.5f / dir);


		App->particles->AddParticle(App->particles->laser, position.x, position.y, dirx, diry, false, Collider::Type::MISSILE);

		shootCooldown = 0;
	}

	if (deleting == false)
		switch (GetTargetDir4(dx, dy))
		{
		case LEFT:
			currentAnim = &enemyshot2left;
			break;
		case RIGHT:
			currentAnim = &enemyshot2right;
			break;
		case DOWN:
			currentAnim = &enemyshot2down;
			break;
		case UP:
			currentAnim = &enemyshot2up;
			break;
		case DOWNLEFT:
			currentAnim = &enemyshot2downleft;
			break;
		case DOWNRIGHT:
			currentAnim = &enemyshot2rightdown;
			break;
		case UPLEFT:
			currentAnim = &enemyshot2upleft;
			break;
		case UPRIGHT:
			currentAnim = &enemyshot2rightup;
			break;
		}

	collider->SetPos(position.x, position.y);

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
