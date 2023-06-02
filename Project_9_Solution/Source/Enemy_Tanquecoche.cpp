#include "Enemy_Tanquecoche.h"
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


Enemy_Tanquecoche::Enemy_Tanquecoche(int x, int y) : Enemy(x, y)
{

	enemydeath1.PushBack({ 713, 473, 70, 64 });
	enemydeath1.PushBack({ 784, 473, 70, 64 });
	enemydeath1.PushBack({ 855, 473, 70, 64 });
	enemydeath1.speed = 0.1f;
	enemydeath1.loop = true;

	enemyshot1down.PushBack({ 905, 547, 64, 42 });
	enemyshot1down.PushBack({ 970, 547, 64, 42 });
	enemyshot1down.PushBack({ 1035, 547, 64, 42 });
	enemyshot1down.speed = 0.1f;

	enemyshot1rightdown.PushBack({ 905, 590, 64, 42 }, true);
	enemyshot1rightdown.PushBack({ 970, 590, 64, 42 }, true);
	enemyshot1rightdown.PushBack({ 1035, 590, 64, 42 }, true);
	enemyshot1rightdown.speed = 0.1f;

	enemyshot1right.PushBack({ 1100, 590, 64, 42 }, true);
	enemyshot1right.PushBack({ 1165, 590, 64, 42 }, true);
	enemyshot1right.PushBack({ 1230, 590, 64, 42 }, true);
	enemyshot1right.speed = 0.1f;

	enemyshot1rightup.PushBack({ 905, 633, 64, 42 }, true);
	enemyshot1rightup.PushBack({ 970, 633, 64, 42 }, true);
	enemyshot1rightup.PushBack({ 1035, 633, 64, 42 }, true);
	enemyshot1rightup.speed = 0.1f;

	enemyshot1up.PushBack({ 1295, 633, 64, 42 });
	enemyshot1up.PushBack({ 1360, 633, 64, 42 });
	enemyshot1up.PushBack({ 1425, 633, 64, 42 });
	enemyshot1up.speed = 0.1f;

	enemyshot1upleft.PushBack({ 905, 633, 64, 42 });
	enemyshot1upleft.PushBack({ 970, 633, 64, 42 });
	enemyshot1upleft.PushBack({ 1035, 633, 64, 42 });
	enemyshot1upleft.speed = 0.1f;

	enemyshot1left.PushBack({ 1100, 590, 64, 42 });
	enemyshot1left.PushBack({ 1165, 590, 64, 42 });
	enemyshot1left.PushBack({ 1230, 590, 64, 42 });
	enemyshot1left.speed = 0.1f;

	enemyshot1downleft.PushBack({ 905, 590, 64, 42 });
	enemyshot1downleft.PushBack({ 970, 590, 64, 42 });
	enemyshot1downleft.PushBack({ 1035, 590, 64, 42 });
	enemyshot1downleft.speed = 0.1f;

	missileLauncher.PushBack({ 6, 1694, 52, 55 });
	missileLauncher.PushBack({ 59, 1694, 52, 55 });

	missileLauncherBrokenBody.PushBack({ 6, 1750, 52, 55 });
	missileLauncherBrokenTop.PushBack({ 67, 1750, 44, 50 });

	missileLauncherDownLeft.PushBack({ 6, 1806, 44, 51 });
	missileLauncherDownRight.PushBack({ 6, 1806, 44, 51 }, true);
	missileLauncherLeft.PushBack({ 51, 1806, 44, 51 });
	missileLauncherRight.PushBack({ 51, 1750, 44, 51 }, true);
	missileLauncherTopLeft.PushBack({ 96, 1750, 44, 51 });
	missileLauncherTopRight.PushBack({ 96, 1750, 44, 51 }, true);

	//POR AHORA CUT CONTENT
	//enemyshot1rightdowndiagonal.PushBack({ 905, 590, 64, 42 }, true);
	//enemyshot1downleftdiagonal.PushBack({ 905, 590, 64, 42 });
	//enemyshot1rightupdiagonal.PushBack({ 905, 633, 64, 42 }, true);
	//enemyshot1upleftdiagonal.PushBack({ 905, 633, 64, 42 });

	hp = 10;


	collider = App->collisions->AddCollider({ 0, 0, 52, 75 }, Collider::Type::ENEMY, (Module*)App->enemies);
	currentAnim = &missileLauncherLeft;
	currentAnim2 = &missileLauncher;
}


void Enemy_Tanquecoche::Update()
{
	shootCooldown++;

	if (enemyMode == 1) 
	{
		test = 10;
	}
	dx = (App->player->position.x + App->player->collider->rect.w / 2 - position.x);
	dy = (App->player->position.y + App->player->collider->rect.h / 2 - position.y);

	if (pendingToDelete == true && deleting == false)
	{
		pendingToDelete = false;
		deleting = true;
	}

	if (deleting == true)
	{
		deathTimer++;
	}

	if (deathTimer > 60)
	{
		pendingToDelete = true;
	}

	if (shootCooldown > test && deleting == false)
	{


		float dir = Dircalculation(dx, dy);

		float dirx = (dx * 1.5f / dir);
		float diry = (dy * 1.5f / dir);


		App->particles->AddParticle(App->particles->missileRight, position.x, position.y, dirx, diry, false, Collider::Type::MISSILE);
		shootCooldown = 0;
	}

	if (deleting == false)
	{
		offsettexture1x = 0;
		offsettexture1y = -26;
	}



	/*if (deleting == false)
		switch (GetTargetDir(dx, dy))
		{
		case LEFT:
			currentAnim = &missileLauncherLeft;
			offsettexture1y = -5;
		
			break;
		case RIGHT:
			currentAnim = &missileLauncherRight;
			offsettexture1y = -5;
		case DOWNLEFT:
			currentAnim = &missileLauncherDownLeft;
			offsettexture1y = -5;
			break;
		case DOWNRIGHT:
			currentAnim = &missileLauncherDownRight;
			offsettexture1y = -5;
			break;
		case UPLEFT:
			currentAnim = &missileLauncherTopLeft;
			offsettexture1y = -5;
			break;
		case UPRIGHT:
			currentAnim = &missileLauncherTopRight;
			offsettexture1y = -5;
			break;
		}*/

	if (deleting == true)
	{
		offsettexture1y -= 3;
		deathTimer++;
	}

	if (deathTimer >= 60)
		pendingToDelete = true;

	collider->SetPos(position.x, position.y - 20);



	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
