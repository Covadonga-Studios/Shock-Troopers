#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "SDL/include/SDL_scancode.h"
#include <stdio.h>

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


	MAX
};

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	// idle animation - just one sprite
	downAnimLeg.PushBack({ 18,330,33,31 });
	downAnimLeg.PushBack({ 51,330,33,31 });
	downAnimLeg.PushBack({ 84,330,33,31 });
	downAnimLeg.PushBack({ 117,330,33,31 });
	downAnimLeg.PushBack({ 150,330,33,31 });
	downAnimLeg.PushBack({ 183,330,33,31 });
	downAnimLeg.PushBack({ 216,330,33,31 });
	downAnimLeg.PushBack({ 249,330,33,31 });
	downAnimLeg.speed = 0.1f;

	upAnimLeg.PushBack({ 18,454,33,31 });
	upAnimLeg.PushBack({ 51,454,33,31 });
	upAnimLeg.PushBack({ 84,454,33,31 });
	upAnimLeg.PushBack({ 117,454,33,31 });
	upAnimLeg.PushBack({ 150,454,33,31 });
	upAnimLeg.PushBack({ 183,454,33,31 });
	upAnimLeg.PushBack({ 216,454,33,31 });
	upAnimLeg.PushBack({ 249,454,33,31 });
	upAnimLeg.speed = 0.1f;

	leftAnimLeg.PushBack({ 18,392,33,31 }, true);
	leftAnimLeg.PushBack({ 51,392,33,31 }, true);
	leftAnimLeg.PushBack({ 84,392,33,31 }, true);
	leftAnimLeg.PushBack({ 117,392,33,31 }, true);
	leftAnimLeg.PushBack({ 150,392,33,31 }, true);
	leftAnimLeg.PushBack({ 183,392,33,31 }, true);
	leftAnimLeg.PushBack({ 216,392,33,31 }, true);
	leftAnimLeg.PushBack({ 249,392,33,31 }, true);
	leftAnimLeg.speed = 0.1f;

	rightAnimLeg.PushBack({ 18,392,33,31 });
	rightAnimLeg.PushBack({ 51,392,33,31 });
	rightAnimLeg.PushBack({ 84,392,33,31 });
	rightAnimLeg.PushBack({ 117,392,33,31 });
	rightAnimLeg.PushBack({ 150,392,33,31 });
	rightAnimLeg.PushBack({ 183,392,33,31 });
	rightAnimLeg.PushBack({ 216,392,33,31 });
	rightAnimLeg.PushBack({ 249,392,33,31 });
	rightAnimLeg.speed = 0.1f;

	upRightAnimLeg.PushBack({ 18,423,33,31 });
	upRightAnimLeg.PushBack({ 51,423,33,31 });
	upRightAnimLeg.PushBack({ 84,423,33,31 });
	upRightAnimLeg.PushBack({ 117,423,33,31 });
	upRightAnimLeg.PushBack({ 150,423,33,31 });
	upRightAnimLeg.PushBack({ 183,423,33,31 });
	upRightAnimLeg.PushBack({ 216,423,33,31 });
	upRightAnimLeg.PushBack({ 249,423,33,31 });
	upRightAnimLeg.speed = 0.1f;

	upLeftAnimLeg.PushBack({ 18,423,33,31 }, true);
	upLeftAnimLeg.PushBack({ 51,423,33,31 }, true);
	upLeftAnimLeg.PushBack({ 84,423,33,31 }, true);
	upLeftAnimLeg.PushBack({ 117,423,33,31 }, true);
	upLeftAnimLeg.PushBack({ 150,423,33,31 }, true);
	upLeftAnimLeg.PushBack({ 183,423,33,31 }, true);
	upLeftAnimLeg.PushBack({ 216,423,33,31 }, true);
	upLeftAnimLeg.PushBack({ 249,423,33,31 }, true);
	upLeftAnimLeg.speed = 0.1f;

	downRightAnimLeg.PushBack({ 18,361,33,31 });
	downRightAnimLeg.PushBack({ 51,361,33,31 });
	downRightAnimLeg.PushBack({ 84,361,33,31 });
	downRightAnimLeg.PushBack({ 117,361,33,31 });
	downRightAnimLeg.PushBack({ 150,361,33,31 });
	downRightAnimLeg.PushBack({ 183,361,33,31 });
	downRightAnimLeg.PushBack({ 216,361,33,31 });
	downRightAnimLeg.PushBack({ 249,361,33,31 });
	downRightAnimLeg.speed = 0.1f;

	downLeftAnimLeg.PushBack({ 18,361,33,31 }, true);
	downLeftAnimLeg.PushBack({ 51,361,33,31 }, true);
	downLeftAnimLeg.PushBack({ 84,361,33,31 }, true);
	downLeftAnimLeg.PushBack({ 117,361,33,31 }, true);
	downLeftAnimLeg.PushBack({ 150,361,33,31 }, true);
	downLeftAnimLeg.PushBack({ 183,361,33,31 }, true);
	downLeftAnimLeg.PushBack({ 216,361,33,31 }, true);
	downLeftAnimLeg.PushBack({ 249,361,33,31 }, true);
	downLeftAnimLeg.speed = 0.1f;

	idleAnimDown.PushBack({ 14,181,36,34 });
	idleAnimDown.PushBack({ 50,181,36,34 });
	idleAnimDown.PushBack({ 86,181,36,34 });
	idleAnimDown.PushBack({ 50,181,36,34 });
	idleAnimDown.speed = 0.13f;

	idleAnimUp.PushBack({ 14,147,36,34 });
	idleAnimUp.PushBack({ 50,147,36,34 });
	idleAnimUp.PushBack({ 86,147,36,34 });
	idleAnimUp.PushBack({ 50,147,36,34 });
	idleAnimUp.speed = 0.13f;

	idleAnimLeft.PushBack({ 14,45,36,34 });
	idleAnimLeft.PushBack({ 50,45,36,34 });
	idleAnimLeft.PushBack({ 86,45,36,34 });
	idleAnimLeft.PushBack({ 50,45,36,34 });
	idleAnimLeft.speed = 0.13f;

	idleAnimRight.PushBack({ 14,45,36,34 }, true);
	idleAnimRight.PushBack({ 50,45,36,34 }, true);
	idleAnimRight.PushBack({ 86,45,36,34 }, true);
	idleAnimRight.PushBack({ 50,45,36,34 }, true);
	idleAnimRight.speed = 0.13f;

	idleAnimDownLeft.PushBack({ 14,79,36,34 });
	idleAnimDownLeft.PushBack({ 50,79,36,34 });
	idleAnimDownLeft.PushBack({ 86,79,36,34 });
	idleAnimDownLeft.PushBack({ 50,79,36,34 });
	idleAnimDownLeft.speed = 0.13f;

	idleAnimDownRight.PushBack({ 14,79,36,34 }, true);
	idleAnimDownRight.PushBack({ 50,79,36,34 }, true);
	idleAnimDownRight.PushBack({ 86,79,36,34 }, true);
	idleAnimDownRight.PushBack({ 50,79,36,34 }, true);
	idleAnimDownRight.speed = 0.13f;

	idleAnimUpLeft.PushBack({ 14,249,36,34 });
	idleAnimUpLeft.PushBack({ 50,249,36,34 });
	idleAnimUpLeft.PushBack({ 86,249,36,34 });
	idleAnimUpLeft.PushBack({ 50,249,36,34 });
	idleAnimUpLeft.speed = 0.13f;

	idleAnimUpRight.PushBack({ 14,249,36,34 }, true);
	idleAnimUpRight.PushBack({ 50,249,36,34 }, true);
	idleAnimUpRight.PushBack({ 86,249,36,34 }, true);
	idleAnimUpRight.PushBack({ 50,249,36,34 }, true);
	idleAnimUpRight.speed = 0.13f;

	shootUpAnim.PushBack({ 122,147,36,34 });
	shootUpAnim.PushBack({ 158,147,36,34 });
	shootUpAnim.PushBack({ 194,147,36,34 });
	shootUpAnim.speed = 0.1f;

	shootDownAnim.PushBack({ 122,181,36,34 });
	shootDownAnim.PushBack({ 158,181,36,34 });
	shootDownAnim.PushBack({ 194,181,36,34 });
	shootDownAnim.speed = 0.1f;

	shootLeftAnim.PushBack({ 122,45,36,34 });
	shootLeftAnim.PushBack({ 158,45,36,34 });
	shootLeftAnim.PushBack({ 194,45,36,34 });
	shootLeftAnim.speed = 0.1f;

	shootRightAnim.PushBack({ 122,45,36,34 }, true);
	shootRightAnim.PushBack({ 158,45,36,34 }, true);
	shootRightAnim.PushBack({ 194,45,36,34 }, true);
	shootRightAnim.speed = 0.1f;

	shootDownLeftAnim.PushBack({ 122,79,36,34 });
	shootDownLeftAnim.PushBack({ 158,79,36,34 });
	shootDownLeftAnim.PushBack({ 194,79,36,34 });
	shootDownLeftAnim.speed = 0.1f;

	shootDownRightAnim.PushBack({ 122,79,36,34 }, true);
	shootDownRightAnim.PushBack({ 158,79,36,34 }, true);
	shootDownRightAnim.PushBack({ 194,79,36,34 }, true);
	shootDownRightAnim.speed = 0.1f;

	shootUpLeftAnim.PushBack({ 122,249,36,34 });
	shootUpLeftAnim.PushBack({ 158,249,36,34 });
	shootUpLeftAnim.PushBack({ 194,249,36,34 });
	shootUpLeftAnim.speed = 0.1f;

	shootUpRightAnim.PushBack({ 122,249,36,34 }, true);
	shootUpRightAnim.PushBack({ 158,249,36,34 }, true);
	shootUpRightAnim.PushBack({ 194,249,36,34 }, true);
	shootUpRightAnim.speed = 0.1f;

	///DODGE////////DODGE////////DODGE////////DODGE////////DODGE////////DODGE////////DODGE////////DODGE////////DODGE////////DODGE////////DODGE////////DODGE////////DODGE////////DODGE////////DODGE/////
	upDodge.PushBack({ 308,309, 41, 51 });
	upDodge.PushBack({ 349,309, 41, 51 });
	upDodge.PushBack({ 390,309, 41, 51 });
	upDodge.PushBack({ 431,309, 41, 51 });
	upDodge.PushBack({ 472,309, 41, 51 });
	upDodge.PushBack({ 513,309, 41, 51 });
	upDodge.PushBack({ 554,309, 41, 51 });
	upDodge.PushBack({ 595,309, 41, 51 });
	upDodge.speed = 0.35f;

	rightUpDodge.PushBack({ 308,360, 41, 51 });
	rightUpDodge.PushBack({ 349,360, 41, 51 });
	rightUpDodge.PushBack({ 390,360, 41, 51 });
	rightUpDodge.PushBack({ 431,360, 41, 51 });
	rightUpDodge.PushBack({ 472,360, 41, 51 });
	rightUpDodge.PushBack({ 513,360, 41, 51 });
	rightUpDodge.PushBack({ 554,360, 41, 51 });
	rightUpDodge.PushBack({ 595,360, 41, 51 });
	rightUpDodge.speed = 0.35f;

	leftUpDodge.PushBack({ 308,360, 41, 51 }, true);
	leftUpDodge.PushBack({ 349,360, 41, 51 }, true);
	leftUpDodge.PushBack({ 390,360, 41, 51 }, true);
	leftUpDodge.PushBack({ 431,360, 41, 51 }, true);
	leftUpDodge.PushBack({ 472,360, 41, 51 }, true);
	leftUpDodge.PushBack({ 513,360, 41, 51 }, true);
	leftUpDodge.PushBack({ 554,360, 41, 51 }, true);
	leftUpDodge.PushBack({ 595,360, 41, 51 }, true);
	leftUpDodge.speed = 0.35f;

	rightDodge.PushBack({ 308,411, 41, 51 });
	rightDodge.PushBack({ 349,411, 41, 51 });
	rightDodge.PushBack({ 390,411, 41, 51 });
	rightDodge.PushBack({ 431,411, 41, 51 });
	rightDodge.PushBack({ 472,411, 41, 51 });
	rightDodge.PushBack({ 513,411, 41, 51 });
	rightDodge.PushBack({ 554,411, 41, 51 });
	rightDodge.PushBack({ 595,411, 41, 51 });
	rightDodge.speed = 0.35f;

	leftDodge.PushBack({ 308,411, 41, 51 }, true);
	leftDodge.PushBack({ 349,411, 41, 51 }, true);
	leftDodge.PushBack({ 390,411, 41, 51 }, true);
	leftDodge.PushBack({ 431,411, 41, 51 }, true);
	leftDodge.PushBack({ 472,411, 41, 51 }, true);
	leftDodge.PushBack({ 513,411, 41, 51 }, true);
	leftDodge.PushBack({ 554,411, 41, 51 }, true);
	leftDodge.PushBack({ 595,411, 41, 51 }, true);
	leftDodge.speed = 0.35f;

	rightDownDodge.PushBack({ 308,462, 41, 51 });
	rightDownDodge.PushBack({ 349,462, 41, 51 });
	rightDownDodge.PushBack({ 390,462, 41, 51 });
	rightDownDodge.PushBack({ 431,462, 41, 51 });
	rightDownDodge.PushBack({ 472,462, 41, 51 });
	rightDownDodge.PushBack({ 513,462, 41, 51 });
	rightDownDodge.PushBack({ 554,462, 41, 51 });
	rightDownDodge.PushBack({ 595,462, 41, 51 });
	rightDownDodge.speed = 0.35f;

	leftDownDodge.PushBack({ 308,462, 41, 51 }, true);
	leftDownDodge.PushBack({ 349,462, 41, 51 }, true);
	leftDownDodge.PushBack({ 390,462, 41, 51 }, true);
	leftDownDodge.PushBack({ 431,462, 41, 51 }, true);
	leftDownDodge.PushBack({ 472,462, 41, 51 }, true);
	leftDownDodge.PushBack({ 513,462, 41, 51 }, true);
	leftDownDodge.PushBack({ 554,462, 41, 51 }, true);
	leftDownDodge.PushBack({ 595,462, 41, 51 }, true);
	leftDownDodge.speed = 0.35f;

	downDodge.PushBack({ 308,513, 41, 51 });
	downDodge.PushBack({ 349,513, 41, 51 });
	downDodge.PushBack({ 390,513, 41, 51 });
	downDodge.PushBack({ 431,513, 41, 51 });
	downDodge.PushBack({ 472,513, 41, 51 });
	downDodge.PushBack({ 513,513, 41, 51 });
	downDodge.PushBack({ 554,513, 41, 51 });
	downDodge.PushBack({ 595,513, 41, 51 });
	downDodge.speed = 0.35f;

	idleAnimDownLeg.PushBack({ 18, 299, 33, 31 });
	idleAnimDownRightLeg.PushBack({ 51, 299, 33, 31 });
	idleAnimRightLeg.PushBack({ 84, 299, 33, 31 });
	idleAnimUpRightLeg.PushBack({ 117, 299, 33, 31 });
	idleAnimUpLeg.PushBack({ 150, 299, 33, 31 });
	idleAnimUpLeftLeg.PushBack({ 183, 299, 33, 31 });
	idleAnimLeftLeg.PushBack({ 216, 299, 33, 31 });
	idleAnimDownLeftLeg.PushBack({ 249, 299, 33, 31 });

	dissapear.PushBack({0,0,0,0});

	//Death//Death//Death//Death//Death//Death//Death//Death//Death

	Deathup.PushBack({});
	Deathup.PushBack({});
	Deathup.PushBack({});
	Deathup.PushBack({});
	Deathup.PushBack({});
	Deathup.PushBack({});

	Deathdown.PushBack({});
	Deathdown.PushBack({});
	Deathdown.PushBack({});
	Deathdown.PushBack({});
	Deathdown.PushBack({});
	Deathdown.PushBack({});

	Deathright.PushBack({});
	Deathright.PushBack({});
	Deathright.PushBack({});
	Deathright.PushBack({});
	Deathright.PushBack({});
	Deathright.PushBack({});

	Deathleft.PushBack({});
	Deathleft.PushBack({});
	Deathleft.PushBack({});
	Deathleft.PushBack({});
	Deathleft.PushBack({});
	Deathleft.PushBack({});

	Deathupright.PushBack({});
	Deathupright.PushBack({});
	Deathupright.PushBack({});
	Deathupright.PushBack({});
	Deathupright.PushBack({});
	Deathupright.PushBack({});

	Deathupleft.PushBack({});
	Deathupleft.PushBack({});
	Deathupleft.PushBack({});
	Deathupleft.PushBack({});
	Deathupleft.PushBack({});
	Deathupleft.PushBack({});

	Deathdownright.PushBack({});
	Deathdownright.PushBack({});
	Deathdownright.PushBack({});
	Deathdownright.PushBack({});
	Deathdownright.PushBack({});
	Deathdownright.PushBack({});

	Deathdownleft.PushBack({});
	Deathdownleft.PushBack({});
	Deathdownleft.PushBack({});
	Deathdownleft.PushBack({});
	Deathdownleft.PushBack({});
	Deathdownleft.PushBack({});

	//Win//Win//Win//Win//Win//Win//Win//Win//Win//Win//Win//Win//Win//Win//Win//Win//Win//Win//Win//Win

	Win.PushBack({ 1312, 324, 40, 56 });
	Win.PushBack({ 1352, 324, 40, 56 });
	Win.PushBack({ 1392, 324, 40, 56 });
	Win.PushBack({ 1432, 324, 40, 56 });
	Win.PushBack({ 1472, 324, 40, 56 });
	Win.PushBack({ 1512, 324, 40, 56 });
	Win.PushBack({ 1552, 324, 40, 56 });
	Win.PushBack({ 1592, 324, 40, 56 });
	Win.PushBack({ 1352, 380, 40, 56 });
	Win.PushBack({ 1392, 380, 40, 56 });
	Win.PushBack({ 1432, 380, 40, 56 });
	Win.PushBack({ 1472, 380, 40, 56 });
	Win.PushBack({ 1512, 380, 40, 56 });
	Win.PushBack({ 1552, 380, 40, 56 });

	//Hurt//Hurt//Hurt//Hurt//Hurt//Hurt//Hurt//Hurt//Hurt//Hurt//Hurt//Hurt//Hurt//Hurt//Hurt//Hurt//Hurt//Hurt//Hurt//Hurt

	Hurtup.PushBack({ 1554, 19, 29, 56 });
	Hurtup.PushBack({ 1583, 19, 29, 56 });
	Hurtup.PushBack({ 1612, 19, 29, 56 });
	Hurtup.PushBack({ 1641, 19, 29, 56 });

	Hurtdown.PushBack({ 1554, 75, 29, 56 });
	Hurtdown.PushBack({ 1583, 75, 29, 56 });
	Hurtdown.PushBack({ 1612, 75, 29, 56 });
	Hurtdown.PushBack({ 1641, 75, 29, 56 });

	Hurtright.PushBack({ 1554, 131, 29, 56 });
	Hurtright.PushBack({ 1583, 131, 29, 56 });
	Hurtright.PushBack({ 1612, 131, 29, 56 });
	Hurtright.PushBack({ 1641, 131, 29, 56 });

	Hurtleft.PushBack({});
	Hurtleft.PushBack({});//mirror
	Hurtleft.PushBack({});
	Hurtleft.PushBack({});

	Hurtupleft.PushBack({});
	Hurtupleft.PushBack({});//mirror
	Hurtupleft.PushBack({});
	Hurtupleft.PushBack({});

	Hurtupright.PushBack({ 1554, 187, 29, 56 });
	Hurtupright.PushBack({ 1583, 187, 29, 56 });
	Hurtupright.PushBack({ 1612, 187, 29, 56 });
	Hurtupright.PushBack({ 1641, 187, 29, 56 });

	Hurtdownright.PushBack({ 1554, 243, 29, 56 });
	Hurtdownright.PushBack({ 1583, 243, 29, 56 });
	Hurtdownright.PushBack({ 1612, 243, 29, 56 });
	Hurtdownright.PushBack({ 1641, 243, 29, 56 });

	Hurtdownleft.PushBack({});
	Hurtdownleft.PushBack({});
	Hurtdownleft.PushBack({});//mirror
	Hurtdownleft.PushBack({});

}

