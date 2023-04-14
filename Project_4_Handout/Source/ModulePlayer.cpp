#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"

#include "SDL/include/SDL_scancode.h"

// Street Fighter reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	position.x = 100;
	position.y = 220;

	// idle animation (arcade sprite sheet)
	idleAnim.PushBack({7, 14, 60, 90});
	idleAnim.PushBack({95, 15, 60, 89});
	idleAnim.PushBack({184, 14, 60, 90});
	idleAnim.PushBack({276, 11, 60, 93});
	idleAnim.PushBack({366, 12, 60, 92});
	idleAnim.speed = 0.2f;

	// walk forward animation (arcade sprite sheet)
	forwardAnim.PushBack({9, 136, 53, 83});
	forwardAnim.PushBack({78, 131, 60, 88});
	forwardAnim.PushBack({162, 128, 64, 92});
	forwardAnim.PushBack({259, 128, 63, 90});
	forwardAnim.PushBack({352, 128, 54, 91});
	forwardAnim.PushBack({432, 131, 50, 89});
	forwardAnim.speed = 0.1f;

	// TODO 4: Make ryu walk backwards with the correct animations

	backwardAnim.PushBack({ 541,131,63,88});
	backwardAnim.PushBack({ 626,129,62,91 });
	backwardAnim.PushBack({ 712,128,58,91 });
	backwardAnim.PushBack({ 796,127,60,91 });
	backwardAnim.PushBack({ 882,128,60,91 });
	backwardAnim.PushBack({ 973,123,58,90 });
	backwardAnim.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/ryu.png"); // arcade version

	return ret;
}

update_status ModulePlayer::Update()
{
	//Reset the currentAnimation back to idle before updating the logic
	currentAnimation = &idleAnim;

	if(App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT)
	{
		currentAnimation = &forwardAnim;
		position.x += speed;
	}

	if (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT)
	{
		currentAnimation = &backwardAnim;
		position.x -= speed;
	}

	if (App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT)
	{
		currentAnimation = &backwardAnim;
		position.y -= speed;
	}

	if (App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT)
	{
		currentAnimation = &backwardAnim;
		position.y += speed;
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT)
	{
		App->particles
	}

	// TODO 4: Make ryu walk backwards with the correct animations

	currentAnimation->Update();

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	App->render->Blit(texture, position.x, position.y - rect.h, &rect);

	return update_status::UPDATE_CONTINUE;
}