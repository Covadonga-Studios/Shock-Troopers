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

	collider = App->collisions->AddCollider({ position.x, position.y, 32, 16 }, Collider::Type::PLAYER, this);
	colliderUp = App->collisions->AddCollider({ position.x, position.y -3, 32, 3 }, Collider::Type::UP_PLAYER, this);
	colliderDown = App->collisions->AddCollider({ position.x, position.y + 6, 32, 3 }, Collider::Type::DOWN_PLAYER, this);
	colliderRight = App->collisions->AddCollider({ position.x + 6, position.y, 3, 16 }, Collider::Type::RIGHT_PLAYER, this);
	colliderLeft = App->collisions->AddCollider({ position.x , position.y, 3, 16 }, Collider::Type::LEFT_PLAYER, this);
	


	// TODO 0: Notice how a font is loaded and the meaning of all its arguments 
	//char lookupTable[] = { "!  ,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz" };
	//scoreFont = App->fonts->Load("Assets/Fonts/rtype_font.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 1);

	// TODO 4: Try loading "rtype_font3.png" that has two rows to test if all calculations are correct
	char lookupTable[] = { "0123456789:;(=)? abcdefghijklmnopqrstuvwxyz@!.-." };
	scoreFont = App->fonts->Load("Assets/Fonts/Small letter font.png", lookupTable, 3);

	return ret;
}

Update_Status ModulePlayer::Update()
{
	

	
	shootCoolDown++;
	dodgeCoolDown++;

////////////////////////////////////////////////MOVING/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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


////////////////////////////////////////////////SHOOTING/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_REPEAT && isDodging == false)
	{
		if (App->player->shootCoolDown > 5 && isDodging == false) {
			switch (bulletDir)
			{
			case LEFT:
				App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, -5, 0, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(laserFx);
				shootCoolDown = 0;
				break;
			case RIGHT:
				App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, 5, 0, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(laserFx);
				shootCoolDown = 0;
				break;
			case DOWN:
				App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, 0, 5, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(laserFx);
				shootCoolDown = 0;
				break;
			case UP:
				App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, 0, -5, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(laserFx);
				shootCoolDown = 0;
				break;
			case DOWNLEFT:
				App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, -5, 5, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(laserFx);
				shootCoolDown = 0;
				break;
			case DOWNRIGHT:
				App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, 5, 5, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(laserFx);
				shootCoolDown = 0;
				break;
			case UPLEFT:
				App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, -5, -5, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(laserFx);
				shootCoolDown = 0;
				break;
			case UPRIGHT:
				App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, 5, -5, Collider::Type::PLAYER_SHOT);
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
			break;
		case RIGHT:
			currentAnimation = &idleAnimRight;
			break;
		case DOWN:
			currentAnimation = &idleAnimDown;
			break;
		case UP:
			currentAnimation = &idleAnimUp;
			break;
		case DOWNLEFT:
			currentAnimation = &idleAnimDownLeft;
			break;
		case DOWNRIGHT:
			currentAnimation = &idleAnimDownRight;
			break;
		case UPLEFT:
			currentAnimation = &idleAnimUpLeft;
			break;
		case UPRIGHT:
			currentAnimation = &idleAnimUpRight;
			break;
		}
	}
	else 
	{
		switch (bulletDir)
		{
		case LEFT:
			currentAnimation = &shootLeftAnim;
			break;
		case RIGHT:
			currentAnimation = &shootRightAnim;
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
		
	
	}

	if (App->input->keys[SDL_SCANCODE_N] == Key_State::KEY_DOWN && dodgeCoolDown > 20)
	{
	
		dodgeCoolDown = 0;

	}


	////////////////////////////////////////////////DODGE///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (dodgeCoolDown < 15)
	{
		collider->SetPos(position.x + 20000, position.y + 20000);
		isDodging = true;
		switch (moveDir)
		{
		case LEFT:
			
			position.x -= speed * 3;
			break;
		case RIGHT:
			
			position.x += speed * 3;
			break;
		case DOWN:
		
			position.y += speed * 3;
			break;
		case UP:
			
			position.y -= speed * 2;
			break;
		case DOWNLEFT:

				position.x -= speed * 3;
				position.y += speed * 3;
			
			break;
		case DOWNRIGHT:
			
				position.x += speed * 3;
				position.y += speed * 3;
			
			break;
		case UPLEFT:
			
				position.x -= speed * 3;
				position.y -= speed * 3;
			
			break;
		case UPRIGHT:
			
				position.x += speed * 3;
				position.y -= speed * 3;
			
			break;
		}
		shootCoolDown = 0;
	}
	else
	{
		collider->SetPos(position.x, position.y);


		isDodging = false;
	}

	colliderUp->SetPos(position.x, position.y - 3);
	colliderDown->SetPos(position.x, position.y + 14);
	colliderRight->SetPos(position.x + 30 , position.y );
	colliderLeft->SetPos(position.x, position.y);

	rightLock = false;
	leftLock = false;
	downLock = false;
	upLock = false;

	currentAnimation->Update();
	legAnimation->Update();

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
			App->render->BlitMirror(texture, position.x + offsetx, position.y + offsety, &rectLeg);
			offsetx = 0;
			offsety = 0;
		}
		else
		{
			App->render->Blit(texture, position.x + offsetx , position.y + offsety, &rectLeg);
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
	sprintf_s(scoreText, 10, "%7d", score);

	// TODO 3: Blit the text of the score in at the bottom of the screen
	//App->fonts->BlitText(0, 0, scoreFont, scoreText);

	App->fonts->BlitText(0 , 200, scoreFont, "this is just a font test");

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
	
}
