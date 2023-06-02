#include "Enemy_Camillers.h"
#include "ModuleEnemies.h"
#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Camillers::Enemy_Camillers(int x, int y) : Enemy(x, y)
{

	medicsWalking.PushBack({ 1795, 1, 126, 48 });
	medicsWalking.PushBack({ 1795, 50, 126, 48 });
	medicsWalking.PushBack({ 1795, 99, 126, 48 });
	medicsWalking.PushBack({ 1795, 148, 126, 48 });
	medicsWalking.PushBack({ 1795, 197, 126, 48 });
	medicsWalking.PushBack({ 1795, 246, 126, 48 });
	medicsWalking.PushBack({ 1795, 295, 126, 48 });
	medicsWalking.PushBack({ 1795, 344, 126, 48 });
	medicsWalking.speed = 0.2f;

	medicsHurt.PushBack({ 1919, 1251, 137, 77 });
	medicsHurt.PushBack({ 1919, 1329, 137, 77 });
	medicsHurt.PushBack({ 1919, 1407, 137, 77 });
	medicsHurt.PushBack({ 1919, 1485, 137, 77 });
	medicsHurt.PushBack({ 1919, 1563, 137, 77 });
	medicsHurt.PushBack({ 1919, 1641, 137, 77 });
	medicsHurt.PushBack({ 1919, 1719, 137, 77 });
	medicsHurt.loop = false;
	medicsHurt.speed = 0.1f;

	enemydeath1.PushBack({ 20, 720, 41, 53 });
	enemydeath1.PushBack({ 61, 720, 41, 53 });
	enemydeath1.PushBack({ 102, 720, 41, 53 });
	enemydeath1.PushBack({ 143, 720, 41, 53 });
	enemydeath1.PushBack({ 184, 720, 41, 53 });
	enemydeath1.PushBack({ 225, 720, 41, 53 });
	enemydeath1.PushBack({ 266, 720, 41, 53 });
	enemydeath1.speed = 0.1f;
	enemydeath1.loop = false;

	dissapear.PushBack({ 0,0,0,0 });

	currentAnim = &medicsWalking;

	collider = App->collisions->AddCollider({ 20, 20, 126, 48 }, Collider::Type::ENEMY, (Module*)App->enemies);
	hp = 1;

}

void Enemy_Camillers::Update()
{
	par++;

	if (deleting == false && par % 2 == 0)
		position.x--;

	if (pendingToDelete == true && deleting == false)
	{
		pendingToDelete = false;
		deleting = true;
		currentAnim = &medicsHurt;
		par = 0;
	}

	if (currentAnim->HasFinished() == true && deleting == true && spawn == false)
	{
		offsettexture3x += 120;
		currentAnim2 = &enemydeath1;
		currentAnim3 = &enemydeath1;
		currentAnim = &dissapear;
		spawn == true;

	}

	if (par > 120 && deleting == true)
	{
		pendingToDelete = true;
	}

	collider->SetPos(position.x , position.y );
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}