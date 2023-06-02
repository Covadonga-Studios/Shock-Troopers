#ifndef __ENEMY_ITEMPICKUP_H__
#define __ENEMY_ITEMPICKUP_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Itempickup : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_Itempickup(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

private:
	// The path that will define the position in the world
	Path path;
	bool deleting;
	bool spawn = false;
	bool loop = false;
	// Enemy animations
	Animation box;
	Animation boxidle;
	Animation front, back;

	Animation life;
	Animation loopLife;
	Animation lifeUp;

	Animation diamondLoop;
	Animation diamondUp;

	Animation bomb;
	Animation loopBomb;
	Animation bombUp;

	Animation flameThrowerIdle;
	Animation flameThrowerLoop;

	Animation threeWayIdle;
	Animation threeWayLoop;
};

#endif // __ENEMY_ITEMPICKUP_H__