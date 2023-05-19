#include "Enemy_Tank.h"
#include "Module.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"
#include "stdio.h"
#include "math.h"


Enemy_Tank::Enemy_Tank(int x, int y) : Enemy(x, y)
{
	
		enemydeath1.PushBack({ 713, 473, 70, 64 });
		enemydeath1.PushBack({ 784, 473, 70, 64 });
		enemydeath1.PushBack({ 855, 473, 70, 64 });
		enemydeath1.speed = 0.1f;
		enemydeath1.loop = true;
	
	enemyshot1down.PushBack({ 20, 600, 43, 47 });
	enemyshot1rightdown.PushBack({ 63, 600, 43, 47 });
	enemyshot1right.PushBack({ 106, 600, 43, 47 });
	enemyshot1rightup.PushBack({ 149, 600, 43, 47 });
	enemyshot1up.PushBack({ 192, 600, 43, 47 });
	enemyshot1upleft.PushBack({ 235, 600, 43, 47 });
	enemyshot1left.PushBack({ 278, 600, 43, 47 });
	enemyshot1downleft.PushBack({ 321, 600, 43, 47 });

	hp = 10;

	collider = App->collisions->AddCollider({ 0, 0, 43, 43 }, Collider::Type::ENEMY, (Module*)App->enemies);
	currentAnim = &enemydeath1;
}

//float Dircalculation3(float Dx, float Dy)
//{
//	float dir = sqrt(Dx * Dx + Dy * Dy);
//	return dir;
//}
//
//float abss3(float value)
//{
//	if (value < 0)
//		return value * -1;
//	else
//		return value;
//}
//
//int GetTargetDir3(float dx, float dy)
//{
//	float diagonal = abss3(dx / dy);
//
//
//	if (diagonal >= 0.5f && diagonal <= 1.5f)
//	{
//		if (dx > 0 && dy > 0)
//			return DOWNRIGHT;
//		else if (dx > 0 && dy < 0)
//			return UPRIGHT;
//		else if (dx < 0 && dy > 0)
//			return DOWNLEFT;
//		else
//			return UPLEFT;
//	}
//	else
//	{
//		if (abss3(dx) > abss3(dy))
//		{
//			if (dx >= 0)
//				return RIGHT;
//			else
//				return LEFT;
//
//		}
//		else
//		{
//			if (dy >= 0)
//				return DOWN;
//			else
//				return UP;
//		}
//	}
//
//
//}

void Enemy_Tank::Update()
{
	//shootCooldown++;

	//dx = (App->player->position.x + App->player->collider->rect.w / 2 - position.x);
	//dy = (App->player->position.y + App->player->collider->rect.h / 2 - position.y);

	//if (pendingToDelete == true && deleting == false)
	//{
	//	pendingToDelete = false;
	//	deleting = true;
	//	currentAnim = &enemydeath1;
	//}

	//if (currentAnim->HasFinished() == true)
	//{
	//	pendingToDelete = true;
	//}

	//if (shootCooldown > 150 && deleting == false)
	//{


	//	float dir = Dircalculation3(dx, dy);

	//	float dirx = (dx * 1.5f / dir);
	//	float diry = (dy * 1.5f / dir);


	//	App->particles->AddParticle(App->particles->laser, position.x, position.y, dirx, diry, false, Collider::Type::ENEMY_SHOT);
	//	shootCooldown = 0;
	//}


	//if (deleting == false)
	//	switch (GetTargetDir3(dx, dy))
	//	{
	//	case LEFT:
	//		currentAnim = &enemyshot1left;
	//		break;
	//	case RIGHT:
	//		currentAnim = &enemyshot1right;
	//		break;
	//	case DOWN:
	//		currentAnim = &enemyshot1down;
	//		break;
	//	case UP:
	//		currentAnim = &enemyshot1up;
	//		break;
	//	case DOWNLEFT:
	//		currentAnim = &enemyshot1downleft;
	//		break;
	//	case DOWNRIGHT:
	//		currentAnim = &enemyshot1rightdown;
	//		break;
	//	case UPLEFT:
	//		currentAnim = &enemyshot1upleft;
	//		break;
	//	case UPRIGHT:
	//		currentAnim = &enemyshot1rightup;
	//		break;
	//	}

	collider->SetPos(position.x, position.y);

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
