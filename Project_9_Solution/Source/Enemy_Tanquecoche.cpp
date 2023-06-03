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
