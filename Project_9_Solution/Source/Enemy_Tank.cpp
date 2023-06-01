#include "Enemy_Tank.h"
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


Enemy_Tank::Enemy_Tank(int x, int y) : Enemy(x, y)
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


void Enemy_Tank::Update()
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


	offsettexture1x = 0;
	offsettexture1y = 0;
	if (deleting == false)
		switch (GetTargetDir(dx, dy))
		{
		case LEFT:
			currentAnim = &enemyshot1left;
			offsettexture1x = -10;
			offsettexture1y = -11;
			break;
		case RIGHT:
			currentAnim = &enemyshot1right;
			offsettexture1x = 15;
			offsettexture1y = -11;
			break;
		case DOWN:
			currentAnim = &enemyshot1down;
			offsettexture1x = 3;
			offsettexture1y = 3;
			break;
		case UP:
			currentAnim = &enemyshot1up;
			offsettexture1x = 3;
			offsettexture1y = -12;
			break;
		case DOWNLEFT:
			currentAnim = &enemyshot1downleft;
			offsettexture1x = -5;
			offsettexture1y = -1;
			break;
		case DOWNRIGHT:
			currentAnim = &enemyshot1rightdown;
			offsettexture1x = 10;
			offsettexture1y = -3;
			break;
		case UPLEFT:
			currentAnim = &enemyshot1upleft;
			offsettexture1x = 2;
			offsettexture1y = -9;
			break;
		case UPRIGHT:
			currentAnim = &enemyshot1rightup;
			offsettexture1x = 4;
			offsettexture1y = -9;
			break;
		}

	collider->SetPos(position.x, position.y);
	
	currentAnim2 = &enemydeath1;


	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
