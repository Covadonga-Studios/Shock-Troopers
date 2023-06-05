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

	cannonDownLeft.PushBack({ 1383, 772, 107, 74 });

	cannonDownRight.PushBack({ 1383, 772, 107, 74 }, true);

	cannonLeft.PushBack({ 1383, 848, 107, 74 });

	cannonRight.PushBack({ 1383, 848, 107, 74 }, true);

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

	baseFinalBoss.PushBack({3,1525,109,162});
	baseFinalBoss.PushBack({ 114,1525,109,162 });
	baseFinalBoss.speed = 0.1f;
	//POR AHORA CUT CONTENT
	//enemyshot1rightdowndiagonal.PushBack({ 905, 590, 64, 42 }, true);
	//enemyshot1downleftdiagonal.PushBack({ 905, 590, 64, 42 });
	//enemyshot1rightupdiagonal.PushBack({ 905, 633, 64, 42 }, true);
	//enemyshot1upleftdiagonal.PushBack({ 905, 633, 64, 42 });

	hp = 600;


	collider = App->collisions->AddCollider({ 0, 0, 109, 162 }, Collider::Type::ENEMY, (Module*)App->enemies);
	currentAnim = &enemydeath1;
	currentAnim2 = &enemydeath1;
	currentAnim3 = &baseFinalBoss;
}


