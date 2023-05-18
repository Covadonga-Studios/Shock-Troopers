#include "Enemy_Barrel.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Barrel::Enemy_Barrel(int x, int y) : Enemy(x, y)
{


	currentAnim = &barrelidle;


	barrelidle.PushBack({ 1509,546,63,122 });
	barrel.PushBack({ 1572,546,62,125 });
	barrel.PushBack({ 1635,546,62,125 });
	barrel.PushBack({ 1699,546,62,125 });
	barrel.PushBack({ 1761,546,62,125 });
	barrel.PushBack({ 1824,546,62,125 });
	barrel.PushBack({ 1890,542,62,125 });
	barrel.PushBack({ 1511,667,62,125});
	barrel.PushBack({ 1573,667,62,125 });
	barrel.PushBack({ 1699,667,62,125 });
	barrel.PushBack({ 1761,667,62,125 });
	barrel.PushBack({ 1822,667,62,125 });
	barrel.PushBack({ 1885,667,62,125 });
	barrel.PushBack({ 1509,799,62,125 });  //SEGUIR AQUÍ
	barrel.PushBack({ 1573,799,62,125 });
	barrel.PushBack({ 1637,799,62,125 });
	barrel.PushBack({ 1701,799,62,125 });
	barrelloop.PushBack({ 1765,799,62,125 });
	barrelloop.PushBack({ 1829,799,62,125 });
	barrelloop.PushBack({ 1893,799,62,125 });
	barrelloop.PushBack({ 1509,924,62,125 });
	barrelloop.PushBack({ 1573,924,62,125 });
	barrelloop.PushBack({ 1637,924,62,125 });
	barrelloop.PushBack({ 1701,924,62,125 });
	barrelloop.PushBack({ 1765,924,62,125 });
									  
	barrel.speed = 0.3f;
	barrelloop.speed = 0.3f;
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
