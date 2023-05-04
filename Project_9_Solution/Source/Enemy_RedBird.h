#ifndef __ENEMY_REDBIRD_H__
#define __ENEMY_REDBIRD_H__

#include "Enemy.h"

class Enemy_RedBird : public Enemy
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	Enemy_RedBird(int x, int y);

	// The enemy is going to perform a sinusoidal movement
	void Update() override;

private:
	// The position (as ratio) in the wave at a specific moment
	float waveRatio = 0.0f;

	// The speed at which the wave ratio is increased
	float waveRatioSpeed = 0.05f;

	// The original spawning position. The wave will be calculated from that
	int spawn_y = 0;
	bool deleting;
	// The total height of the wave
	int waveHeight = 15;
	int shootCooldown;
	// The enemy animation
	Animation flyAnim;
	Animation enemydeath2;

	Animation enemyshot2down;
	Animation enemyshot2rightdown;
	Animation enemyshot2right;
	Animation enemyshot2rightup;
	Animation enemyshot2up;
	Animation enemyshot2upleft;
	Animation enemyshot2left;
	Animation enemyshot2downleft;


	float dx;
		float dy;
};

#endif // __ENEMY_REDBIRD_H__