ModulePlayer::~ModulePlayer()
{

}
bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Sprites/spritesheet definitiva.png");
	currentAnimation = &idleAnimUp;
	legAnimation = &upAnimLeg;

	laserFx = App->audio->LoadFx("Assets/Fx/laser.wav");
	explosionFx = App->audio->LoadFx("Assets/Fx/explosion.wav");

	position.x = 150;
	position.y = 120;

	destroyed = false;

	collider = App->collisions->AddCollider({ position.x, position.y, 32, 47 }, Collider::Type::PLAYER, this);
	colliderUp = App->collisions->AddCollider({ position.x, position.y -3, 28, 3 }, Collider::Type::UP_PLAYER, this);
	colliderDown = App->collisions->AddCollider({ position.x, position.y + 47, 28, 3 }, Collider::Type::DOWN_PLAYER, this);
	colliderRight = App->collisions->AddCollider({ position.x + 6, position.y, 3, 47 }, Collider::Type::RIGHT_PLAYER, this);
	colliderLeft = App->collisions->AddCollider({ position.x , position.y, 3, 47 }, Collider::Type::LEFT_PLAYER, this);
	
	timerRect = { 0, 0, 30, 8 };

	// TODO 0: Notice how a font is loaded and the meaning of all its arguments 
	//char lookupTable[] = { "!  ,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz" };
	//scoreFont = App->fonts->Load("Assets/Fonts/rtype_font.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 1);

	// TODO 4: Try loading "rtype_font3.png" that has two rows to test if all calculations are correct
	char lookupTable[] = { "0123456789:;(=)? abcdefghijklmnopqrstuvwxyz@!.-." };
	scoreFont = App->fonts->Load("Assets/Fonts/Small letter font.png", lookupTable, 3);
	char lookupTableTimer[] = { "0123456789" };
	timerFont= App->fonts->Load("Assets/Fonts/TIME number.png", lookupTableTimer);
	return ret;
}

