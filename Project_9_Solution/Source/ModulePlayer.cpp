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
	idleAnimUp.PushBack({ 0, 0, 28, 27 });

	// move upwards
	upAnim.PushBack({ 0, 0, 28, 27 });
	upAnim.PushBack({ 28, 0, 28, 27 });
	upAnim.PushBack({ 56, 0, 28, 27 });
	upAnim.PushBack({ 84, 0, 28, 27 });
	upAnim.PushBack({ 112, 0, 28, 27 });
	upAnim.PushBack({ 140, 0, 28, 27 });
	upAnim.PushBack({ 168, 0, 28, 27 });
	upAnim.PushBack({ 196, 0, 28, 27 });

	upAnim.speed = 0.2f;
	//up right
	upRightAnim.PushBack({ 0, 27, 28, 27 });
	upRightAnim.PushBack({ 28, 27, 28, 27 });
	upRightAnim.PushBack({ 56, 27, 28, 27 });
	upRightAnim.PushBack({ 84, 27, 28, 27 });
	upRightAnim.PushBack({ 112, 27, 28, 27 });
	upRightAnim.PushBack({ 140, 27, 28, 27 });
	upRightAnim.PushBack({ 168, 27, 28, 27 });
	upRightAnim.PushBack({ 196, 27, 28, 27 });

	upRightAnim.speed = 0.2f;


	//right
	rightAnim.PushBack({ 0, 54, 28, 27 });
	rightAnim.PushBack({ 28, 54, 28, 27 });
	rightAnim.PushBack({ 56, 54, 28, 27 });
	rightAnim.PushBack({ 84, 54, 28, 27 });
	rightAnim.PushBack({ 112, 54, 28, 27 });
	rightAnim.PushBack({ 140, 54, 28, 27 });
	rightAnim.PushBack({ 168, 54, 28, 27 });
	rightAnim.PushBack({ 196, 54, 28, 27 });

	rightAnim.speed = 0.2f;

	//left
	leftAnim.PushBack({ 0, 54, 28, 27 }, true);
	leftAnim.PushBack({ 28, 54, 28, 27 }, true);
	leftAnim.PushBack({ 56, 54, 28, 27 }), true;
	leftAnim.PushBack({ 84, 54, 28, 27 }, true);
	leftAnim.PushBack({ 112, 54, 28, 27 }, true);
	leftAnim.PushBack({ 140, 54, 28, 27 }, true);
	leftAnim.PushBack({ 168, 54, 28, 27 }, true);
	leftAnim.PushBack({ 196, 54, 28, 27 }, true);

	//down right
	downRightAnim.PushBack({ 0, 81, 28, 27 });
	downRightAnim.PushBack({ 28, 81, 28, 27 });
	downRightAnim.PushBack({ 56, 81, 28, 27 });
	downRightAnim.PushBack({ 84, 81, 28, 27 });
	downRightAnim.PushBack({ 112, 81, 28, 27 });
	downRightAnim.PushBack({ 140, 81, 28, 27 });
	downRightAnim.PushBack({ 168, 81, 28, 27 });
	downRightAnim.PushBack({ 196, 81, 28, 27 });

	leftAnim.speed = 0.2f;
	// Move down
	downAnim.PushBack({ 0, 108, 28, 27 });
	downAnim.PushBack({ 28, 108, 28, 27 });
	downAnim.PushBack({ 56, 108, 28, 27 });
	downAnim.PushBack({ 84, 108, 28, 27 });
	downAnim.PushBack({ 112, 108, 28, 27 });
	downAnim.PushBack({ 140, 108, 28, 27 });
	downAnim.PushBack({ 168, 108, 28, 27 });
	downAnim.PushBack({ 196, 108, 28, 27 });

	downAnim.speed = 0.2f;
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Sprites/SpritesSomersault.png");
	currentAnimation = &idleAnimUp;


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
		if (currentAnimation != &upRightAnim)
		{
			upRightAnim.Reset();
			currentAnimation = &upRightAnim;
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
		if (currentAnimation != &leftAnim)
		{
			leftAnim.Reset();
			currentAnimation = &leftAnim;
		}
	}
	else if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT && 
			 rightLock == false &&
			 isDodging == false)
	{
		moveDir = RIGHT;
		position.x += speed;
		if (currentAnimation != &rightAnim)
		{
			rightAnim.Reset();
			currentAnimation = &rightAnim;
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
		if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
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
		if (currentAnimation != &upAnim)
		{
			upAnim.Reset();
			currentAnimation = &upAnim;
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

	// If no up/down movement detected, set the current animation back to idle
	
	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE)
	{
		currentAnimation = &idleAnimUp;
	}

	if (App->input->keys[SDL_SCANCODE_N] == Key_State::KEY_DOWN && dodgeCoolDown > 20)
	{
		upAnim.Reset();
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
			if(position.x > App->render->camera.x)
			position.x -= speed * 3;
			break;
		case RIGHT:
			if (position.x < SCREEN_WIDTH + App->render->camera.x - collider->rect.w)
			position.x += speed * 3;
			break;
		case DOWN:
			if(position.y < App->render->camera.y + SCREEN_HEIGHT - collider->rect.h)
			position.y += speed * 3;
			break;
		case UP:
			if (position.y > App->render->camera.y)
				currentAnimation = &upAnim;
			position.y -= speed * 2;
			break;
		case DOWNLEFT:
			if (position.x > App->render->camera.x || position.y < App->render->camera.y + SCREEN_HEIGHT - collider->rect.h)
			{
				position.x -= speed * 3;
				position.y += speed * 3;
			}
			break;
		case DOWNRIGHT:
			if (position.x < SCREEN_WIDTH + App->render->camera.x - collider->rect.w || position.y < App->render->camera.y + SCREEN_HEIGHT - collider->rect.h)
			{
				position.x += speed * 3;
				position.y += speed * 3;
			}
			break;
		case UPLEFT:
			if (position.x > App->render->camera.x || position.y > App->render->camera.y)
			{
				position.x -= speed * 3;
				position.y -= speed * 3;
			}
			break;
		case UPRIGHT:
			if (position.x < SCREEN_WIDTH + App->render->camera.x - collider->rect.w || position.y > App->render->camera.y)
			{
				position.x += speed * 3;
				position.y -= speed * 3;
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

	colliderUp->SetPos(position.x, position.y - 3);
	colliderDown->SetPos(position.x, position.y + 14);
	colliderRight->SetPos(position.x + 30 , position.y );
	colliderLeft->SetPos(position.x, position.y);

	rightLock = false;
	leftLock = false;
	downLock = false;
	upLock = false;

	currentAnimation->Update();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
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
	App->fonts->BlitText(0, 0, scoreFont, scoreText);

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