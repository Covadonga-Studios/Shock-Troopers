#ifndef __ENEMY_BARRICADE_H__
#define __ENEMY_BARRICADE_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Barricade : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_Barricade(int x, int y);

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
	Animation barricade;
	Animation barricadedestroy;
	Animation peekyDownRight;
	Animation peekyDown;
	Animation peekyDownLeft;
	Animation enemydeath1;

	//checkear
	Animation lightMGenemyDownRight;
	Animation lightMGenemyDownLeft;
	Animation lightMGenemyDown;


	int shootCooldown = 0;
	int randomoffset = 0;
	float dx;
	float dy;
	int hpold;
};

#endif // __ENEMY_BARRICADE_H__