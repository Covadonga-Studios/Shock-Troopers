#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_scancode.h"

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

ModulePlayer::ModulePlayer()
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

	texture = App->textures->Load("Assets/ship.png");
	currentAnimation = &idleAnim;

	laserFx = App->audio->LoadFx("Assets/laser.wav");
	explosionFx = App->audio->LoadFx("Assets/explosion.wav");

	position.x = 150;
	position.y = 120;

	collider = App->collisions->AddCollider({ position.x, position.y, 32, 16}, Collider::Type::PLAYER, this);

	return ret;
}

update_status ModulePlayer::Update()
{
	// Moving the player with the camera scroll
	shootCoolDown++;
	dodgeCoolDown++;
	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
	moveDir = UPLEFT;
	position.x -= speed;
	position.y -= speed;

	if (App->input->keys[SDL_SCANCODE_SPACE] != KEY_STATE::KEY_REPEAT)
		bulletDir = UPLEFT;
	}
	else if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		moveDir = DOWNLEFT;
		position.x -= speed;
		position.y += speed;

		if(App->input->keys[SDL_SCANCODE_SPACE] != KEY_STATE::KEY_REPEAT)
		bulletDir = DOWNLEFT;
	}
	else if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		moveDir = DOWNRIGHT;	
		position.x += speed;
		position.y += speed;

		if (App->input->keys[SDL_SCANCODE_SPACE] != KEY_STATE::KEY_REPEAT)
			bulletDir = DOWNRIGHT;
	}
	else if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		moveDir = UPRIGHT;
		position.x += speed;
		position.y -= speed;

		if (App->input->keys[SDL_SCANCODE_SPACE] != KEY_STATE::KEY_REPEAT)
		bulletDir = UPRIGHT;
	}
	else if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		moveDir = LEFT;
		position.x -= speed;

		if (App->input->keys[SDL_SCANCODE_SPACE] != KEY_STATE::KEY_REPEAT)
		bulletDir = LEFT;
	}
	else if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		moveDir = RIGHT;
		position.x += speed;

		if (App->input->keys[SDL_SCANCODE_SPACE] != KEY_STATE::KEY_REPEAT )
		bulletDir = RIGHT;
	}
	else if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		moveDir = DOWN;
		position.y += speed;

		if (App->input->keys[SDL_SCANCODE_SPACE] != KEY_STATE::KEY_REPEAT)
		bulletDir = DOWN;
		if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
		}
	}
	else if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		moveDir = UP;
		position.y -= speed;

		if (App->input->keys[SDL_SCANCODE_SPACE] != KEY_STATE::KEY_REPEAT )
		bulletDir = UP;
			if (currentAnimation != &upAnim)
		{
			upAnim.Reset();
			currentAnimation = &upAnim;
		}
	}
	
	

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT && isDodging == false)
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
	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE)
		currentAnimation = &idleAnim;

	if (App->input->keys[SDL_SCANCODE_N] == KEY_STATE::KEY_DOWN )
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
	
	

	currentAnimation->Update();

	if (destroyed)
	{
		destroyedCountdown--;
		if (destroyedCountdown <= 0)
			return update_status::UPDATE_STOP;
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}

	return update_status::UPDATE_CONTINUE;
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

		destroyed = true;
	}
}