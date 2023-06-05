#ifndef __ENEMY_BARREL_H__
#define __ENEMY_BARREL_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Barrel : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_Barrel(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

private:
	// The path that will define the position in the world
	Path path;
	bool deleting;
	int timer = 0;
	// Enemy animations
	Animation barrel;
	Animation barrelidle;
	Animation barrelloop;
	Animation front, back;
	Collider* collider2 = nullptr;
	Collider* collider3 = nullptr;
	uint deathfx = 0;
};

#endif // __ENEMY_BARREL_H__