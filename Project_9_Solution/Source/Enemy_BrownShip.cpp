#include "Enemy_BrownShip.h"
#include "Module.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"
#include "stdio.h"
#include "math.h"


Enemy_BrownShip::Enemy_BrownShip(int x, int y) : Enemy(x, y)
{
	fly.PushBack({5,72,21,22});
	enemydeath1.PushBack({ 20, 720, 41, 53 });
	enemydeath1.PushBack({ 61, 720, 41, 53 });
	enemydeath1.PushBack({ 102, 720, 41, 53 });
	enemydeath1.PushBack({ 143, 720, 41, 53 });
	enemydeath1.PushBack({ 184, 720, 41, 53 });
	enemydeath1.PushBack({ 225, 720, 41, 53 });
	enemydeath1.PushBack({ 266, 720, 41, 53 });
	enemydeath1.speed = 0.1f;
	enemydeath1.loop = false;
	currentAnim = &fly;
	
	enemyshot1down.PushBack({ 20, 600, 43, 47 });
	enemyshot1rightdown.PushBack({ 63, 600, 43, 47 });
	enemyshot1right.PushBack({ 106, 600, 43, 47 });
	enemyshot1rightup.PushBack({ 149, 600, 43, 47 });
	enemyshot1up.PushBack({ 192, 600, 43, 47 });
	enemyshot1upleft.PushBack({ 235, 600, 43, 47 });
	enemyshot1left.PushBack({ 278, 600, 43, 47 });
	enemyshot1downleft.PushBack({ 321, 600, 43, 47 });

	enemyBurning.PushBack({ 1133, 962, 60, 74 });
	enemyBurning.PushBack({ 1194, 962, 60, 74 });
	enemyBurning.PushBack({ 1255, 962, 60, 74 });
	enemyBurning.PushBack({ 1316, 962, 60, 74 });
	enemyBurning.PushBack({ 1377, 962, 60, 74 });
	enemyBurning.PushBack({ 1438, 962, 60, 74 });
	enemyBurning.PushBack({ 1133, 1037, 60, 74 });
	enemyBurning.PushBack({ 1194, 1037, 60, 74 });
	enemyBurning.PushBack({ 1255, 1037, 60, 74 });
	enemyBurning.PushBack({ 1316, 1037, 60, 74 });
	enemyBurning.PushBack({ 1377, 1037, 60, 74 });
	enemyBurning.PushBack({ 1438, 1037, 60, 74 });
	enemyBurning.PushBack({ 1133, 1112, 60, 74 });
	enemyBurning.PushBack({ 1194, 1112, 60, 74 });
	enemyBurning.PushBack({ 1255, 1112, 60, 74 });
	enemyBurning.PushBack({ 1316, 1112, 60, 74 });
	enemyBurning.PushBack({ 1377, 1112, 60, 74 });
	enemyBurning.loop = false;
	enemyBurning.speed = 0.1f;

	enemyRunning.PushBack({ 881, 971, 39, 55 });
	enemyRunning.PushBack({ 921, 971, 39, 55 });
	enemyRunning.PushBack({ 961, 971, 39, 55 });
	enemyRunning.PushBack({ 1001, 971, 39, 55 });

	enemyStopping.PushBack({ 821, 1026, 39, 55 });
	enemyStopping.PushBack({ 921, 1026, 39, 55 });
	enemyStopping.PushBack({ 961, 1026, 39, 55 });
	enemyStopping.PushBack({ 1001, 1026, 39, 55 });
	enemyStopping.PushBack({ 1041, 1026, 39, 55 });
	enemyStopping.PushBack({ 1081, 1026, 39, 55 });

	enemyLooking.PushBack({ 1625, 304, 33, 50 });
	enemyLooking.PushBack({ 1659, 304, 33, 50 });
	enemyLooking.PushBack({ 1693, 304, 33, 50 });
	enemyLooking.PushBack({ 1728, 304, 33, 50 });
	enemyLooking.PushBack({ 1763, 304, 33, 50 });
	enemyLooking.PushBack({ 1625, 355, 33, 50 });
	enemyLooking.PushBack({ 1659, 355, 33, 50 });
	enemyLooking.PushBack({ 1693, 355, 33, 50 });
	enemyLooking.PushBack({ 1728, 355, 33, 50 });
	enemyLooking.PushBack({ 1763, 355, 33, 50 });
	enemyLooking.PushBack({ 1625, 406, 66, 50 });
	enemyLooking.PushBack({ 1693, 406, 33, 50 });
	enemyLooking.PushBack({ 1728, 406, 33, 50 });

	walkingUp.PushBack({ 1132, 1187, 41, 50 });
	walkingUp.PushBack({ 1174, 1187, 41, 50 });
	walkingUp.PushBack({ 1216, 1187, 41, 50 });
	walkingUp.PushBack({ 1258, 1187, 41, 50 });
	walkingUp.PushBack({ 1300, 1187, 41, 50 });
	walkingUp.PushBack({ 1342, 1187, 41, 50 });
	walkingUp.PushBack({ 1384, 1187, 41, 50 });

	walkingLeft.PushBack({ 1132, 1238, 41, 50 });
	walkingLeft.PushBack({ 1174, 1238, 41, 50 });
	walkingLeft.PushBack({ 1216, 1238, 41, 50 });
	walkingLeft.PushBack({ 1258, 1238, 41, 50 });
	walkingLeft.PushBack({ 1300, 1238, 41, 50 });
	walkingLeft.PushBack({ 1342, 1238, 41, 50 });
	walkingLeft.PushBack({ 1384, 1238, 41, 50 });
	walkingLeft.PushBack({ 1426, 1238, 41, 50 });

	walkingRight.PushBack({ 1132, 1238, 41, 50 }, true);
	walkingRight.PushBack({ 1174, 1238, 41, 50 }, true);
	walkingRight.PushBack({ 1216, 1238, 41, 50 }, true);
	walkingRight.PushBack({ 1258, 1238, 41, 50 }, true);
	walkingRight.PushBack({ 1300, 1238, 41, 50 }, true);
	walkingRight.PushBack({ 1342, 1238, 41, 50 }, true);
	walkingRight.PushBack({ 1384, 1238, 41, 50 }, true);
	walkingRight.PushBack({ 1426, 1238, 41, 50 }, true);

	walkingDownRight.PushBack({ 1132, 1289, 41, 50 });
	walkingDownRight.PushBack({ 1174, 1289, 41, 50 });
	walkingDownRight.PushBack({ 1216, 1289, 41, 50 });
	walkingDownRight.PushBack({ 1258, 1289, 41, 50 });
	walkingDownRight.PushBack({ 1300, 1289, 41, 50 });
	walkingDownRight.PushBack({ 1342, 1289, 41, 50 });
	walkingDownRight.PushBack({ 1384, 1289, 41, 50 });
	walkingDownRight.PushBack({ 1426, 1289, 41, 50 });

	walkingDownLeft.PushBack({ 1132, 1289, 41, 50 }, true);
	walkingDownLeft.PushBack({ 1174, 1289, 41, 50 }, true);
	walkingDownLeft.PushBack({ 1216, 1289, 41, 50 }, true);
	walkingDownLeft.PushBack({ 1258, 1289, 41, 50 }, true);
	walkingDownLeft.PushBack({ 1300, 1289, 41, 50 }, true);
	walkingDownLeft.PushBack({ 1342, 1289, 41, 50 }, true);
	walkingDownLeft.PushBack({ 1384, 1289, 41, 50 }, true);
	walkingDownLeft.PushBack({ 1426, 1289, 41, 50 }, true);

	walkingUpLeft.PushBack({ 1132, 1340, 41, 50 });
	walkingUpLeft.PushBack({ 1174, 1340, 41, 50 });
	walkingUpLeft.PushBack({ 1216, 1340, 41, 50 });
	walkingUpLeft.PushBack({ 1258, 1340, 41, 50 });
	walkingUpLeft.PushBack({ 1300, 1340, 41, 50 });
	walkingUpLeft.PushBack({ 1342, 1340, 41, 50 });
	walkingUpLeft.PushBack({ 1384, 1340, 41, 50 });
	walkingUpLeft.PushBack({ 1426, 1340, 41, 50 });

	walkingUpRight.PushBack({ 1132, 1340, 41, 50 }, true);
	walkingUpRight.PushBack({ 1174, 1340, 41, 50 }, true);
	walkingUpRight.PushBack({ 1216, 1340, 41, 50 }, true);
	walkingUpRight.PushBack({ 1258, 1340, 41, 50 }, true);
	walkingUpRight.PushBack({ 1300, 1340, 41, 50 }, true);
	walkingUpRight.PushBack({ 1342, 1340, 41, 50 }, true);
	walkingUpRight.PushBack({ 1384, 1340, 41, 50 }, true);
	walkingUpRight.PushBack({ 1426, 1340, 41, 50 }, true);

	enemyFallingRight.PushBack({ 1, 1421, 90, 98 });
	enemyFallingRight.PushBack({ 92, 1421, 90, 98 });
	enemyFallingRight.PushBack({ 183, 1421, 90, 98 });
	enemyFallingRight.PushBack({ 274, 1421, 90, 98 });
	enemyFallingRight.PushBack({ 365, 1421, 90, 98 });
	enemyFallingRight.PushBack({ 456, 1421, 90, 98 });
	enemyFallingRight.PushBack({ 547, 1421, 90, 98 });
	enemyFallingRight.PushBack({ 638, 1421, 90, 98 });
	enemyFallingRight.PushBack({ 729, 1421, 90, 98 });
	enemyFallingRight.PushBack({ 820, 1421, 90, 98 });
	enemyFallingRight.PushBack({ 911, 1421, 90, 98 });
	enemyFallingRight.PushBack({ 1002, 1421, 90, 98 });

	enemyFallingLeft.PushBack({ 1, 1421, 90, 98 }, true);
	enemyFallingLeft.PushBack({ 92, 1421, 90, 98 }, true);
	enemyFallingLeft.PushBack({ 183, 1421, 90, 98 }, true);
	enemyFallingLeft.PushBack({ 274, 1421, 90, 98 }, true);
	enemyFallingLeft.PushBack({ 365, 1421, 90, 98 }, true);
	enemyFallingLeft.PushBack({ 456, 1421, 90, 98 }, true);
	enemyFallingLeft.PushBack({ 547, 1421, 90, 98 }, true);
	enemyFallingLeft.PushBack({ 638, 1421, 90, 98 }, true);
	enemyFallingLeft.PushBack({ 729, 1421, 90, 98 }, true);
	enemyFallingLeft.PushBack({ 820, 1421, 90, 98 }, true);
	enemyFallingLeft.PushBack({ 911, 1421, 90, 98 }, true);
	enemyFallingLeft.PushBack({ 1002, 1421, 90, 98 }, true);

	enemyRunningRight.PushBack({ 931, 1260, 49, 51 });
	enemyRunningRight.PushBack({ 981, 1260, 49, 51 });
	enemyRunningRight.PushBack({ 1031, 1260, 49, 51 });
	enemyRunningRight.PushBack({ 1081, 1260, 49, 51 });

	enemyRunningLeft.PushBack({ 931, 1260, 49, 51 }, true);
	enemyRunningLeft.PushBack({ 981, 1260, 49, 51 }, true);
	enemyRunningLeft.PushBack({ 1031, 1260, 49, 51 }, true);
	enemyRunningLeft.PushBack({ 1081, 1260, 49, 51 }, true);

	enemyRunningUpRight.PushBack({ 931, 1312, 49, 51 });
	enemyRunningUpRight.PushBack({ 981, 1312, 49, 51 });
	enemyRunningUpRight.PushBack({ 1031, 1312, 49, 51 });
	enemyRunningUpRight.PushBack({ 1081, 1312, 49, 51 });

	enemyRunningUpLeft.PushBack({ 931, 1312, 49, 51 }, true);
	enemyRunningUpLeft.PushBack({ 981, 1312, 49, 51 }, true);
	enemyRunningUpLeft.PushBack({ 1031, 1312, 49, 51 }, true);
	enemyRunningUpLeft.PushBack({ 1081, 1312, 49, 51 }, true);

	enemyRunningUp.PushBack({ 931, 1364, 49, 51 });
	enemyRunningUp.PushBack({ 981, 1364, 49, 51 });
	enemyRunningUp.PushBack({ 1031, 1364, 49, 51 });
	enemyRunningUp.PushBack({ 1081, 1364, 49, 51 });

	enemyMeleeLeft.PushBack({ 1468, 1194, 50, 53 });
	enemyMeleeLeft.PushBack({ 1519, 1194, 50, 53 });
	enemyMeleeLeft.PushBack({ 1570, 1194, 50, 53 });
	enemyMeleeLeft.PushBack({ 1621, 1194, 50, 53 });
	enemyMeleeLeft.PushBack({ 1672, 1194, 50, 53 });
	enemyMeleeLeft.PushBack({ 1723, 1194, 50, 53 });
	enemyMeleeLeft.PushBack({ 1774, 1194, 50, 53 });
	enemyMeleeLeft.PushBack({ 1468, 1248, 50, 53 });
	enemyMeleeLeft.PushBack({ 1519, 1248, 50, 53 });
	enemyMeleeLeft.PushBack({ 1570, 1248, 50, 53 });
	enemyMeleeLeft.PushBack({ 1621, 1248, 50, 53 });
	enemyMeleeLeft.PushBack({ 1672, 1248, 50, 53 });
	enemyMeleeLeft.PushBack({ 1723, 1248, 50, 53 });

	enemyMeleeRight.PushBack({ 1468, 1194, 50, 53 }, true);
	enemyMeleeRight.PushBack({ 1519, 1194, 50, 53 }, true);
	enemyMeleeRight.PushBack({ 1570, 1194, 50, 53 }, true);
	enemyMeleeRight.PushBack({ 1621, 1194, 50, 53 }, true);
	enemyMeleeRight.PushBack({ 1672, 1194, 50, 53 }, true);
	enemyMeleeRight.PushBack({ 1723, 1194, 50, 53 }, true);
	enemyMeleeRight.PushBack({ 1774, 1194, 50, 53 }, true);
	enemyMeleeRight.PushBack({ 1468, 1248, 50, 53 }, true);
	enemyMeleeRight.PushBack({ 1519, 1248, 50, 53 }, true);
	enemyMeleeRight.PushBack({ 1570, 1248, 50, 53 }, true);
	enemyMeleeRight.PushBack({ 1621, 1248, 50, 53 }, true);
	enemyMeleeRight.PushBack({ 1672, 1248, 50, 53 }, true);
	enemyMeleeRight.PushBack({ 1723, 1248, 50, 53 }, true);

	greenDeathUpRight.PushBack({ 623, 1520, 55, 55 });
	greenDeathUpRight.PushBack({ 679, 1520, 55, 55 });
	greenDeathUpRight.PushBack({ 735, 1520, 55, 55 });
	greenDeathUpRight.PushBack({ 791, 1520, 55, 55 });
	greenDeathUpRight.PushBack({ 847, 1520, 55, 55 });
	greenDeathUpRight.PushBack({ 903, 1520, 55, 55 });
	greenDeathUpRight.PushBack({ 959, 1520, 55, 55 });

	greenDeathUpLeft.PushBack({ 623, 1520, 55, 55 }, true);
	greenDeathUpLeft.PushBack({ 679, 1520, 55, 55 }, true);
	greenDeathUpLeft.PushBack({ 735, 1520, 55, 55 }, true);
	greenDeathUpLeft.PushBack({ 791, 1520, 55, 55 }, true);
	greenDeathUpLeft.PushBack({ 847, 1520, 55, 55 }, true);
	greenDeathUpLeft.PushBack({ 903, 1520, 55, 55 }, true);
	greenDeathUpLeft.PushBack({ 959, 1520, 55, 55 }, true);

	greenDeathDownRight.PushBack({ 623, 1576, 55, 55 });
	greenDeathDownRight.PushBack({ 679, 1576, 55, 55 });
	greenDeathDownRight.PushBack({ 735, 1576, 55, 55 });
	greenDeathDownRight.PushBack({ 791, 1576, 55, 55 });
	greenDeathDownRight.PushBack({ 847, 1576, 55, 55 });
	greenDeathDownRight.PushBack({ 903, 1576, 55, 55 });
	greenDeathDownRight.PushBack({ 959, 1576, 55, 55 });

	greenDeathDownLeft.PushBack({ 623, 1576, 55, 55 }, true);
	greenDeathDownLeft.PushBack({ 679, 1576, 55, 55 }, true);
	greenDeathDownLeft.PushBack({ 735, 1576, 55, 55 }, true);
	greenDeathDownLeft.PushBack({ 791, 1576, 55, 55 }, true);
	greenDeathDownLeft.PushBack({ 847, 1576, 55, 55 }, true);
	greenDeathDownLeft.PushBack({ 903, 1576, 55, 55 }, true);
	greenDeathDownLeft.PushBack({ 959, 1576, 55, 55 }, true);

	greenDeathRight.PushBack({ 623, 1632, 55, 55 });
	greenDeathRight.PushBack({ 679, 1632, 55, 55 });
	greenDeathRight.PushBack({ 735, 1632, 55, 55 });
	greenDeathRight.PushBack({ 791, 1632, 55, 55 });
	greenDeathRight.PushBack({ 847, 1632, 55, 55 });
	greenDeathRight.PushBack({ 903, 1632, 55, 55 });
	greenDeathRight.PushBack({ 959, 1632, 55, 55 });

	greenDeathLeft.PushBack({ 623, 1632, 55, 55 }, true);
	greenDeathLeft.PushBack({ 679, 1632, 55, 55 }, true);
	greenDeathLeft.PushBack({ 735, 1632, 55, 55 }, true);
	greenDeathLeft.PushBack({ 791, 1632, 55, 55 }, true);
	greenDeathLeft.PushBack({ 847, 1632, 55, 55 }, true);
	greenDeathLeft.PushBack({ 903, 1632, 55, 55 }, true);
	greenDeathLeft.PushBack({ 959, 1632, 55, 55 }, true);

	hp = 1;

	
	collider = App->collisions->AddCollider({0, 0, 43, 43}, Collider::Type::ENEMY, (Module*)App->enemies);
}


void Enemy_BrownShip::Update()
{
	shootCooldown++;

	dx = (App->player->position.x + App->player->collider->rect.w / 2 - position.x);
	dy = (App->player->position.y + App->player->collider->rect.h / 2 - position.y);

	if (pendingToDelete == true && deleting == false) 
	{
		pendingToDelete = false;
		deleting = true;
		if (!isOnFire) {

			currentAnim = &enemydeath1;
		}
		else
			currentAnim = &enemyBurning;
	}

	if (currentAnim->HasFinished() == true)
	{
		pendingToDelete = true;
	}

	if (shootCooldown > 150 && deleting == false)
	{

		 
		float dir = Dircalculation(dx, dy);

		float dirx = (dx * 1.5f / dir);
		float diry = (dy * 1.5f / dir);
		
		
		App->particles->AddParticle(App->particles->laser, position.x, position.y,dirx, diry, false, Collider::Type::ENEMY_SHOT);
		shootCooldown = 0;
	}


	if (deleting == false)
	switch (GetTargetDir(dx,dy))
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

	collider->SetPos(position.x, position.y);

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
