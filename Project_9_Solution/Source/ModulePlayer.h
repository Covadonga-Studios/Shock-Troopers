#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer(bool startEnabled);

	// Destructor
	~ModulePlayer();

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
	Animation idleAnimUpLeg;
	Animation idleAnimDown;
	Animation idleAnimRight;
	Animation idleAnimLeft;
	Animation idleAnimDownLeft;
	Animation idleAnimDownRight;
	Animation idleAnimUpRight;
	Animation idleAnimUpLeft;

	Animation shootUpAnim;
	Animation upAnimLeg;
	Animation shootDownAnim;
	Animation downAnimLeg;
	Animation shootRightAnim;
	Animation rightAnimLeg;
	Animation shootLeftAnim;
	Animation leftAnimLeg;
	Animation shootUpLeftAnim;
	Animation shootUpRightAnim;
	Animation shootDownLeftAnim;
	Animation shootDownRightAnim;
	Animation upLeftAnimLeg;
	Animation upRightAnimLeg;
	Animation downLeftAnimLeg;
	Animation downRightAnimLeg;

	int bulletDir = 0;
	int moveDir = 0;
	int shootCoolDown = 10;
	int dodgeCoolDown = 10;
	int dodgeDuration = 15;
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
	// A flag to detect when the player has been destroyed
	bool destroyed = false;

	// Sound effects indices
	uint laserFx = 0;
	uint explosionFx = 0;

	// Font score index
	uint score = 000;
	int scoreFont = -1;
	char scoreText[10] = { "\0" };

};

#endif //!__MODULE_PLAYER_H__