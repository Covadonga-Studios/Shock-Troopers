#include "ModuleUI.h"


#include"ModulePlayer.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFonts.h"
#include <stdio.h>


ModuleUI::ModuleUI(bool startEnabled) : Module(startEnabled)
{

}

ModuleUI::~ModuleUI()
{

}

bool ModuleUI::Start()
{
	bool ret = true;




	texture = App->textures->Load("Assets/Sprites/spritesheet_definitiva_i_swear_i_swear.png");




	char lookupTable[] = { "0123456789:;(=)? abcdefghijklmnopqrstuvwxyz@!.-." };
	scoreFont = App->fonts->Load("Assets/Fonts/Small letter font.png", lookupTable, 3);
	char lookupTableTimer[] = { "0123456789" };
	timerFont = App->fonts->Load("Assets/Fonts/TIME number.png", lookupTableTimer);

	timerRect = { 0, 0, 30, 8 };

	for (int i = 0; i < 16; i++)
	{
		HPBar[i].hp8.PushBack({ 31,0,8,8 });
		HPBar[i].hp0.PushBack({ 95,0,8,8 });
	}

	hpRectUp = { 103, 0, 8, 8 };
	hpRectDown = { 111, 0, 8, 8 };

	return ret;
}

Update_Status ModuleUI::Update()
{
	

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleUI::PostUpdate()
{
	
	for (int i = 0; i < 16; i++)
	{
		if (App->player->getHP() >= App->player->maxHp - i)
		{
			HPBar[i].hpState = &HPBar[i].hp8;
		}
		else
		{
			HPBar[i].hpState = &HPBar[i].hp0;

		}
	}

	sprintf_s(scoreText, 10, "%08d", App->player->getScore());

	sprintf_s(timerText, 10, "%2d", App->player->getTimer());

	
	App->fonts->BlitText(41, 8, scoreFont, scoreText);
	App->fonts->BlitText(145, 17, timerFont, timerText);



	int x = App->render->camera.x;
	int y = App->render->camera.y;
	App->render->Blit(texture, x + 138, y + 8, &timerRect);




	for (int i = 0; i < 16; i++)
	{
		HPBar[i].hpRect = HPBar[i].hpState->GetCurrentFrame();
		App->render->Blit(texture, x + 8, y + 64 + (8 * i), &HPBar[i].hpRect);
	}

	App->render->Blit(texture, x + 8, y + 56, &hpRectUp);
	App->render->Blit(texture, x + 8, y + 192, &hpRectDown);

	return Update_Status::UPDATE_CONTINUE;
}


