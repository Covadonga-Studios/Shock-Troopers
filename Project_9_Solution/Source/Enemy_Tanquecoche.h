#ifndef __ENEMY_TANQUECOCHE_H__
#define __ENEMY_TANQUECOCHE_H__

#include "Enemy.h"

class Enemy_Tanquecoche : public Enemy
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	Enemy_Tanquecoche(int x, int y);

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
	int deathTimer;
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

	Animation missileLauncher;

	Animation missileLauncherBrokenBody;
	Animation missileLauncherBrokenTop;

	Animation missileLauncherDownLeft;
	Animation missileLauncherDownRight;
	Animation missileLauncherLeft;
	Animation missileLauncherRight;
	Animation missileLauncherTopLeft;
	Animation missileLauncherTopRight;
	float dx;
	float dy;
	int test = 120;
};

#endif // __ENEMY_TANQUECOCHE_H__