#ifndef __ENEMY_BLACKSOLDIER_H__
#define __ENEMY_BLACKSOLDIER_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_BlackSoldier : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_BlackSoldier(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

private:
	// The path that will define the position in the world
	Path path;
	int moveCooldown = 0;
	int shootCooldown = 0;
	bool isShooting = false;
	bool deleting;
	// Enemy animations
	Animation box;
	Animation boxidle;
	Animation front, back;
	Animation helicopterArriving;
	Animation helicopterFight;
	Animation greyEnemyMeleeDown;
	Animation blackSoldierDeath;
	float dx;
	float dy;
};

#endif // __ENEMY_BLACKSOLDIER_H__