#include "Enemy_Barrel.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Barrel::Enemy_Barrel(int x, int y) : Enemy(x, y)
{


	currentAnim = &barrelidle;

	barrelidle.PushBack({1509,547,63,122});
	barrel.PushBack({ 1573,547,63,122 });
	barrel.PushBack({ 1637,547,63,122 });
	barrel.PushBack({ 1701,547,63,122 });
	barrel.PushBack({ 1765,547,63,122 });
	barrel.PushBack({ 1829,547,63,122 });
	barrel.PushBack({ 1893,547,63,122 });

	barrel.PushBack({ 1509,673,63,122 });
	barrel.PushBack({ 1573,673,63,122 });
	barrel.PushBack({ 1637,673,63,122 });
	barrel.PushBack({ 1701,673,63,122 });
	barrel.PushBack({ 1765,673,63,122 });
	barrel.PushBack({ 1829,673,63,122 });
	barrel.PushBack({ 1893,673,63,122 });

	barrel.PushBack({ 1509,799,63,122 });
	barrel.PushBack({ 1573,799,63,122 });
	barrel.PushBack({ 1637,799,63,122 });
	barrel.PushBack({ 1701,799,63,122 });

	barrelloop.PushBack({ 1765,799,63,122 });
	barrelloop.PushBack({ 1829,799,63,122 });
	barrelloop.PushBack({ 1893,799,63,122 });
	barrelloop.PushBack({ 1509,924,63,122 });
	barrelloop.PushBack({ 1573,924,63,122 });
	barrelloop.PushBack({ 1637,924,63,122 });
	barrelloop.PushBack({ 1701,924,63,122 });
	barrelloop.PushBack({ 1765,924,63,122 });

	barrel.speed = 0.3f;
	barrelloop.speed = 0.2f;
	barrel.loop = false;
	barrelloop.loop = true;
	collider = App->collisions->AddCollider({ 20, 80, 20, 30 }, Collider::Type::ENEMY, (Module*)App->enemies);
	hp = 1;

}

void Enemy_Barrel::Update()
{
	if (deleting == true)
		timer++;

	if (pendingToDelete == true && deleting == false)
	{
		pendingToDelete = false;
		deleting = true;
		currentAnim = &barrel;
	}

	if (currentAnim->HasFinished() == true && currentAnim == &barrel) 
	{
		currentAnim = &barrelloop;
	}

	if (timer >= 300) 
	{
		barrelloop.loop = false;
	}

	if (currentAnim->HasFinished() == true && currentAnim != &barrel)
	{
		pendingToDelete = true;
	}

	collider->SetPos(position.x + 20, position.y + 88);
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
