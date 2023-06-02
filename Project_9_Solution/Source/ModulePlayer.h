#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

enum DIR
{
	NONE = -1,
	LEFT,
	RIGHT,
	DOWN,
	UP,
	DOWNLEFT,
	DOWNRIGHT,
	UPLEFT,
	UPRIGHT,
	UPRIGHTDIAGONAL,
	UPLEFTDIAGONAL,
	DOWNRIGHTDIAGONAL,
	DOWNLEFTDIAGONAL,

	MAX
};

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer(bool startEnabled);

	// Destructor
	~ModulePlayer();

	enum DIR
{
	NONE = -1,
	LEFT,
	RIGHT,
	DOWN,
	UP,
	DOWNLEFT,
	DOWNRIGHT,
	UPLEFT,
	UPRIGHT,
	UPRIGHTDIAGONAL,
	UPLEFTDIAGONAL,
	DOWNRIGHTDIAGONAL,
	DOWNLEFTDIAGONAL,


	MAX
};

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	Update_Status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	Update_Status PostUpdate() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

	void MoveUpdate();
	void GamepadUpdate();
	void ShootingUpdate();
	void AnimationLegTorsoUpdate();
	void DodgeUpdate();
	void LoseWinLogicUpdate();
	void GrenadeUpdate();
	void DebugLogicUpdate();
	void HurtUpdate();

public:
	// Position of the player in the map
	iPoint position;

	// The speed in which we move the player (pixels per frame)
	int speed = 1;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;
	
	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;
	Animation* legAnimation = nullptr;


	// A set of animations
	Animation idleAnimUp;
	Animation idleAnimDown;
	Animation idleAnimRight;
	Animation idleAnimLeft;
	Animation idleAnimDownLeft;
	Animation idleAnimDownRight;
	Animation idleAnimUpRight;
	Animation idleAnimUpLeft;

	Animation idleAnimUpLeg;
	Animation idleAnimUpRightLeg;
	Animation idleAnimUpLeftLeg;
	Animation idleAnimDownRightLeg;
	Animation idleAnimDownLeftLeg;
	Animation idleAnimRightLeg;
	Animation idleAnimLeftLeg;
	Animation idleAnimDownLeg;

	Animation shootUpAnim;
	Animation shootDownAnim;
	Animation shootRightAnim;
	Animation shootLeftAnim;
	Animation shootUpLeftAnim;
	Animation shootUpRightAnim;
	Animation shootDownLeftAnim;
	Animation shootDownRightAnim;
	

	Animation upAnimLeg;
	Animation downAnimLeg;
	Animation rightAnimLeg;
	Animation leftAnimLeg;
	Animation upLeftAnimLeg;
	Animation upRightAnimLeg;
	Animation downLeftAnimLeg;
	Animation downRightAnimLeg;

	Animation upAnimLegReverse;
	Animation downAnimLegReverse;
	Animation rightAnimLegReverse;
	Animation leftAnimLegReverse;
	Animation upLeftAnimLegReverse;
	Animation upRightAnimLegReverse;
	Animation downLeftAnimLegReverse;
	Animation downRightAnimLegReverse;


	Animation dissapear;

	Animation upDodge;
	Animation downDodge;
	Animation leftDodge;
	Animation rightDodge;
	Animation rightUpDodge;
	Animation leftUpDodge;
	Animation rightDownDodge;
	Animation leftDownDodge;

	Animation deathfront;
	Animation deathback;
	Animation deathright;
	Animation deathleft;
	Animation deathfrontright;
	Animation deathfrontleft;
	Animation deathbackright;
	Animation deathbackleft;

	Animation Win;

	Animation Hurtup;
	Animation Hurtdown;
	Animation Hurtleft;
	Animation Hurtright;
	Animation Hurtupleft;
	Animation Hurtupright;
	Animation Hurtdownright;
	Animation Hurtdownleft;

	Animation Grenade;
	Animation tankBullet;
	Animation explosion1;
	Animation explosionDefault;
	Animation blueBullet;
	Animation explosion2;

	Animation banana;
	Animation monkeyRight;
	Animation monkeyLeft;
	Animation monkeyHappy;
	Animation monkeyAngry;
	Animation monkeyLeavingRight;
	Animation monkeyLeavingLeft;

	Animation greyEnemyMeleeDown;

	Animation powerUpThreeBullets;

	Animation fogonazoDown;
	Animation fogonazoDownRight;
	Animation fogonazoDownLeft;
	Animation fogonazoUp;
	Animation fogonazoUpRight;
	Animation fogonazoUpLeft;
	Animation fogonazoRight;
	Animation fogonazoLeft;

	Animation peekyDownRight;
	Animation peekyDown;
	Animation peekyDownLeft;

	Animation flameThrower;

	Animation barricade;

	Animation missileLauncher;
	Animation missileLauncherBrokenBody;
	Animation missileLauncherBrokenTop;
	Animation missileLauncherTopRight;
	Animation missileLauncherTopLeft;
	Animation missileLauncherLeft;
	Animation missileLauncherRight;
	Animation missileLauncherDownLeft;
	Animation missileLauncherDownRight;

	Animation medicTent;
	Animation medicTentBroken;
	Animation towerBreaking;
	Animation tower2Breaking;

	Animation medicsWalking;
	Animation medicsHurt;

	Animation grenadeThrowRight;
	Animation grenadeThrowLeft;
	Animation grenadeThrowDownLeft;
	Animation grenadeThrowDownRight;
	Animation grenadeThrowUp;
	Animation grenadeThrowDown;
	Animation grenadeThrowUpRight;
	Animation grenadeThrowUpLeft;

	int bulletDir = 0;
	int moveDir = 0;
	int shootCoolDown = 10;
	int dodgeCoolDown = 30;
	int dodgeDuration = 15;
	int grenadeCoolDown = 20;
	bool isDodging = false;
	int dx;
	int dy;
	// The player's collider
	Collider* collider = nullptr;
	Collider* colliderUp = nullptr;
	Collider* colliderDown = nullptr;
	Collider* colliderRight = nullptr;
	Collider* colliderLeft = nullptr;
	bool upLock = false;
	bool downLock = false;
	bool rightLock = false;
	bool leftLock = false;
	bool upLeftLock;
	bool upRightLock;
	bool downLeftLock;
	bool downRightLock;
	bool isDead = false;
	// A flag to detect when the player has been destroyed
	bool destroyed = false;
	bool winCon = false;
	bool godMode = false;
	bool isHurt = false;
	bool isShooting = false;
	bool isThrowing = false;
	int grenadeAnimationTimer = 0;
	int hurtDuration = 0;
	int offsetx;
	int offsety;
	int offsetx2;
	int offsety2;
	int cartridge = 6; 
	int grenadeCounter = 15;
	bool invincible = false;
	int weapon = 1;
	int bullets = 0;

	int hp  = 120;
	int getHP() const
	{
		return hp;
	}
	const int maxHp = 128;
	// Sound effects indices
	uint laserFx = 0;
	uint explosionFx = 0;

	// Font score index
	uint score = 000;
	uint getScore() const
	{
		return score;
	}

	//time
	int timer = 99;
	int timerCounter = 0;
	int getTimer()const
	{
		return timer;
	}


	
	

};

#endif //!__MODULE_PLAYER_H__