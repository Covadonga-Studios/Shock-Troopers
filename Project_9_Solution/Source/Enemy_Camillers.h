#ifndef __ENEMY_CAMILLERS_H__
#define __ENEMY_CAMILLERS_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Camillers : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_Camillers(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

private:
	// The path that will define the position in the world
	Path path;
	bool deleting;
	int par = 0;
	bool spawn = false;
	// Enemy animations
	Animation box;
	Animation boxidle;
	Animation front, back;
	Animation medicsWalking;
	Animation medicsHurt;
	Animation enemydeath1;
	Animation dissapear;
};			  

#endif // __ENEMY_CAMILLERS_H__#pragma once