Update_Status ModulePlayer::Update()
{
	shootCoolDown++;
	dodgeCoolDown++;

//////////////////MOVING//////////////////////////////MOVING//////////////////////////////MOVING//////////////////////MOVING/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT && 
		App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT &&
		leftLock == false &&
		upLock == false &&
		isDodging == false)
	{
		moveDir = UPLEFT;
		position.x -= speed;
		position.y -= speed;

		if (App->input->keys[SDL_SCANCODE_SPACE] != Key_State::KEY_REPEAT)
			bulletDir = UPLEFT;
		if (legAnimation != &upLeftAnimLeg)
		{
			upLeftAnimLeg.Reset();
			legAnimation = &upLeftAnimLeg;
		}
	}
	else if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT && 
			 App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT && 
			 leftLock == false &&
			 downLock == false &&
			 isDodging == false)
		{
			moveDir = DOWNLEFT;
			position.x -= speed;
			position.y += speed;

		if (App->input->keys[SDL_SCANCODE_SPACE] != Key_State::KEY_REPEAT)
			bulletDir = DOWNLEFT;
		if (legAnimation != &downLeftAnimLeg)
		{
			downRightAnimLeg.Reset();
			legAnimation = &downLeftAnimLeg;
		}
		}
	
	else if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT && 
			 App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT && 
			 rightLock == false &&
			 downLock == false &&
			 isDodging == false)
		 {
		moveDir = DOWNRIGHT;
		position.x += speed;
		position.y += speed;

		if (App->input->keys[SDL_SCANCODE_SPACE] != Key_State::KEY_REPEAT)
			bulletDir = DOWNRIGHT;
		if (legAnimation != &downRightAnimLeg)
		{
			downRightAnimLeg.Reset();
			legAnimation = &downRightAnimLeg;
		}
	}
	else if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT && 
			 App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT && 
			 rightLock == false && 
			 upLock == false &&  
			 isDodging == false)
	{
		moveDir = UPRIGHT;
		position.x += speed;
		position.y -= speed;

		if (App->input->keys[SDL_SCANCODE_SPACE] != Key_State::KEY_REPEAT)
			bulletDir = UPRIGHT;
		if (legAnimation != &upRightAnimLeg)
		{
			upRightAnimLeg.Reset();
			legAnimation = &upRightAnimLeg;
		}
	}
	else if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT &&
			 leftLock == false &&
			 isDodging == false)
	{
		moveDir = LEFT;
		position.x -= speed;

		if (App->input->keys[SDL_SCANCODE_SPACE] != Key_State::KEY_REPEAT)
			bulletDir = LEFT;
		if (legAnimation != &leftAnimLeg)
		{
			leftAnimLeg.Reset();
			legAnimation = &leftAnimLeg;
		}
	}
	else if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT && 
			 rightLock == false &&
			 isDodging == false)
	{
		moveDir = RIGHT;
		position.x += speed;
		if (legAnimation != &rightAnimLeg)
		{
			rightAnimLeg.Reset();
			legAnimation = &rightAnimLeg;
		}

		if (App->input->keys[SDL_SCANCODE_SPACE] != Key_State::KEY_REPEAT)
			bulletDir = RIGHT;
		
	}
	else if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT && 
			 downLock == false &&
			 isDodging == false)
	{
		moveDir = DOWN;
		position.y += speed;

		if (App->input->keys[SDL_SCANCODE_SPACE] != Key_State::KEY_REPEAT)
			bulletDir = DOWN;
		if (legAnimation != &downAnimLeg)
		{
			downAnimLeg.Reset();
			legAnimation= &downAnimLeg;
		}
	}
	else if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT &&
			 upLock == false &&
			 isDodging == false)
	{
		moveDir = UP;
		position.y -= speed;

		if (App->input->keys[SDL_SCANCODE_SPACE] != Key_State::KEY_REPEAT)
			bulletDir = UP;
		if (legAnimation != &upAnimLeg)
		{
			upAnimLeg.Reset();
			legAnimation = &upAnimLeg;
		}
	}


