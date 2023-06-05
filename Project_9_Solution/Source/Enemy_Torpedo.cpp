#include "Enemy_Torpedo.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Torpedo::Enemy_Torpedo(int x, int y) : Enemy(x, y)
{

	//MONKE

	banana.PushBack({ 854, 1161, 16, 16 });
	banana.PushBack({ 871, 1161, 16, 16 });
	banana.speed = 0.1f;

	monkeyRight.PushBack({ 854, 1178, 29, 23 });
	monkeyRight.PushBack({ 884, 1178, 29, 23 });
	monkeyRight.PushBack({ 914, 1178, 29, 23 });
	monkeyRight.PushBack({ 944, 1178, 29, 23 });
	monkeyRight.PushBack({ 974, 1178, 29, 23 });
	monkeyRight.PushBack({ 1004, 1178, 29, 23 });
	monkeyRight.speed = 0.1f;
	monkeyRight.loop = true;

	monkeyLeft.PushBack({ 854, 1178, 29, 23 }, true);
	monkeyLeft.PushBack({ 884, 1178, 29, 23 }, true);
	monkeyLeft.PushBack({ 914, 1178, 29, 23 }, true);
	monkeyLeft.PushBack({ 944, 1178, 29, 23 }, true);
	monkeyLeft.PushBack({ 974, 1178, 29, 23 }, true);
	monkeyLeft.PushBack({ 1004, 1178, 29, 23 }, true);
	monkeyLeft.speed = 0.1f;
	monkeyLeft.loop = true;

	monkeyHappy.PushBack({ 854, 1202, 22, 30 });
	monkeyHappy.PushBack({ 877, 1202, 22, 30 });
	monkeyHappy.PushBack({ 900, 1202, 22, 30 });
	monkeyHappy.PushBack({ 923, 1202, 22, 30 });
	monkeyHappy.PushBack({ 946, 1202, 22, 30 });
	monkeyHappy.PushBack({ 969, 1202, 22, 30 });
	monkeyHappy.PushBack({ 992, 1202, 22, 30 });
	monkeyHappy.speed = 0.1f;

	monkeyAngry.PushBack({ 854, 1233, 27, 26 });
	monkeyAngry.PushBack({ 882, 1233, 27, 26 });
	monkeyAngry.PushBack({ 910, 1233, 27, 26 });
	monkeyAngry.PushBack({ 938, 1233, 27, 26 });
	monkeyAngry.PushBack({ 854, 1233, 27, 26 });
	monkeyAngry.PushBack({ 882, 1233, 27, 26 });
	monkeyAngry.PushBack({ 910, 1233, 27, 26 });
	monkeyAngry.PushBack({ 938, 1233, 27, 26 });
	monkeyAngry.PushBack({ 854, 1233, 27, 26 });
	monkeyAngry.PushBack({ 882, 1233, 27, 26 });
	monkeyAngry.PushBack({ 910, 1233, 27, 26 });
	monkeyAngry.PushBack({ 938, 1233, 27, 26 });
	monkeyAngry.speed = 0.1f;
	monkeyAngry.loop = false;

	monkeyLeavingRight.PushBack({ 854, 1260, 25, 24 });
	monkeyLeavingRight.PushBack({ 880, 1260, 25, 24 });
	monkeyLeavingRight.speed = 0.1f;
	monkeyLeavingRight.loop = false;

	monkeyLeavingLeft.PushBack({ 854, 1260, 25, 24 }, true);
	monkeyLeavingLeft.PushBack({ 880, 1260, 25, 24 }, true);
	monkeyLeavingLeft.speed = 0.1f;
	monkeyLeavingLeft.loop = false;
	

	collider = App->collisions->AddCollider({ position.x, position.y, 25, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);
	currentAnim = &monkeyRight;

}

void Enemy_Torpedo::Update()
{
	
	position.x++;
	counter++;

	if(counter >= 182){
		currentAnim = &monkeyAngry;
		currentAnim->HasFinished();
	}

	

	if (pendingToDelete == true && deleting == false)
	{
		pendingToDelete = false;
		deleting = true;
		
	}

	if (currentAnim->HasFinished() == true)
	{
		pendingToDelete = true;
	}

	collider->SetPos(position.x + 20, position.y + 24);
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
