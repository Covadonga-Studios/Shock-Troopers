#ifndef __ENEMY_THREEBARRELS_H__
#define __ENEMY_THREEBARRELS_H__

#include "Enemy.h"
#include "Path.h"


class Enemy_ThreeBarrels : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_ThreeBarrels(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

private:
	// The path that will define the position in the world
	Path path;
	bool deleting;
	// Enemy animations
	Animation box;
	Animation boxidle;
	Animation front, back;
	int deathTimer = 0;
};

#endif // __ENEMY_THREEBARRELS_H__