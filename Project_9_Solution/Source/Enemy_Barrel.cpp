#include "Enemy_Barrel.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"

Enemy_Barrel::Enemy_Barrel(int x, int y) : Enemy(x, y)
{


	currentAnim = &barrelidle;


	barrelidle.PushBack({ 1509,546,63,122 });
	barrel.PushBack({ 1572,546,62,125 });
	barrel.PushBack({ 1635,546,62,125 });
	barrel.PushBack({ 1699,546,62,125 });
	barrel.PushBack({ 1761,546,62,125 });
	barrel.PushBack({ 1824,546,62,125 });
	barrel.PushBack({ 1890,546,62,125 });
	barrel.PushBack({ 1509,671,62,125 });
	barrel.PushBack({ 1571,671,62,125 });
	barrel.PushBack({ 1697,671,62,125 });
	barrel.PushBack({ 1759,671,62,125 });
	barrel.PushBack({ 1820,671,62,125 });
	barrel.PushBack({ 1883,671,62,125 });
	barrel.PushBack({ 1505,797,62,125 });
	barrel.PushBack({ 1568,797,62,125 });
	barrel.PushBack({ 1633,797,62,125 });
	barrel.PushBack({ 1697,797,62,125 });
	barrelloop.PushBack({ 1759,797,62,125 });
	barrelloop.PushBack({ 1821,797,62,125 });
	barrelloop.PushBack({ 1883,797,62,125 });
	barrelloop.PushBack({ 1507,923,62,125 });
	barrelloop.PushBack({ 1571,923,62,125 });
	barrelloop.PushBack({ 1635,923,62,125 });
	barrelloop.PushBack({ 1700,923,62,125 });
	barrelloop.PushBack({ 1760,923,62,125 });
									  
	barrel.speed = 0.3f;
	barrelloop.speed = 0.3f;
	barrel.loop = false;
	barrelloop.loop = true;
	collider = App->collisions->AddCollider({ 20, 80, 20, 30 }, Collider::Type::ENEMY, (Module*)App->enemies);
	collider2 = App->collisions->AddCollider({ 20, 80, 20, 30 }, Collider::Type::ENEMY_SHOT, (Module*)App->enemies);
	collider3 = App->collisions->AddCollider({ 20, 80, 20, 30 }, Collider::Type::PLAYER_SHOT, (Module*)App->enemies);
	collider2->SetPos(2000, 3000);
	collider3->SetPos(2000, 3000);
	hp = 12;
	deathfx = App->audio->LoadFx("Assets/Fx/barreldestruction.wav");

}

void Enemy_Barrel::Update()
{
	if (deleting == true)
		timer++;

	if (hp <= 0 && deleting == false)
	{
		App->audio->PlayFx(deathfx);
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
		die = true;
		collider2->pendingToDelete = true;
		collider3->pendingToDelete = true;
	}
	if (deleting == true) 
	{
		collider2->SetPos(position.x + 20, position.y + 88);
		collider3->SetPos(position.x + 20, position.y + 88);
	}

	collider->SetPos(position.x + 20, position.y + 88);
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
