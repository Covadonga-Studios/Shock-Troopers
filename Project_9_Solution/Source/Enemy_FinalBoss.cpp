#include "Enemy_FinalBoss.h"
#include "Module.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"
#include "stdio.h"
#include "math.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"


Enemy_FinalBoss::Enemy_FinalBoss(int x, int y) : Enemy(x, y)
{

	cannonDown.PushBack({ 1383, 696, 107, 74 });

	cannonDownLeft.PushBack({ 1383, 772, 107, 74 }, true);

	cannonDownRight.PushBack({ 1383, 772, 107, 74 }, true);

	cannonLeft.PushBack({ 1383, 848, 107, 74 }, true);

	cannonRight.PushBack({ 1383, 848, 107, 74 }, true);

	bulletDown.PushBack({ 445, 1888, 48, 48 });
	bulletDown.PushBack({ 494, 1888, 48, 48 });
	bulletDown.PushBack({ 543, 1888, 48, 48 });
	bulletDown.PushBack({ 592, 1888, 48, 48 });
	bulletDown.PushBack({ 641, 1888, 48, 48 });
	bulletDown.PushBack({ 690, 1888, 48, 48 });

	bulletDownLeft.PushBack({ 445, 1937, 48, 48 });
	bulletDownLeft.PushBack({ 494, 1937, 48, 48 });
	bulletDownLeft.PushBack({ 543, 1937, 48, 48 });
	bulletDownLeft.PushBack({ 592, 1937, 48, 48 });
	bulletDownLeft.PushBack({ 641, 1937, 48, 48 });
	bulletDownLeft.PushBack({ 690, 1937, 48, 48 });

	bulletDownRight.PushBack({ 445, 1937, 48, 48 }, true);
	bulletDownRight.PushBack({ 494, 1937, 48, 48 }, true);
	bulletDownRight.PushBack({ 543, 1937, 48, 48 }, true);
	bulletDownRight.PushBack({ 592, 1937, 48, 48 }, true);
	bulletDownRight.PushBack({ 641, 1937, 48, 48 }, true);
	bulletDownRight.PushBack({ 690, 1937, 48, 48 }, true);
	
	bulletLeft.PushBack({ 445, 1986, 48, 48 });
	bulletLeft.PushBack({ 494, 1986, 48, 48 });
	bulletLeft.PushBack({ 543, 1986, 48, 48 });
	bulletLeft.PushBack({ 592, 1986, 48, 48 });
	bulletLeft.PushBack({ 641, 1986, 48, 48 });
	bulletLeft.PushBack({ 690, 1986, 48, 48 });

	bulletRight.PushBack({ 445, 1986, 48, 48 }, true);
	bulletRight.PushBack({ 494, 1986, 48, 48 }, true);
	bulletRight.PushBack({ 543, 1986, 48, 48 }, true);
	bulletRight.PushBack({ 592, 1986, 48, 48 }, true);
	bulletRight.PushBack({ 641, 1986, 48, 48 }, true);
	bulletRight.PushBack({ 690, 1986, 48, 48 }, true);

	tankMissileRight.PushBack({ 739, 2006, 50, 28 });
	tankMissileRight.PushBack({ 790, 2006, 50, 28 });
	tankMissileRight.PushBack({ 841, 2006, 50, 28 });
	tankMissileRight.PushBack({ 892, 2006, 50, 28 });
	tankMissileRight.PushBack({ 943, 2006, 50, 28 });
	tankMissileRight.PushBack({ 994, 2006, 50, 28 });
	tankMissileRight.PushBack({ 1045, 2006, 50, 28 });
	tankMissileRight.PushBack({ 1096, 2006, 50, 28 });

	tankMissileLeft.PushBack({ 739, 2006, 50, 28 }, true);
	tankMissileLeft.PushBack({ 790, 2006, 50, 28 }, true);
	tankMissileLeft.PushBack({ 841, 2006, 50, 28 }, true);
	tankMissileLeft.PushBack({ 892, 2006, 50, 28 }, true);
	tankMissileLeft.PushBack({ 943, 2006, 50, 28 }, true);
	tankMissileLeft.PushBack({ 994, 2006, 50, 28 }, true);
	tankMissileLeft.PushBack({ 1045, 2006, 50, 28 }, true);
	tankMissileLeft.PushBack({ 1096, 2006, 50, 28 }, true);

	turretDown.PushBack({ 4, 1060, 42, 27 });

	turretDownLeft.PushBack({ 48, 1060, 42, 27});

	turretDownRight.PushBack({ 48, 1060, 42, 27 }, true);

	turretLeft.PushBack({ 92, 1060, 42, 27 });

	turretRight.PushBack({ 92, 1060, 42, 27 }, true);


	//POR AHORA CUT CONTENT
	//enemyshot1rightdowndiagonal.PushBack({ 905, 590, 64, 42 }, true);
	//enemyshot1downleftdiagonal.PushBack({ 905, 590, 64, 42 });
	//enemyshot1rightupdiagonal.PushBack({ 905, 633, 64, 42 }, true);
	//enemyshot1upleftdiagonal.PushBack({ 905, 633, 64, 42 });

	hp = 10;


	collider = App->collisions->AddCollider({ 0, 0, 70, 63 }, Collider::Type::ENEMY, (Module*)App->enemies);
	currentAnim = &enemydeath1;
	currentAnim2 = &enemydeath1;
}


void Enemy_FinalBoss::Update()
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


		App->particles->AddParticle(App->particles->laser, position.x, position.y, dirx, diry, false, Collider::Type::ENEMY_SHOT);
		shootCooldown = 0;
	}


	if (deleting == false)
		switch (GetTargetDir(dx, dy))
		{
		case LEFT:
			currentAnim = &turretLeft;
			currentAnim2 = &cannonLeft;
			break;
		case RIGHT:
			currentAnim = &turretRight;
			currentAnim2 = &cannonRight;
			break;
		case DOWN:
			currentAnim = &turretDown;
			currentAnim2 = &cannonDown;
			break;
		case UP:
			currentAnim = &turretDown;
			currentAnim2 = &cannonDown;
			break;
		case DOWNLEFT:
			currentAnim = &turretDownLeft;
			currentAnim2 = &cannonDownLeft;
			break;
		case DOWNRIGHT:
			currentAnim = &turretDownRight;
			currentAnim2 = &cannonDownRight;
			break;
		case UPLEFT:
			currentAnim = &turretDown;
			currentAnim2 = &cannonDown;
			break;
		case UPRIGHT:

			currentAnim = &turretDown;
			currentAnim2 = &cannonDown;
			break;
		}

	collider->SetPos(position.x, position.y);

	//currentAnim2 = &enemydeath1;


	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
