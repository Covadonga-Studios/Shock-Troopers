#ifndef __ENEMY_STRUCTURES_H__
#define __ENEMY_STRUCTURES_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Structures : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_Structures(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

private:
	// The path that will define the position in the world
	Path path;
	bool deleting;
	bool start;
	float dx;
	float dy;
	int shootCooldown;
	int dissapearCooldown;

	// Enemy animations
	Animation dissapear;
	Animation medicTent;
	Animation medicTentBroken;
	Animation towerBreaking;
	Animation tower;
	Animation tower2;
	Animation tower2Breaking;
	Animation enemyshot1down;
	Animation enemyshot1rightdown;
	Animation enemyshot1right;
	Animation enemyshot1rightup;
	Animation enemyshot1up;
	Animation enemyshot1upleft;
	Animation enemyshot1left;
	Animation enemyshot1downleft;
	Animation lightMGenemyDownRight;
	Animation lightMGenemyDownLeft;
	Animation lightMGenemyDown;
};

#endif // __ENEMY_STRUCTURES_H__