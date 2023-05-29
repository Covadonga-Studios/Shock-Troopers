#ifndef __ENEMY_BROWNSHIP_H__
#define __ENEMY_BROWNSHIP_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_BrownShip : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_BrownShip(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	Path path;
	int shootCooldown = 0;
	bool deleting = false;
	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation fly;
	Animation enemydeath1;
	Animation enemyshot1down;
	Animation enemyshot1rightdown;
	Animation enemyshot1right;
	Animation enemyshot1rightup;
	Animation enemyshot1up;
	Animation enemyshot1upleft;
	Animation enemyshot1left;
	Animation enemyshot1downleft;
	Animation enemyBurning;
	Animation enemyRunning;
	Animation enemyStopping;
	Animation enemyLooking;
	Animation walkingUp;
	Animation walkingLeft;
	Animation walkingDownRight;
	Animation walkingUpLeft;

	float dx;
	float dy;
};

#endif // __ENEMY_BROWNSHIP_H__