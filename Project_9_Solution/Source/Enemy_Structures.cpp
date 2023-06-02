#include "Enemy_Structures.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"

Enemy_Structures::Enemy_Structures(int x, int y) : Enemy(x, y)
{

	medicTent.PushBack({ 1160, 1601, 76, 190 });
	medicTent.PushBack({ 1237, 1601, 76, 190 });
	medicTent.PushBack({ 1314, 1601, 76, 190 });
	medicTent.PushBack({ 1391, 1601, 76, 190 });
	medicTent.loop = true;
	medicTent.speed = 0.1f;

	medicTentBroken.PushBack({ 1314, 1410, 76, 190 });
	medicTentBroken.PushBack({ 1391, 1410, 76, 190 });
	medicTentBroken.loop = false;
	medicTentBroken.speed = 0.07f;

	tower.PushBack({ 1468, 1302, 86, 195 });

	enemyshot1down.PushBack({ 20, 600, 43, 47 });
	enemyshot1rightdown.PushBack({ 63, 600, 43, 47 });
	enemyshot1right.PushBack({ 106, 600, 43, 47 });
	enemyshot1rightup.PushBack({ 149, 600, 43, 47 });
	enemyshot1up.PushBack({ 192, 600, 43, 47 });
	enemyshot1upleft.PushBack({ 235, 600, 43, 47 });
	enemyshot1left.PushBack({ 278, 600, 43, 47 });
	enemyshot1downleft.PushBack({ 321, 600, 43, 47 });

	towerBreaking.PushBack({ 1555, 1302, 86, 195 });
	towerBreaking.PushBack({ 1642, 1302, 86, 195 });
	towerBreaking.PushBack({ 1729, 1302, 86, 195 });
	towerBreaking.PushBack({ 1816, 1302, 86, 195 });
	towerBreaking.PushBack({ 1468, 1498, 86, 195 });
	towerBreaking.PushBack({ 1555, 1498, 86, 195 });
	towerBreaking.PushBack({ 1642, 1498, 86, 195 });
	towerBreaking.PushBack({ 1729, 1498, 86, 195 });
	towerBreaking.PushBack({ 1816, 1498, 86, 195 });
	towerBreaking.loop = false;
	towerBreaking.speed = 0.1f;

	tower2.PushBack({ 1853, 1125, 64, 125 });
	
	tower2Breaking.PushBack({ 1918, 1125, 64, 125 });
	tower2Breaking.PushBack({ 1983, 1125, 64, 125 });
	tower2Breaking.loop = false;
	tower2Breaking.speed = 0.1f;


	currentAnim = &medicTent;

	hp = 1;

}

void Enemy_Structures::Update()
{

	dx = (App->player->position.x + App->player->collider->rect.w / 2 - position.x);
	dy = (App->player->position.y + App->player->collider->rect.h / 2 - position.y);

	if (start == false)
	{
		switch (enemyMode)
		{
		case 0:
			currentAnim2 = &medicTent;
			collider = App->collisions->AddCollider({ 20, 20, 76, 190 }, Collider::Type::ENEMY, (Module*)App->enemies);
			break;
		case 1:
			currentAnim2 = &tower;

			collider = App->collisions->AddCollider({ 20, 20, 86, 195 }, Collider::Type::ENEMY, (Module*)App->enemies);
			break;
		case 2:
			currentAnim2 = &tower2;
			collider = App->collisions->AddCollider({ 20, 20, 64, 125 }, Collider::Type::ENEMY, (Module*)App->enemies);
			break;
		}
		start = true;
	}


	switch (enemyMode)
	{
	case 0:
		if (pendingToDelete == true && deleting == false)
		{
			pendingToDelete = false;
			deleting = true;
			currentAnim2 = &medicTentBroken;
		}

		if (currentAnim2->HasFinished() == true)
		{
			pendingToDelete = true;
		}
		break;
	case 1:
		if (deleting == false)
		{
			switch (GetTargetDir(dx, dy))
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

			if (pendingToDelete == true && deleting == false)
			{
				pendingToDelete = false;
				deleting = true;
				currentAnim2 = &towerBreaking;
			}

			if (currentAnim2->HasFinished() == true)
			{
				pendingToDelete = true;
			}
			break;
	case 2:
		if (pendingToDelete == true && deleting == false)
		{
			pendingToDelete = false;
			deleting = true;
			currentAnim2 = &tower2Breaking;
		}

		if (currentAnim2->HasFinished() == true)
		{
			pendingToDelete = true;
		}
		break;
		}

	}
		collider->SetPos(position.x, position.y);
		// Call to the base class. It must be called at the end
		// It will update the collider depending on the position
		Enemy::Update();
	
}