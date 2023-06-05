#include "Enemy_RedBird.h"

#include "Module.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"
#include "stdio.h"


Enemy_RedBird::Enemy_RedBird(int x, int y) : Enemy(x, y)
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

	enemyWalking.PushBack({ 389, 1365, 34, 51 });
	enemyWalking.PushBack({ 424, 1365, 34, 51 });
	enemyWalking.PushBack({ 459, 1365, 34, 51 });
	enemyWalking.PushBack({ 494, 1365, 34, 51 });
	enemyWalking.PushBack({ 529, 1365, 34, 51 });
	enemyWalking.PushBack({ 564, 1365, 34, 51 });
	enemyWalking.PushBack({ 599, 1365, 34, 51 });
	enemyWalking.PushBack({ 634, 1365, 34, 51 });

	enemyDeathUpRight.PushBack({ 231, 1520, 55, 55 });
	enemyDeathUpRight.PushBack({ 287, 1520, 55, 55 });
	enemyDeathUpRight.PushBack({ 343, 1520, 55, 55 });
	enemyDeathUpRight.PushBack({ 399, 1520, 55, 55 });
	enemyDeathUpRight.PushBack({ 455, 1520, 55, 55 });
	enemyDeathUpRight.PushBack({ 511, 1520, 55, 55 });
	enemyDeathUpRight.PushBack({ 567, 1520, 55, 55 });
	enemyDeathUpRight.speed = 0.1f;
	enemyDeathUpRight.loop = false;

	enemyDeathUpLeft.PushBack({ 231, 1520, 55, 55 }, true);
	enemyDeathUpLeft.PushBack({ 287, 1520, 55, 55 }, true);
	enemyDeathUpLeft.PushBack({ 343, 1520, 55, 55 }, true);
	enemyDeathUpLeft.PushBack({ 399, 1520, 55, 55 }, true);
	enemyDeathUpLeft.PushBack({ 455, 1520, 55, 55 }, true);
	enemyDeathUpLeft.PushBack({ 511, 1520, 55, 55 }, true);
	enemyDeathUpLeft.PushBack({ 567, 1520, 55, 55 }, true);
	enemyDeathUpLeft.speed = 0.1f;
	enemyDeathUpLeft.loop = false;

	enemyDeathDownRight.PushBack({ 231, 1576, 55, 55 });
	enemyDeathDownRight.PushBack({ 287, 1576, 55, 55 });
	enemyDeathDownRight.PushBack({ 343, 1576, 55, 55 });
	enemyDeathDownRight.PushBack({ 399, 1576, 55, 55 });
	enemyDeathDownRight.PushBack({ 455, 1576, 55, 55 });
	enemyDeathDownRight.PushBack({ 511, 1576, 55, 55 });
	enemyDeathDownRight.PushBack({ 567, 1576, 55, 55 });
	enemyDeathDownRight.speed = 0.1f;
	enemyDeathDownRight.loop = false;

	enemyDeathDownLeft.PushBack({ 231, 1576, 55, 55 }, true);
	enemyDeathDownLeft.PushBack({ 287, 1576, 55, 55 }, true);
	enemyDeathDownLeft.PushBack({ 343, 1576, 55, 55 }, true);
	enemyDeathDownLeft.PushBack({ 399, 1576, 55, 55 }, true);
	enemyDeathDownLeft.PushBack({ 455, 1576, 55, 55 }, true);
	enemyDeathDownLeft.PushBack({ 511, 1576, 55, 55 }, true);
	enemyDeathDownLeft.PushBack({ 567, 1576, 55, 55 }, true);
	enemyDeathDownLeft.speed = 0.1f;
	enemyDeathDownLeft.loop = false;

	enemyDeathLeft.PushBack({ 231, 1632, 55, 55 });
	enemyDeathLeft.PushBack({ 287, 1632, 55, 55 });
	enemyDeathLeft.PushBack({ 343, 1632, 55, 55 });
	enemyDeathLeft.PushBack({ 399, 1632, 55, 55 });
	enemyDeathLeft.PushBack({ 455, 1632, 55, 55 });
	enemyDeathLeft.PushBack({ 511, 1632, 55, 55 });
	enemyDeathLeft.PushBack({ 567, 1632, 55, 55 });
	enemyDeathLeft.speed = 0.1f;
	enemyDeathLeft.loop = false;

	enemyDeathRight.PushBack({ 231, 1632, 55, 55 }, true);
	enemyDeathRight.PushBack({ 287, 1632, 55, 55 }, true);
	enemyDeathRight.PushBack({ 343, 1632, 55, 55 }, true);
	enemyDeathRight.PushBack({ 399, 1632, 55, 55 }, true);
	enemyDeathRight.PushBack({ 455, 1632, 55, 55 }, true);
	enemyDeathRight.PushBack({ 511, 1632, 55, 55 }, true);
	enemyDeathRight.PushBack({ 567, 1632, 55, 55 }, true);
	enemyDeathRight.speed = 0.1f;
	enemyDeathRight.loop = false;

	enemyRollRight.PushBack({ 269, 1688, 38, 53 });
	enemyRollRight.PushBack({ 308, 1688, 38, 53 });
	enemyRollRight.PushBack({ 347, 1688, 38, 53 });
	enemyRollRight.PushBack({ 386, 1688, 38, 53 });
	enemyRollRight.PushBack({ 425, 1688, 38, 53 });
	enemyRollRight.PushBack({ 464, 1688, 38, 53 });
	enemyRollRight.PushBack({ 503, 1688, 38, 53 });
	enemyRollRight.PushBack({ 542, 1688, 38, 53 });
	enemyRollRight.PushBack({ 581, 1688, 38, 53 });
	enemyRollRight.speed = 0.2f;

	enemyRollLeft.PushBack({ 269, 1742, 38, 53 });
	enemyRollLeft.PushBack({ 308, 1742, 38, 53 });
	enemyRollLeft.PushBack({ 347, 1742, 38, 53 });
	enemyRollLeft.PushBack({ 386, 1742, 38, 53 });
	enemyRollLeft.PushBack({ 425, 1742, 38, 53 });
	enemyRollLeft.PushBack({ 464, 1742, 38, 53 });
	enemyRollLeft.PushBack({ 503, 1742, 38, 53 });
	enemyRollLeft.PushBack({ 542, 1742, 38, 53 });
	enemyRollLeft.PushBack({ 581, 1742, 38, 53 });
	enemyRollLeft.speed = 0.2f;

	enemyRollDownPointingLeft.PushBack({ 317, 741, 65, 43 });
	enemyRollDownPointingLeft.PushBack({ 317, 785, 65, 43 });
	enemyRollDownPointingLeft.PushBack({ 317, 829, 65, 43 });
	enemyRollDownPointingLeft.PushBack({ 317, 873, 65, 43 });
	enemyRollDownPointingLeft.PushBack({ 317, 917, 65, 43 });
	enemyRollDownPointingLeft.PushBack({ 317, 961, 65, 43 });
	enemyRollDownPointingLeft.PushBack({ 317, 1005, 65, 43 });
	enemyRollDownPointingLeft.PushBack({ 317, 1049, 65, 43 });
	enemyRollDownPointingLeft.speed = 0.2f;

	enemyRollDownPointingRight.PushBack({ 317, 741, 65, 43 }, true);
	enemyRollDownPointingRight.PushBack({ 317, 785, 65, 43 }, true);
	enemyRollDownPointingRight.PushBack({ 317, 829, 65, 43 }, true);
	enemyRollDownPointingRight.PushBack({ 317, 873, 65, 43 }, true);
	enemyRollDownPointingRight.PushBack({ 317, 917, 65, 43 }, true);
	enemyRollDownPointingRight.PushBack({ 317, 961, 65, 43 }, true);
	enemyRollDownPointingRight.PushBack({ 317, 1005, 65, 43 }, true);
	enemyRollDownPointingRight.PushBack({ 317, 1049, 65, 43 }, true);
	enemyRollDownPointingRight.speed = 0.2f;

	enemyRollUpPointingLeft.PushBack({ 317, 1049, 65, 43 });
	enemyRollUpPointingLeft.PushBack({ 317, 1005, 65, 43 });
	enemyRollUpPointingLeft.PushBack({ 317, 961, 65, 43 });
	enemyRollUpPointingLeft.PushBack({ 317, 917, 65, 43 });
	enemyRollUpPointingLeft.PushBack({ 317, 873, 65, 43 });
	enemyRollUpPointingLeft.PushBack({ 317, 829, 65, 43 });
	enemyRollUpPointingLeft.PushBack({ 317, 785, 65, 43 });
	enemyRollUpPointingLeft.PushBack({ 317, 741, 65, 43 });
	enemyRollUpPointingLeft.speed = 0.2f;

	enemyRollUpPointingRight.PushBack({ 317, 1049, 65, 43 }, true);
	enemyRollUpPointingRight.PushBack({ 317, 1005, 65, 43 }, true);
	enemyRollUpPointingRight.PushBack({ 317, 961, 65, 43 }, true);
	enemyRollUpPointingRight.PushBack({ 317, 917, 65, 43 }, true);
	enemyRollUpPointingRight.PushBack({ 317, 873, 65, 43 }, true);
	enemyRollUpPointingRight.PushBack({ 317, 829, 65, 43 }, true);
	enemyRollUpPointingRight.PushBack({ 317, 785, 65, 43 }, true);
	enemyRollUpPointingRight.PushBack({ 317, 741, 65, 43 }, true);
	enemyRollUpPointingRight.speed = 0.2f;

	enemyBurning.PushBack({ 800, 1792, 59, 63 });
	enemyBurning.PushBack({ 860, 1792, 59, 63 });
	enemyBurning.PushBack({ 920, 1792, 59, 63 });
	enemyBurning.PushBack({ 980, 1792, 59, 63 });
	enemyBurning.PushBack({ 1040, 1792, 59, 63 });
	enemyBurning.PushBack({ 1100, 1792, 59, 63 });
	enemyBurning.PushBack({ 1160, 1792, 59, 63 });
	enemyBurning.PushBack({ 1220, 1792, 59, 63 });
	enemyBurning.PushBack({ 1280, 1792, 59, 63 });
	enemyBurning.PushBack({ 1340, 1792, 59, 63 });
	enemyBurning.PushBack({ 1400, 1792, 59, 63 });
	enemyBurning.PushBack({ 1460, 1792, 59, 63 });
	enemyBurning.PushBack({ 1520, 1792, 59, 63 });
	enemyBurning.PushBack({ 1580, 1792, 59, 63 });
	enemyBurning.PushBack({ 1640, 1792, 59, 63 });
	enemyBurning.PushBack({ 1700, 1792, 59, 63 });
	enemyBurning.speed = 0.1f;
	enemyBurning.loop = false;

	hp = 1;

	currentAnim = &flyAnim;

	collider = App->collisions->AddCollider({0, 0, 43, 43}, Collider::Type::ENEMY, (Module*)App->enemies);
}


