#include "CharacterScreen.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

CharacterScreen::CharacterScreen(bool startEnabled) : Module(startEnabled)
{

}

CharacterScreen::~CharacterScreen()
{

}

// Load assets
bool CharacterScreen::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture2 = App->textures->Load("Assets/Sprites/background titlescreen.png");
	bgTexture3 = App->textures->Load("Assets/Sprites/characterselect.png");
	boxTexture = App->textures->Load("Assets/Sprites/boxselect.png");
	selectFx = App->audio->LoadFx("Assets/Fx/cambiar seleccion.wav");
	acceptFx = App->audio->LoadFx("Assets/Fx/Aceptar seleccion.wav");
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status CharacterScreen::Update()
{
	timerpass++;
		
	
	if (App->input->keys[SDL_SCANCODE_G] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 1);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status CharacterScreen::PostUpdate()
{
	GamePad& pad = App->input->pads[0];

	if (pad.l_x < -0.2f && pad.l_x < 0.0f) {
		App->input->keys[SDL_SCANCODE_A] = Key_State::KEY_REPEAT;
	}
	if (pad.l_x > 0.2f && pad.l_x > 0.0f) {
		App->input->keys[SDL_SCANCODE_D] = Key_State::KEY_REPEAT;
	}
	if (pad.l_y > 0.2f && pad.l_y > 0.0f) {
		App->input->keys[SDL_SCANCODE_S] = Key_State::KEY_REPEAT;
	}
	if (pad.l_y < -0.2f && pad.l_y < 0.0f) {
		App->input->keys[SDL_SCANCODE_W] = Key_State::KEY_REPEAT;
	}
	if (pad.a == 1) {
		App->input->keys[SDL_SCANCODE_SPACE] = Key_State::KEY_DOWN;
	}


		App->render->Blit(bgTexture2, 20, 0);
	
	// Draw everything --------------------------------------

		App->render->Blit(bgTexture3, 24,25);

		if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT && boxx != 136 + 32 + 32 + 32 && timerpass > 10)
		{
			boxx += 32;
			timerpass = 0;
			App->audio->PlayFx(selectFx);
		}
		if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT && boxx != 136 && timerpass > 10)
		{
			boxx -= 32;
			timerpass = 0;
			App->audio->PlayFx(selectFx);
		}
		if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT && boxy != 30 && timerpass > 10)
		{
			boxy -= 32;
			timerpass = 0;
			App->audio->PlayFx(selectFx);
		}
		if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT && boxy != 30 + 32 && timerpass > 10)
		{
			boxy += 32;
			timerpass = 0;
			App->audio->PlayFx(selectFx);
		}

		if (boxx == 136 + 32 && boxy == 30 && App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN) 
		{
			App->audio->PlayFx(acceptFx);
			canPass = true;
		}

		if (canPass == true) 
		{
			App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 10);
		}

		if (canPass == false)
		App->render->Blit(boxTexture, boxx, boxy);
	

	return Update_Status::UPDATE_CONTINUE;
}