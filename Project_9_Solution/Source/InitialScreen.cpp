#include "InitialScreen.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

InitialScreen::InitialScreen(bool startEnabled) : Module(startEnabled)
{

}

InitialScreen::~InitialScreen()
{

}

// Load assets
bool InitialScreen::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture2 = App->textures->Load("Assets/Sprites/Titlescreen definitiva.png");


	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status InitialScreen::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status InitialScreen::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture2, 0, 0);

	return Update_Status::UPDATE_CONTINUE;
}