void Enemy_FinalBoss::Update()
{
	shootCooldown++;
	shootCooldown2++;
	shootCooldown3++;
	shootCooldown4++;

	offsettexture2x =0;
	offsettexture2y =0;
	offsettexture1x =0;
	offsettexture1y =0;
	int offsetx = 50;
	int offsety = 50;

	dx = (App->player->position.x + App->player->collider->rect.w / 2 - position.x - offsetx);
	dy = (App->player->position.y + App->player->collider->rect.h / 2 - position.y - offsety);

	if (hp <= 0 && deleting == false)
	{
		pendingToDelete = false;
		deleting = true;
		currentAnim = &enemydeath1;
		App->particles->AddParticle(App->particles->explosionDefault, position.x, position.y, 0, 0, false, Collider::Type::NONE);
		App->particles->AddParticle(App->particles->explosionDefault, position.x +40, position.y, 0, 0, false, Collider::Type::NONE, 10);
		App->particles->AddParticle(App->particles->explosionDefault, position.x +80, position.y, 0, 0, false, Collider::Type::NONE, 20);

		App->particles->AddParticle(App->particles->explosionDefault, position.x +40, position.y +50, 0, 0, false, Collider::Type::NONE, 30);
		App->particles->AddParticle(App->particles->explosionDefault, position.x +80, position.y + 50, 0, 0, false, Collider::Type::NONE,40);
		App->particles->AddParticle(App->particles->explosionDefault, position.x, position.y + 50, 0, 0, false, Collider::Type::NONE, 50);

		App->particles->AddParticle(App->particles->explosionDefault, position.x, position.y + 100, 0, 0, false, Collider::Type::NONE, 60);
		App->particles->AddParticle(App->particles->explosionDefault, position.x + 40, position.y + 100, 0, 0, false, Collider::Type::NONE,70);
		App->particles->AddParticle(App->particles->explosionDefault, position.x + 80, position.y + 100, 0, 0, false, Collider::Type::NONE,80);

		App->player->bigkill = 1;
	}

	if (deleting == true) {
		deathTimer++;
	}

	if (deathTimer >= 90)
	{
		pendingToDelete = true;
		
	}

	if (deleting == false)
		switch (GetTargetDir(dx, dy))
		{
		case LEFT:
			currentAnim = &turretLeft;
			currentAnim2 = &cannonLeft;
			offsettexture2x = 3;
			offsettexture2y = 20;
			offsettexture1x = 50;
			offsettexture1y = 45;
			break;
		case RIGHT:
			currentAnim = &turretRight;
			currentAnim2 = &cannonRight;
			offsettexture2x = 3;
			offsettexture2y = 20;
			offsettexture1x = 30;
			offsettexture1y = 25;
			break;
		case DOWN:
			currentAnim = &turretDown;
			currentAnim2 = &cannonDown;
			offsettexture2x = 3;
			offsettexture2y = 20;
			offsettexture1x = 50;
			offsettexture1y = 35;
			break;
		case UP:
			currentAnim = &turretDown;
			currentAnim2 = &cannonDown;
			offsettexture2x = 3;
			offsettexture2y = 20;
			break;
		case DOWNLEFT:
			currentAnim = &turretDownLeft;
			currentAnim2 = &cannonDownLeft;
			offsettexture2x = 3;
			offsettexture2y = 20;
			offsettexture1x = 50;
			offsettexture1y = 45;
			break;
		case DOWNRIGHT:
			currentAnim = &turretDownRight;
			currentAnim2 = &cannonDownRight;
			offsettexture2x = 3;
			offsettexture2y = 20;
			offsettexture1x = 50;
			offsettexture1y = 25;
			break;
		case UPLEFT:
			currentAnim = &turretDown;
			currentAnim2 = &cannonDown;
			offsettexture2x = 3;
			offsettexture2y = 20;
			break;
		case UPRIGHT:

			currentAnim = &turretDown;
			currentAnim2 = &cannonDown;
			offsettexture2x = 3;
			offsettexture2y = 20;
			break;
		}

	if (shootCooldown > 150 && deleting == false)
	{
		float dir = Dircalculation(dx, dy);

		float dirx = (dx * 1.5f / dir);
		float diry = (dy * 1.5f / dir);

		App->particles->AddParticle(App->particles->laser, position.x + offsettexture1x, position.y + offsettexture1y, dirx, diry, false, Collider::Type::ENEMY_SHOT);
		shootCooldown = 0;
	}

	if (shootCooldown2 > 300 && deleting == false)
	{
		float dir = Dircalculation(dx, dy);

		float dirx = (dx * 1.5f / dir);
		float diry = (dy * 1.5f / dir);
		switch (GetTargetDir(dx, dy))
		{
		case LEFT:
			App->particles->AddParticle(App->particles->finalBulletLeft, position.x + offsettexture1x, position.y + offsettexture1y, dirx, diry, false, Collider::Type::ENEMY_SHOT);
			break;
		case RIGHT:
			App->particles->AddParticle(App->particles->finalBulletRight, position.x + offsettexture1x, position.y + offsettexture1y, dirx, diry, false, Collider::Type::ENEMY_SHOT);
			break;
		case DOWN:
			App->particles->AddParticle(App->particles->finalBulletDown, position.x + offsettexture1x, position.y + offsettexture1y, dirx, diry, false, Collider::Type::ENEMY_SHOT);
			break;
		case UP:
			App->particles->AddParticle(App->particles->finalBulletDown, position.x + offsettexture1x, position.y + offsettexture1y, dirx, diry, false, Collider::Type::ENEMY_SHOT);
			break;
		case DOWNLEFT:
			App->particles->AddParticle(App->particles->finalBulletDownLeft, position.x + offsettexture1x, position.y + offsettexture1y, dirx, diry, false, Collider::Type::ENEMY_SHOT);
			break;
		case DOWNRIGHT:
			App->particles->AddParticle(App->particles->finalBulletDownRight, position.x + offsettexture1x, position.y + offsettexture1y, dirx, diry, false, Collider::Type::ENEMY_SHOT);
			break;
		case UPLEFT:
			App->particles->AddParticle(App->particles->finalBulletDown, position.x + offsettexture1x, position.y + offsettexture1y, dirx, diry, false, Collider::Type::ENEMY_SHOT);
			break;
		case UPRIGHT:
			App->particles->AddParticle(App->particles->finalBulletDown, position.x + offsettexture1x, position.y + offsettexture1y, dirx, diry, false, Collider::Type::ENEMY_SHOT);
			break;
		}

	
		shootCooldown2 = 0;
	}
	if (shootCooldown3 > 500 && deleting == false)
	{
		App->particles->AddParticle(App->particles->missileDown, App->render->camera.x + 50, App->render->camera.y, 0, 2, false, Collider::Type::MISSILE);

		App->particles->AddParticle(App->particles->missileDown, App->render->camera.x + 100, App->render->camera.y, 0, 2, false, Collider::Type::MISSILE);

		App->particles->AddParticle(App->particles->missileDown, App->render->camera.x + 150, App->render->camera.y, 0, 2, false, Collider::Type::MISSILE);

		App->particles->AddParticle(App->particles->missileDown, App->render->camera.x + 200, App->render->camera.y, 0, 2, false, Collider::Type::MISSILE);

		shootCooldown3 = 0;
	}

	if (shootCooldown4 > 350) 
	{
		float dir = Dircalculation(dx, dy);

		float dirx = (dx * 1.5f / dir);
		float diry = (dy * 1.5f / dir);


			App->particles->AddParticle(App->particles->laser, position.x + offsettexture1x, position.y + offsettexture1y, (dirx - 1) * 1.5f , diry , false, Collider::Type::ENEMY_SHOT);

			App->particles->AddParticle(App->particles->laser, position.x + offsettexture1x, position.y + offsettexture1y, dirx , diry + 1, false, Collider::Type::ENEMY_SHOT);

			App->particles->AddParticle(App->particles->laser, position.x + offsettexture1x, position.y + offsettexture1y, dirx , diry + 1.5f, false, Collider::Type::ENEMY_SHOT);

			App->particles->AddParticle(App->particles->laser, position.x + offsettexture1x, position.y + offsettexture1y, dirx + 2, diry , false, Collider::Type::ENEMY_SHOT);

			shootCooldown4 = 0;
	}
	collider->SetPos(position.x, position.y);

	//currentAnim2 = &enemydeath1;


	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
