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

	missileLauncherBody.PushBack({ 6, 1694, 52, 55 }, true);
	missileLauncherBody.PushBack({ 59, 1694, 52, 55 },true);

	missileLauncherBrokenBody.PushBack({ 6, 1750, 52, 55 });
	missileLauncherBrokenTop.PushBack({ 67, 1750, 44, 50 });

	missileLauncherDownLeft.PushBack({ 96, 1750, 44, 51 });

	missileLauncherDownRight.PushBack({ 96, 1750, 44, 51 }, true);

	missileLauncherRight.PushBack({ 51, 1806, 44, 51 });

	missileLauncherLeft.PushBack({ 51, 1806, 44, 51 }, true);
	


	//POR AHORA CUT CONTENT
	//enemyshot1rightdowndiagonal.PushBack({ 905, 590, 64, 42 }, true);
	//enemyshot1downleftdiagonal.PushBack({ 905, 590, 64, 42 });
	//enemyshot1rightupdiagonal.PushBack({ 905, 633, 64, 42 }, true);
	//enemyshot1upleftdiagonal.PushBack({ 905, 633, 64, 42 });

	hp = 10;


	collider = App->collisions->AddCollider({ 0, 0, 52, 75 }, Collider::Type::ENEMY, (Module*)App->enemies);

}


void Enemy_Tanquecoche::Update()
{
	shootCooldown++; 

	switch (enemyMode) {
	case 0:
		currentAnim = &missileLauncherLeft;
		currentAnim2 = &missileLauncherBody;
		
		break;
	case 1:
		currentAnim = &missileLauncherRight;
		currentAnim2 = &missileLauncher;
		offsettexture2x = 10;
		break;
	}
	dx = (App->player->position.x + App->player->collider->rect.w / 2 - position.x);
	dy = (App->player->position.y + App->player->collider->rect.h / 2 - position.y);

	if (hp <= 0 && deleting == false)
	{
		pendingToDelete = false;
		deleting = true;
		currentAnim = &missileLauncherBrokenBody;
		currentAnim2 = &missileLauncherBrokenTop;
		App->particles->AddParticle(App->particles->explosionDefault, position.x + 15, position.y + 10, 0, 0, false, Collider::Type::NONE);
		App->particles->AddParticle(App->particles->explosionDefault, position.x + 25, position.y + 25, 0, 0, false, Collider::Type::NONE, 10);
		App->particles->AddParticle(App->particles->explosionDefault, position.x + 35, position.y, 0, 0, false, Collider::Type::NONE, 25);
		App->particles->AddParticle(App->particles->explosionDefault, position.x + -12, position.y - 50, 0, 0, false, Collider::Type::NONE, 40);
		App->particles->AddParticle(App->particles->explosionDefault, position.x + -12, position.y - 50, 0, -2, false, Collider::Type::NONE, 12);
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

		switch (enemyMode) {

		case 1:
			App->particles->AddParticle(App->particles->missileRight, position.x, position.y, dirx, diry, false, Collider::Type::MISSILE);
			shootCooldown = 0;
			break;
		case 0:
			App->particles->AddParticle(App->particles->missileLeft, position.x, position.y, dirx, diry, false, Collider::Type::MISSILE);
			shootCooldown = 0;
		}
	}

	if (deleting == false)
	{
		offsettexture1x = 8;
		offsettexture1y = -26;
	}

	if (deleting == true)
	{
		offsettexture1y -= 3;
		deathTimer++;
	}

	if (deathTimer >= 60)
		die = true;

	collider->SetPos(position.x, position.y - 20);



	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
