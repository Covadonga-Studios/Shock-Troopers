#ifndef __ENEMY_FINALBOSS_H__
#define __ENEMY_FINALBOSS_H__

#include "Enemy.h"

class Enemy_FinalBoss : public Enemy
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	Enemy_FinalBoss(int x, int y);

	// The enemy is going to perform a sinusoidal movement
	void Update() override;

private:
	// The position (as ratio) in the wave at a specific moment
	float waveRatio = 0.0f;

	// The speed at which the wave ratio is increased
	float waveRatioSpeed = 0.05f;

	// The original spawning position. The wave will be calculated from that
	int spawn_y = 0;
	bool deleting = false;
	// The total height of the wave
	int waveHeight = 15;
	int shootCooldown;
	// The enemy animation
	Animation flyAnim;
	Animation enemydeath1;

	Animation enemyshot1down;
	Animation enemyshot1rightdown;
	Animation enemyshot1rightdowndiagonal;
	Animation enemyshot1right;
	Animation enemyshot1rightup;
	Animation enemyshot1rightupdiagonal;
	Animation enemyshot1up;
	Animation enemyshot1upleft;
	Animation enemyshot1upleftdiagonal;
	Animation enemyshot1left;
	Animation enemyshot1downleft;
	Animation enemyshot1downleftdiagonal;

	Animation cannonDown;
	Animation cannonDownLeft;
	Animation cannonDownRight;
	Animation cannonLeft;
	Animation cannonRight;

	Animation bulletDown;
	Animation bulletDownLeft;
	Animation bulletDownRight;
	Animation bulletLeft;
	Animation bulletRight;

	Animation tankMissileRight;
	Animation tankMissileLeft;



	float dx;
	float dy;
};

#endif // __ENEMY_FINALBOSS_H__