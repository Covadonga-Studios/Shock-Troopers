#include "Enemy_Itempickup.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"

Enemy_Itempickup::Enemy_Itempickup(int x, int y) : Enemy(x, y)
{


    //POWERUPS //POWERUPS //POWERUPS //POWERUPS //POWERUPS //POWERUPS //POWERUPS //POWERUPS 

    life.PushBack({ 166, 1819, 18, 15 });
    life.PushBack({ 188, 1819, 18, 15 });
    life.PushBack({ 210, 1819, 18, 15 });
    life.PushBack({ 232, 1819, 18, 15 });
    life.PushBack({ 254, 1819, 18, 15 });
    life.PushBack({ 276, 1819, 18, 15 });
    life.PushBack({ 298, 1819, 18, 15 });
    life.PushBack({ 320, 1819, 30, 15 });
    life.speed = 0.1f;
    life.loop =false;

    loopLife.PushBack({ 354, 1819, 28, 15 });
    loopLife.PushBack({ 386, 1819, 28, 15 });
    loopLife.loop = true;
    loopLife.speed = 0.07f;

    lifeUp.PushBack({ 418, 1820, 32, 15 });
    lifeUp.PushBack({ 452, 1820, 32, 15 });
    lifeUp.PushBack({ 486, 1820, 32, 15 });
    lifeUp.loop = false;
    lifeUp.speed = 0.04f;

    diamondLoop.PushBack({ 263, 1840, 15, 16 });
    diamondLoop.PushBack({ 279, 1840, 15, 16 });
    diamondLoop.PushBack({ 295, 1840, 15, 16 });
    diamondLoop.PushBack({ 311, 1840, 15, 16 });
    diamondLoop.PushBack({ 327, 1840, 15, 16 });
    diamondLoop.PushBack({ 343, 1840, 15, 16 });
    diamondLoop.PushBack({ 359, 1840, 15, 16 });
    diamondLoop.PushBack({ 375, 1840, 15, 16 });
    diamondLoop.loop = true;
    diamondLoop.speed = 0.1f;

    diamondUp.PushBack({ 393, 1842, 26, 14 });
    diamondUp.PushBack({ 421, 1842, 26, 14 });
    diamondUp.PushBack({ 449, 1842, 26, 14 });
    diamondUp.loop = false;
    diamondUp.speed = 0.04f;

    bomb.PushBack({ 263, 1862, 20, 13 });
    bomb.PushBack({ 285, 1862, 20, 13 });
    bomb.PushBack({ 307, 1860, 20, 15 });
    bomb.PushBack({ 329, 1860, 30, 15 });
    bomb.PushBack({ 361, 1860, 30, 15 });
    bomb.PushBack({ 393, 1860, 30, 15 });
    bomb.PushBack({ 425, 1860, 30, 15 });
    bomb.PushBack({ 457, 1860, 30, 15 });
    bomb.loop = false;
    bomb.speed = 0.1f;

    loopBomb.PushBack({ 489, 1860, 30, 15 });
    loopBomb.PushBack({ 521, 1860, 30, 15 });
    loopBomb.PushBack({ 553, 1860, 30, 15 });
    loopBomb.loop = true;
    loopBomb.speed = 0.1f;

    bombUp.PushBack({ 586, 1861, 25, 14 });
    bombUp.PushBack({ 613, 1861, 25, 14 });
    bombUp.PushBack({ 640, 1861, 25, 14 });
    bombUp.loop = false;
    bombUp.speed = 0.04f;


    flameThrowerIdle.PushBack({ 1929, 152, 32, 16 });

    flameThrowerLoop.PushBack({ 1929, 171, 32, 16 });
    flameThrowerLoop.PushBack({ 1929, 190, 32, 16 });


    threeWayIdle.PushBack({ 1964, 152, 32, 15 });

    threeWayLoop.PushBack({ 1964, 171, 32, 16 });
    threeWayLoop.PushBack({ 1964, 190, 32, 16 });
    threeWayLoop.speed = 0.1f;
    //powerups

   

	currentAnim = &life;

	collider = App->collisions->AddCollider({ 20, 20, 30, 15}, Collider::Type::ITEM, (Module*)App->enemies);
	hp = 1;

}

void Enemy_Itempickup::Update()
{
    switch (enemyMode) 
    {
    case 0:
        if (spawn == false)
        {
            currentAnim = &life;
            spawn = true;

        }


        if (currentAnim->HasFinished() && spawn == true && loop == false && deleting == false)
        {
            loop = true;
            currentAnim = &loopLife;
        }

        if (pendingToDelete == true && deleting == false)
        {
            pendingToDelete = false;
            deleting = true;
            currentAnim = &lifeUp;
            App->player->hp += 64;
            App->player->score += 3000;

        }

        if (currentAnim->HasFinished() == true && deleting == true)
        {
            pendingToDelete = true;
        }

        break;
    case 1:
        if (spawn == false)
        {
            spawn = true;
            currentAnim = &diamondLoop;
        }


        if (pendingToDelete == true && deleting == false)
        {
            pendingToDelete = false;
            deleting = true;
            currentAnim = &diamondUp;
            App->player->score += 30000;
        }

        if (currentAnim->HasFinished() == true && deleting == true)
        {
            pendingToDelete = true;
        }
        break;
    case 2:
        if (spawn == false)
        {
            spawn = true;
            currentAnim = &bomb;
        }


        if (currentAnim->HasFinished() && spawn == true && loop == false && deleting == false)
        {
            currentAnim = &loopBomb;
        }

        if (pendingToDelete == true && deleting == false)
        {
            pendingToDelete = false;
            deleting = true;
            currentAnim = &bombUp;
            App->player->score += 4000;
            App->player->grenadeCounter++;
        }

        if (currentAnim->HasFinished() == true && deleting == true)
        {
            pendingToDelete = true;
        }
        break;
    case 3:
        if (spawn == false)
        {
            currentAnim = &flameThrowerLoop;
            spawn = true;
        }
  
        if (pendingToDelete == true && deleting == false)
        {
            pendingToDelete = false;
            deleting = true;
            App->player->weapon = 1;
            App->player->bullets = 200;
            App->player->score += 4000;
            App->player->cartridge = 0;
        }

        if (deleting == true)
        {
            pendingToDelete = true;
        }
        break;
    case 4:
        if (spawn == false)
        {
            spawn = true;
                currentAnim = &threeWayLoop;
        }
      
        if (pendingToDelete == true && deleting == false)
        {
            pendingToDelete = false;
            deleting = true;
            App->player->weapon = 2;
            App->player->bullets = 100;
            App->player->score += 4000;
            App->player->cartridge = 0;
        }

        if (deleting == true)
        {
            pendingToDelete = true;
        }
        break;
    }

  

	collider->SetPos(position.x, position.y);
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
