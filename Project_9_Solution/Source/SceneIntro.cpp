#include "SceneIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleUI.h"

SceneIntro::SceneIntro(bool startEnabled) : Module(startEnabled)
{

}

SceneIntro::~SceneIntro()
{

}

// Load assets
bool SceneIntro::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/Titlescreen.png");
	App->audio->PlayMusic("Assets/Music/introTitle.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;


	char lookupTable[] = { "0123456789:;(=)? abcdefghijklmnopqrstuvwxyz@!.-." };
	textFont = App->fonts->Load("Assets/Fonts/Small letter font.png", lookupTable, 3);

	text = "press space to start";
	App->player->Disable();
	App->enemies->Disable();
	App->UI->Disable();
	App->collisions->Disable();
	App->particles->Disable();

	return ret;
}

Update_Status SceneIntro::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
	}

	if (App->input->keys[SDL_SCANCODE_G] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 1);
	}
	
	counter++;
	if (counter == 60)
	{
		counter = 0;
		textOnScreen = !textOnScreen;
	}
	if (textOnScreen == true)
	{
		text = "press space to start";
	}
	else
	{
		text = nullptr;
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneIntro::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	App->fonts->BlitText(75, 170, textFont, text);

	return Update_Status::UPDATE_CONTINUE;
}