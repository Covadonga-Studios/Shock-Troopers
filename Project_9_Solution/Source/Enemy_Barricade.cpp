#include "Enemy_Barricade.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"

Enemy_Barricade::Enemy_Barricade(int x, int y) : Enemy(x, y)
{


	barricade.PushBack({ 619, 1244, 97, 42 });

	barricadedestroy.PushBack({ 717, 1244, 97, 42 });

	peekyDownRight.PushBack({ 1020, 1231, 33, 28 });

	peekyDown.PushBack({ 1054, 1231, 33, 28 });

	peekyDownLeft.PushBack({ 1088, 1231, 33, 28 });
	
	enemydeath1.PushBack({ 20, 720, 41, 53 });
	enemydeath1.PushBack({ 61, 720, 41, 53 });
	enemydeath1.PushBack({ 102, 720, 41, 53 });
	enemydeath1.PushBack({ 143, 720, 41, 53 });
	enemydeath1.PushBack({ 184, 720, 41, 53 });
	enemydeath1.PushBack({ 225, 720, 41, 53 });
	enemydeath1.PushBack({ 266, 720, 41, 53 });
	enemydeath1.speed = 0.1f;
	enemydeath1.loop = false;

	//CHECKEAR
	lightMGenemyDown.PushBack({ 987, 1971, 36, 41 });
	//CHECKEAR
	lightMGenemyDownRight.PushBack({ 1024, 1971, 36, 41 });
	//CHECKEAR
	lightMGenemyDownLeft.PushBack({ 1061, 1971, 36,41 });
	//CHECKEAR

	currentAnim = &peekyDown;
	currentAnim2 = &barricade;

	offsettexture1x = 30;

	collider = App->collisions->AddCollider({ 20, 20, 97, 42 }, Collider::Type::ENEMY, (Module*)App->enemies);
	hp = 24;
	hpold = hp;

}

void Enemy_Barricade::Update()
{

	shootCooldown++;
	randomoffset += 2;
	int offsetx = 35;
	int offsety = 10;

	dx = (App->player->position.x + App->player->collider->rect.w / 2 - position.x - offsetx);
	dy = (App->player->position.y + App->player->collider->rect.h / 2 - position.y - offsety);

	if (pendingToDelete == true && deleting == false)
	{
		pendingToDelete = false;
		deleting = true;
		
		currentAnim = &enemydeath1;
		offsettexture1y = -45;
		App->particles->AddParticle(App->particles->explosionDefault, position.x , position.y , 0,0, false, Collider::Type::NONE);
		App->particles->AddParticle(App->particles->explosionDefault, position.x + 60, position.y, 0, 0, false, Collider::Type::NONE);
	}

	if (randomoffset > 60) 
	{
		randomoffset = 0;
	}

	if (hp < 8) 
	{
		currentAnim2 = &barricadedestroy;
	}

	if (hpold > hp) 
	{
		hpold = hp;
		App->particles->AddParticle(App->particles->dust, position.x + randomoffset, position.y + 10,0, 0, false, Collider::Type::NONE);
	}

	if (shootCooldown > 120 && deleting == false)
	{

		float dir = Dircalculation(dx, dy);

		float dirx = (dx * 1.5f / dir);
		float diry = (dy * 1.5f / dir);


		App->particles->AddParticle(App->particles->laser, position.x + offsetx, position.y + offsety, dirx * 2, diry * 2, false, Collider::Type::ENEMY_SHOT);

		shootCooldown = 0;
	}

	if (deleting == false)
	switch (GetTargetDir(dx, dy))
	{
	case LEFT:
		currentAnim = &peekyDownLeft;
		break;
	case RIGHT:
		currentAnim = &peekyDownRight;
		break;
	case DOWN:
		currentAnim = &peekyDown;
		break;
	
	case DOWNLEFT:
		currentAnim = &peekyDownLeft;
		break;
	case DOWNRIGHT:
		currentAnim = &peekyDownRight;
		break;

	}

	if (currentAnim->HasFinished() == true)
	{
		pendingToDelete = true;
	}

	collider->SetPos(position.x , position.y);
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
