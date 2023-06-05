#include "Enemy_Structures.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"

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
	medicTentBroken.speed = 0.1f;

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
	
	tower2almost.PushBack({ 1918, 1125, 64, 125 });
	tower2Breaking.PushBack({ 1983, 1125, 64, 125 });
	tower2Breaking.loop = false;
	tower2Breaking.speed = 0.1f;


	lightMGenemyDown.PushBack({ 987, 1971, 36, 41 });

	lightMGenemyDownRight.PushBack({ 1024, 1971, 36, 41 });

	lightMGenemyDownLeft.PushBack({ 1061, 1971, 36,41 });


	dissapear.PushBack({ 0,0,0,0 });


	

	
	hp = 24;
	hpold = hp;
}

void Enemy_Structures::Update()
{
	shootCooldown++;

	if (deleting == true) 
	{
		dissapearCooldown++;
	}

	dx = (App->player->position.x + App->player->collider->rect.w / 2 - position.x);
	dy = (App->player->position.y + App->player->collider->rect.h / 2 - position.y);

	if (start == false)
	{
		switch (enemyMode)
		{
		case 0:
			currentAnim = &medicTent;
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

		collider->SetPos(position.x, position.y);
		if (hp <= 0 && deleting == false)
		{
			pendingToDelete = false;
			deleting = true;
			currentAnim = &medicTentBroken;
			App->particles->AddParticle(App->particles->explosionDefault, position.x + 15, position.y + 100, 0, 0, false, Collider::Type::NONE);
			App->particles->AddParticle(App->particles->explosionDefault, position.x + 15, position.y + 110, 0, 0, false, Collider::Type::NONE, 10);
			App->particles->AddParticle(App->particles->explosionDefault, position.x + 25, position.y + 120, 0, 0, false, Collider::Type::NONE, 20);
			App->particles->AddParticle(App->particles->explosionDefault, position.x + 35, position.y, 90, 0, false, Collider::Type::NONE, 40);
			App->particles->AddParticle(App->particles->explosionDefault, position.x + 15, position.y + 100, 0, 0, false, Collider::Type::NONE, 45);
			App->particles->AddParticle(App->particles->explosionDefault, position.x + -12, position.y + 140, 0, 0, false, Collider::Type::NONE, 30);
		}

		if (dissapearCooldown > 40)
		{
			die = true;
		}
		break;
	case 1:
		offsettexture1x = 15;
		offsettexture1y = 5;

		collider->SetPos(position.x, position.y);
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
		}
			if (shootCooldown > 150 && deleting == false)
			{
				float dir = Dircalculation(dx, dy);

				float dirx = (dx * 1.5f / dir);
				float diry = (dy * 1.5f / dir);

				App->particles->AddParticle(App->particles->laser, position.x, position.y, dirx, diry, false, Collider::Type::ENEMY_SHOT);
				shootCooldown = 0;
			}

			if (hp <= 0 && deleting == false)
			{
				pendingToDelete = false;
				deleting = true;
				currentAnim2 = &towerBreaking;
				currentAnim = &dissapear;
				App->particles->AddParticle(App->particles->explosionDefault, position.x, position.y, 0, 0, false, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->explosionDefault, position.x, position.y +40, 0, 0, false, Collider::Type::NONE, 10);
				App->particles->AddParticle(App->particles->explosionDefault, position.x+10, position.y +80, 0, 0, false, Collider::Type::NONE, 20);
				App->particles->AddParticle(App->particles->explosionDefault, position.x+45, position.y +110, 0, 0, false, Collider::Type::NONE,30);
				App->particles->AddParticle(App->particles->explosionDefault, position.x + 0, position.y + 120, 0, 0, false, Collider::Type::NONE, 40);
				App->particles->AddParticle(App->particles->explosionDefault, position.x + 25, position.y + 140, 0, 0, false, Collider::Type::NONE, 50);
			}

			if (dissapearCooldown > 80)
			{
				die = true;
			}
			break;
	case 2:
		offsettexture1x = 15;
		offsettexture1y = 15;

		
		randomoffset += 2;

		dx = (App->player->position.x + App->player->collider->rect.w / 2 - position.x - 15);
		dy = (App->player->position.y + App->player->collider->rect.h / 2 - position.y - 15);

		collider->SetPos(position.x, position.y);
		if (deleting == false)
		{
			switch (GetTargetDir(dx, dy))
			{
		
			case RIGHT:
				currentAnim = &enemyshot1right;
				break;
			case DOWN:
				currentAnim = &lightMGenemyDownRight;
				break;
			case DOWNLEFT:
				currentAnim = &lightMGenemyDownLeft;
				break;
			case DOWNRIGHT:
				currentAnim = &lightMGenemyDown;
				break;
			}
		}
			if (shootCooldown > 150 && deleting == false)
			{


				float dir = Dircalculation(dx, dy);

				float dirx = (dx * 1.5f / dir);
				float diry = (dy * 1.5f / dir);


				App->particles->AddParticle(App->particles->laser, position.x , position.y , dirx, diry, false, Collider::Type::ENEMY_SHOT);
				shootCooldown = 0;
			}

			if (randomoffset > 40)
			{
				randomoffset = 0;
			}
			if (hp < 8)
			{
				currentAnim2 = &tower2almost;
			}
			if (hpold > hp)
			{
				hpold = hp;
				App->particles->AddParticle(App->particles->dust, position.x + randomoffset, position.y + 30, 0, 0, false, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->dust, position.x + randomoffset, position.y + 80, 0, 0, false, Collider::Type::NONE);
			}

			if (hp <= 0 && deleting == false)
			{
				pendingToDelete = false;
				deleting = true;
				currentAnim2 = &tower2Breaking;
				currentAnim = &dissapear;
				App->particles->AddParticle(App->particles->explosionDefault, position.x + 5, position.y + 20, 0, 0, false, Collider::Type::NONE, 0);
				App->particles->AddParticle(App->particles->explosionDefault, position.x + 25, position.y + 50, 0, 0, false, Collider::Type::NONE, 10);
				App->particles->AddParticle(App->particles->explosionDefault, position.x , position.y + 45, 0, 0, false, Collider::Type::NONE, 20);
				App->particles->AddParticle(App->particles->explosionDefault, position.x , position.y + 45, 0, 0, false, Collider::Type::NONE, 30);
				App->particles->AddParticle(App->particles->explosionDefault, position.x + 5, position.y + 85, 0, 0, false, Collider::Type::NONE, 40);
				App->particles->AddParticle(App->particles->explosionDefault, position.x + 25, position.y + 20, 0, 0, false, Collider::Type::NONE, 50);
				App->particles->AddParticle(App->particles->explosionDefault, position.x , position.y + 50, 0, 0, false, Collider::Type::NONE, 60);
			}

			if (dissapearCooldown > 80)
			{
				die = true;
			}
			break;
	}

		
		collider->SetPos(position.x, position.y);
		// Call to the base class. It must be called at the end
		// It will update the collider depending on the position
		Enemy::Update();

	
}