void Enemy_RedBird::Update()
{

	shootCooldown++;
	spawn++;

	dx = (App->player->position.x + App->player->collider->rect.w / 2 - position.x - offsetshootx);
	dy = (App->player->position.y + App->player->collider->rect.h / 2 - position.y - offsetshooty);

	dx2 = (App->player->position.x + App->player->collider->rect.w / 2 - position.x);
	dy2 = (App->player->position.y + App->player->collider->rect.h / 2 - position.y);

	if (spawn < spawnlimit)
		switch (enemyMode)
		{
		case 0:
			spawnlimit = 50;
			currentAnim = &enemyRollRight;
		
			position.x++;


			break;
		case 1:
			spawnlimit = 50;
			currentAnim = &enemyRollLeft;
		
			position.x--;
			break;
		case 2:
			spawnlimit = 50;
			currentAnim = &enemyRollDownPointingRight;
			position.y++;
			break;
		case 3:
			spawnlimit = 50;
			currentAnim = &enemyRollDownPointingLeft;
			position.y++;
			break;

		}

	if (hp <= 0 && deleting == false && spawn > spawnlimit)
	{
 		pendingToDelete = false;
		deleting = true;
		

	
		if (!isOnFire)
			switch (GetTargetDir(dx2, dy2))
			{
			case LEFT:
				currentAnim = &enemyDeathRight;

				break;
			case RIGHT:
				currentAnim = &enemyDeathLeft;

				break;
			case DOWN:
				currentAnim = &enemydeath2;

				break;
			case UP:
				currentAnim = &enemyDeathDownLeft;
				break;
			case DOWNLEFT:

				currentAnim = &enemyDeathRight;
				break;
			case DOWNRIGHT:
				currentAnim = &enemyDeathUpLeft;

				break;
			case UPLEFT:

				currentAnim = &enemyDeathDownRight;
				break;
			case UPRIGHT:
				currentAnim = &enemyDeathDownLeft;

				break;
			}
		else
			currentAnim = &enemyBurning;
	}

	if (currentAnim->HasFinished() == true && spawn > spawnlimit)
	{
		die = true;
	}

	if (shootCooldown > 233 && deleting == false && spawn > spawnlimit)
	{

		
		float dir = Dircalculation(dx, dy);

		float dirx = (dx * 1.5f / dir);
		float diry = (dy * 1.5f / dir);


		App->particles->AddParticle(App->particles->laser, position.x + offsetshootx, position.y + offsetshooty, dirx, diry, false, Collider::Type::ENEMY_SHOT);

		App->particles->AddParticle(App->particles->laser, position.x + offsetshootx, position.y + offsetshooty, dirx, diry, false, Collider::Type::ENEMY_SHOT, 20);
		shootCooldown = 0;
	}

	if (deleting == false && spawn > spawnlimit)
	switch (GetTargetDir(dx2, dy2))
	{
	case LEFT:
		currentAnim = &enemyshot2left;
		offsetshootx = -2;
		offsetshooty = 15;
		break;
	case RIGHT:
		currentAnim = &enemyshot2right;
		offsetshootx = 40;
		offsetshooty = 15;
		break;
	case DOWN:
		currentAnim = &enemyshot2down;
		offsetshootx = 25;
		offsetshooty = 35;
		break;
	case UP:
		currentAnim = &enemyshot2up;
		offsetshootx = 20;
		break;
	case DOWNLEFT:
		currentAnim = &enemyshot2downleft;
		offsetshootx = 5;
		offsetshooty = 22;
		break;
	case DOWNRIGHT:
		currentAnim = &enemyshot2rightdown;
		offsetshootx = 30;
		offsetshooty = 30;
		break;
	case UPLEFT:
		currentAnim = &enemyshot2upleft;
		offsetshootx = 5;
		offsetshooty = -1;
		break;
	case UPRIGHT:
		currentAnim = &enemyshot2rightup;
		offsetshootx = 35;
		offsetshooty = 10;
		break;
	}

	if (spawn > spawnlimit)
		collider->SetPos(position.x + 10, position.y);
	else
		collider->SetPos(-1300, 5465);


	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}