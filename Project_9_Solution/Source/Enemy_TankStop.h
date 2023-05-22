#ifndef __ENEMY_TANKSTOP_H__
#define __ENEMY_TANKSTOP_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_TankStop : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_TankStop(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

private:
	// The path that will define the position in the world
	Path path;
	int shootCooldown = 0;
	bool deleting;
	// Enemy animations
	Animation box;
	Animation boxidle;
	Animation front, back;
};

#endif // __ENEMY_MECH_H__