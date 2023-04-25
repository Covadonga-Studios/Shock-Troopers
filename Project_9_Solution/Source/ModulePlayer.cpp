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
	idleAnim.PushBack({ 66, 1, 32, 14 });

	// move upwards
	upAnim.PushBack({ 100, 1, 32, 14 });
	upAnim.PushBack({ 132, 0, 32, 14 });
	upAnim.loop = false;
	upAnim.speed = 0.1f;

	// Move down
	downAnim.PushBack({ 33, 1, 32, 14 });
	downAnim.PushBack({ 0, 1, 32, 14 });
	downAnim.loop = false;
	downAnim.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Sprites/ship.png");
	currentAnimation = &idleAnim;

	laserFx = App->audio->LoadFx("Assets/Fx/laser.wav");
	explosionFx = App->audio->LoadFx("Assets/Fx/explosion.wav");

	position.x = 150;
	position.y = 120;

	destroyed = false;

	collider = App->collisions->AddCollider({ position.x, position.y, 32, 16 }, Collider::Type::PLAYER, this);

	// TODO 0: Notice how a font is loaded and the meaning of all its arguments 
	//char lookupTable[] = { "!  ,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz" };
	//scoreFont = App->fonts->Load("Assets/Fonts/rtype_font.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 1);

	// TODO 4: Try loading "rtype_font3.png" that has two rows to test if all calculations are correct
	char lookupTable[] = { "0123456789:;(=)? abcdefghijklmnopqrstuvwxyz@!.-." };
	scoreFont = App->fonts->Load("Assets/Fonts/ShockTroopersSmallLetter.png", lookupTable, 3);

	return ret;
}

Update_Status ModulePlayer::Update()
{
	// Moving the player with the camera scroll
	shootCoolDown++;
	dodgeCoolDown++;
	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT && 
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
			 position.x < SCREEN_WIDTH + App->render->camera.x - collider->rect.w && 
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
			 position.x < SCREEN_WIDTH + App->render->camera.x - collider->rect.w && 
			 isDodging == false)
	{
		moveDir = UPRIGHT;
		position.x += speed;
		position.y -= speed;

		if (App->input->keys[SDL_SCANCODE_SPACE] != Key_State::KEY_REPEAT)
			bulletDir = UPRIGHT;
	}
	else if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT && isDodging == false)
	{
		moveDir = LEFT;
		position.x -= speed;

		if (App->input->keys[SDL_SCANCODE_SPACE] != Key_State::KEY_REPEAT)
			bulletDir = LEFT;
	}
	else if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT && 
			 position.x < SCREEN_WIDTH + App->render->camera.x - collider->rect.w && 
			 isDodging == false)
	{
		moveDir = RIGHT;
		position.x += speed;

		if (App->input->keys[SDL_SCANCODE_SPACE] != Key_State::KEY_REPEAT)
			bulletDir = RIGHT;
	}
	else if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT && isDodging == false)
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
	else if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT && isDodging == false)
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



	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_REPEAT && isDodging == false)
	{
		if (App->player->shootCoolDown > 10 && isDodging == false) {
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
	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE)
		currentAnimation = &idleAnim;

	if (App->input->keys[SDL_SCANCODE_N] == Key_State::KEY_DOWN && dodgeCoolDown > 20)
	{
		dodgeCoolDown = 0;

	}

	if (dodgeCoolDown < 10)
	{
		collider->SetPos(position.x + 20000, position.y + 20000);
		isDodging = true;
		switch (moveDir)
		{
		case LEFT:
			position.x -= speed * 3;
			break;
		case RIGHT:
			if (position.x < SCREEN_WIDTH + App->render->camera.x - collider->rect.w)
			position.x += speed * 3;
			break;
		case DOWN:
			position.y += speed * 3;
			break;
		case UP:
			position.y -= speed * 3;
			break;
		case DOWNLEFT:

			position.x -= speed * 3;
			position.y += speed * 3;
			break;
		case DOWNRIGHT:
			if (position.x < SCREEN_WIDTH + App->render->camera.x - collider->rect.w)
			{
				position.x += speed * 3;
				position.y += speed * 3;
			}
			break;
		case UPLEFT:
			position.x -= speed * 3;
			position.y -= speed * 3;
			break;
		case UPRIGHT:
			if (position.x < SCREEN_WIDTH + App->render->camera.x - collider->rect.w)
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

	currentAnimation->Update();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
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
	if (c1 == collider && destroyed == false)
	{
		App->particles->AddParticle(App->particles->explosion, position.x, position.y, Collider::Type::NONE, 9);
		App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, Collider::Type::NONE, 14);
		App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, Collider::Type::NONE, 40);
		App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, Collider::Type::NONE, 28);
		App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, Collider::Type::NONE, 21);

		App->audio->PlayFx(explosionFx);
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 60);

		destroyed = true;
	}

	if (c1->type == Collider::Type::PLAYER_SHOT && c2->type == Collider::Type::ENEMY)
	{
		score += 23;
	}
}