///////////////SHOOTING/////////////////////////////////SHOOTING/////////////////////////SHOOTING//////////////////////SHOOTING/////////////SHOOTING/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_REPEAT && isDodging == false)
	{
		if (App->player->shootCoolDown > 5 && isDodging == false) {
			switch (bulletDir)
			{
			case LEFT:
				App->particles->AddParticle(App->particles->PlayerShotLeft, position.x, position.y + 12, -5, 0, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(laserFx);
				shootCoolDown = 0;
				break;
			case RIGHT:
				App->particles->AddParticle(App->particles->PlayerShotRight, position.x + 20, position.y + 12, 5, 0, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(laserFx);
				shootCoolDown = 0;
				break;
			case DOWN:
				App->particles->AddParticle(App->particles->PlayerShotDown, position.x + 9, position.y + 26, 0, 5, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(laserFx);
				shootCoolDown = 0;
				break;
			case UP:
				App->particles->AddParticle(App->particles->PlayerShotUp, position.x + 17, position.y, 0, -5, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(laserFx);
				shootCoolDown = 0;
				break;
			case DOWNLEFT:
				App->particles->AddParticle(App->particles->PlayerShotDownLeft, position.x + 4, position.y + 18, -5, 5, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(laserFx);
				shootCoolDown = 0;
				break;
			case DOWNRIGHT:
				App->particles->AddParticle(App->particles->PlayerShotDownRight, position.x + 20, position.y + 18, 5, 5, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(laserFx);
				shootCoolDown = 0;
				break;
			case UPLEFT:
				App->particles->AddParticle(App->particles->PlayerShotUpLeft, position.x +4, position.y + 1, -5, -5, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(laserFx);
				shootCoolDown = 0;
				break;
			case UPRIGHT:
				App->particles->AddParticle(App->particles->PlayerShotUpRight, position.x + 20, position.y, 5, -5, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(laserFx);
				shootCoolDown = 0;
				break;
			}
		}


	}

	if (App->input->keys[SDL_SCANCODE_SPACE] != Key_State::KEY_REPEAT) {
		switch (moveDir)
		{
		case LEFT:
			currentAnimation = &idleAnimLeft;
			offsetx = 5;
			break;
		case RIGHT:
			currentAnimation = &idleAnimRight;
			offsetx = -2;
			break;
		case DOWN:
			currentAnimation = &idleAnimDown;
			offsety = -1;
			break;
		case UP:
			currentAnimation = &idleAnimUp;
			offsetx = 1;
			offsety = -1;
			break;
		case DOWNLEFT:
			currentAnimation = &idleAnimDownLeft;
			offsetx = 2;
			offsety = -1;
			break;
		case DOWNRIGHT:
			currentAnimation = &idleAnimDownRight;
			break;
		case UPLEFT:
			currentAnimation = &idleAnimUpLeft;
			offsetx = 4;
			offsety = -1;
			break;
		case UPRIGHT:
			currentAnimation = &idleAnimUpRight;
			offsetx = -1;
			offsety = -1;
			break;
		}
	}
	else 
	{
		switch (bulletDir)
		{
		case LEFT:
			currentAnimation = &shootLeftAnim;
			offsetx = 7;
			offsety = -1;
			break;
		case RIGHT:
			currentAnimation = &shootRightAnim;
			offsetx = -4;			
			break;
		case DOWN:
			currentAnimation = &shootDownAnim;
			break;
		case UP:
			currentAnimation = &shootUpAnim;
			break;
		case DOWNLEFT:
			currentAnimation = &shootDownLeftAnim;
			break;
		case DOWNRIGHT:
			currentAnimation = &shootDownRightAnim;
			break;
		case UPLEFT:
			currentAnimation = &shootUpLeftAnim;
			break;
		case UPRIGHT:
			currentAnimation = &shootUpRightAnim;		
			break;
		}
	}
	// If no up/down movement detected, set the current animation back to idle
	
	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE)
	{
		switch (moveDir)
		{
		case LEFT:
			legAnimation = &idleAnimLeftLeg;
			
			break;
		case RIGHT:
			legAnimation = &idleAnimRightLeg;

			break;
		case DOWN:
			legAnimation = &idleAnimDownLeg;
			break;
		case UP:
			legAnimation = &idleAnimUpLeg;
			break;
		case DOWNLEFT:
			legAnimation = &idleAnimDownLeftLeg;
			break;
		case DOWNRIGHT:
			legAnimation = &idleAnimDownRightLeg;
			break;
		case UPLEFT:
			legAnimation = &idleAnimUpLeftLeg;
			break;
		case UPRIGHT:
			legAnimation = &idleAnimUpRightLeg;
			break;
		}
	

	
	}

	if (App->input->keys[SDL_SCANCODE_N] == Key_State::KEY_DOWN && dodgeCoolDown > 30)
	{
	
		dodgeCoolDown = 0;

	}


	////////////////////////////////////////////////DODGE///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (dodgeCoolDown < 25)
	{

		collider->SetPos(position.x + 20000, position.y + 20000);
		isDodging = true;

		switch (moveDir)
		{
		case LEFT:
			if (!leftLock) 
			{
				currentAnimation = &leftDodge;
				position.x -= speed * 3;
			}
		
			break;
		case RIGHT:

			if (!rightLock) 
			{
				currentAnimation = &rightDodge;
				position.x += speed * 3;
			}

			break;
		case DOWN:
			if (!downLock) 
			{
				currentAnimation = &downDodge;
				position.y += speed * 3;
			}

			break;
		case UP:

			if (!upLock) 
			{
				currentAnimation = &upDodge;
				position.y -= speed * 3;
			}

			break;
		case DOWNLEFT:

			if (!downLock && !leftLock) 
			{
				currentAnimation = &leftDownDodge;
				position.x -= speed * 2;
				position.y += speed * 2;
			}

			
			break;
		case DOWNRIGHT:

			if (!downLock && !rightLock) 
			{
				currentAnimation = &rightDownDodge;
				position.x += speed * 2;
				position.y += speed * 2;
			}
		
			
			break;
		case UPLEFT:

			if (!upLock && !leftLock) 
			{
				currentAnimation = &leftUpDodge;
				position.x -= speed * 2;
				position.y -= speed * 2;
			}

			
			break;
		case UPRIGHT:

			if (!upLock && !rightLock) 
			{
				currentAnimation = &rightUpDodge;
				position.x += speed * 2;
				position.y -= speed * 2;
			}
			
			break;
		}
		shootCoolDown = 0;
	}
	else
	{
		collider->SetPos(position.x, position.y);


		isDodging = false;
	}

	colliderUp->SetPos(position.x+3, position.y - 3);
	colliderDown->SetPos(position.x +3 , position.y + 45);
	colliderRight->SetPos(position.x + 30 , position.y );
	colliderLeft->SetPos(position.x, position.y);

	if (isDodging && rightLock == false && leftLock == false && downLock == false && upLock == false)
	{
		legAnimation = &dissapear;
	}

	if (!isDodging) 
	{
		 upDodge.Reset();
		 downDodge.Reset();
		 leftDodge.Reset();
		 rightDodge.Reset();
		 rightUpDodge.Reset();
		 leftUpDodge.Reset();
		 rightDownDodge.Reset();
		 leftDownDodge.Reset();
	}

	rightLock = false;
	leftLock = false;
	downLock = false;
	upLock = false;
	



	currentAnimation->Update();
	legAnimation->Update();


	//Timer
	timerCounter++;
	if (timerCounter == 60)
	{
		timerCounter = 0;
		if (timer != 0)
		{
			timer--;

		}
	}
	


	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{

		SDL_Rect rectLeg = legAnimation->GetCurrentFrame();
		bool mirrorLeg = legAnimation->GetMirror();

		if (mirrorLeg == true)
		{
			App->render->BlitMirror(texture, position.x + offsetx, position.y +20 + offsety, &rectLeg);
			offsetx = 0;
			offsety = 0;
		}
		else
		{
			App->render->Blit(texture, position.x + offsetx , position.y +20+ offsety, &rectLeg);
			offsetx = 0;
			offsety = 0;
		}

		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		bool mirror = currentAnimation->GetMirror();
	
		if (mirror == true)
		{
			App->render->BlitMirror(texture, position.x, position.y, &rect);

			
		}
		else
		{
			App->render->Blit(texture, position.x, position.y, &rect);
		}

	}

	// Draw UI (score) --------------------------------------
	sprintf_s(scoreText, 10, "%08d", score);

	sprintf_s(timerText, 10, "%2d", timer);

	// TODO 3: Blit the text of the score in at the bottom of the screen
	App->fonts->BlitText(41, 8, scoreFont, scoreText);
	App->fonts->BlitText(145, 17, timerFont, timerText);
	
	
	
	int x = App->render->camera.x;
	int y = App->render->camera.y;
	App->render->Blit(texture, x+138, y+8, &timerRect);


	//App->fonts->BlitText(0 , 200, scoreFont, "this is just a font test");


	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{


	if (c1->type == Collider::Type::UP_PLAYER && c2->type == Collider::Type::WALL)
	{
		upLock = true;
	}

	if (c1->type == Collider::Type::DOWN_PLAYER && c2->type == Collider::Type::WALL)
	{
		downLock = true;
	}
	if (c1->type == Collider::Type::RIGHT_PLAYER && c2->type == Collider::Type::WALL)
	{
		rightLock = true;
	}
	if (c1->type == Collider::Type::LEFT_PLAYER && c2->type == Collider::Type::WALL)
	{
		leftLock = true;
	}


	if (c1->type == Collider::Type::PLAYER_SHOT && c2->type == Collider::Type::ENEMY)
	{
		score += 23;
	}

	if (c1->type == Collider::Type::ENEMY_SHOT && c2->type == Collider::Type::PLAYER)
	{
		hp--;
	}
}
