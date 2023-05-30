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

	enemyDeathUpLeft.PushBack({ 231, 1520, 55, 55 }, true);
	enemyDeathUpLeft.PushBack({ 287, 1520, 55, 55 }, true);
	enemyDeathUpLeft.PushBack({ 343, 1520, 55, 55 }, true);
	enemyDeathUpLeft.PushBack({ 399, 1520, 55, 55 }, true);
	enemyDeathUpLeft.PushBack({ 455, 1520, 55, 55 }, true);
	enemyDeathUpLeft.PushBack({ 511, 1520, 55, 55 }, true);
	enemyDeathUpLeft.PushBack({ 567, 1520, 55, 55 }, true);

	enemyDeathDownRight.PushBack({ 231, 1576, 55, 55 });
	enemyDeathDownRight.PushBack({ 287, 1576, 55, 55 });
	enemyDeathDownRight.PushBack({ 343, 1576, 55, 55 });
	enemyDeathDownRight.PushBack({ 399, 1576, 55, 55 });
	enemyDeathDownRight.PushBack({ 455, 1576, 55, 55 });
	enemyDeathDownRight.PushBack({ 511, 1576, 55, 55 });
	enemyDeathDownRight.PushBack({ 567, 1576, 55, 55 });

	enemyDeathDownLeft.PushBack({ 231, 1576, 55, 55 }, true);
	enemyDeathDownLeft.PushBack({ 287, 1576, 55, 55 }, true);
	enemyDeathDownLeft.PushBack({ 343, 1576, 55, 55 }, true);
	enemyDeathDownLeft.PushBack({ 399, 1576, 55, 55 }, true);
	enemyDeathDownLeft.PushBack({ 455, 1576, 55, 55 }, true);
	enemyDeathDownLeft.PushBack({ 511, 1576, 55, 55 }, true);
	enemyDeathDownLeft.PushBack({ 567, 1576, 55, 55 }, true);

	enemyDeathLeft.PushBack({ 231, 1632, 55, 55 });
	enemyDeathLeft.PushBack({ 287, 1632, 55, 55 });
	enemyDeathLeft.PushBack({ 343, 1632, 55, 55 });
	enemyDeathLeft.PushBack({ 399, 1632, 55, 55 });
	enemyDeathLeft.PushBack({ 455, 1632, 55, 55 });
	enemyDeathLeft.PushBack({ 511, 1632, 55, 55 });
	enemyDeathLeft.PushBack({ 567, 1632, 55, 55 });

	enemyDeathRight.PushBack({ 231, 1632, 55, 55 }, true);
	enemyDeathRight.PushBack({ 287, 1632, 55, 55 }, true);
	enemyDeathRight.PushBack({ 343, 1632, 55, 55 }, true);
	enemyDeathRight.PushBack({ 399, 1632, 55, 55 }, true);
	enemyDeathRight.PushBack({ 455, 1632, 55, 55 }, true);
	enemyDeathRight.PushBack({ 511, 1632, 55, 55 }, true);
	enemyDeathRight.PushBack({ 567, 1632, 55, 55 }, true);

	enemyRollRight.PushBack({ 269, 1688, 38, 53 });
	enemyRollRight.PushBack({ 308, 1688, 38, 53 });
	enemyRollRight.PushBack({ 347, 1688, 38, 53 });
	enemyRollRight.PushBack({ 386, 1688, 38, 53 });
	enemyRollRight.PushBack({ 425, 1688, 38, 53 });
	enemyRollRight.PushBack({ 464, 1688, 38, 53 });
	enemyRollRight.PushBack({ 503, 1688, 38, 53 });
	enemyRollRight.PushBack({ 542, 1688, 38, 53 });
	enemyRollRight.PushBack({ 581, 1688, 38, 53 });

	enemyRollLeft.PushBack({ 269, 1742, 38, 53 });
	enemyRollLeft.PushBack({ 308, 1742, 38, 53 });
	enemyRollLeft.PushBack({ 347, 1742, 38, 53 });
	enemyRollLeft.PushBack({ 386, 1742, 38, 53 });
	enemyRollLeft.PushBack({ 425, 1742, 38, 53 });
	enemyRollLeft.PushBack({ 464, 1742, 38, 53 });
	enemyRollLeft.PushBack({ 503, 1742, 38, 53 });
	enemyRollLeft.PushBack({ 542, 1742, 38, 53 });
	enemyRollLeft.PushBack({ 581, 1742, 38, 53 });

	hp = 1;

	currentAnim = &flyAnim;

	collider = App->collisions->AddCollider({0, 0, 43, 43}, Collider::Type::ENEMY, (Module*)App->enemies);
}


void Enemy_RedBird::Update()
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

		
		float dir = Dircalculation(dx, dy);

		float dirx = (dx * 1.5f / dir);
		float diry = (dy * 1.5f / dir);


		App->particles->AddParticle(App->particles->laser, position.x, position.y, dirx, diry, false, Collider::Type::ENEMY_SHOT);

		App->particles->AddParticle(App->particles->laser, position.x , position.y, dirx, diry, false, Collider::Type::ENEMY_SHOT, 20);
		shootCooldown = 0;
	}

	if (deleting == false)
	switch (GetTargetDir(dx, dy))
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
