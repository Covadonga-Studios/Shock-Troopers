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
	//Initialise each sprite for each chunk
	for (int i = 0; i < 16; i++)
	{
		HPBar[i].hp8.PushBack({ 31,0,8,8 });
		HPBar[i].hp7.PushBack({ 39,0,8,8 });
		HPBar[i].hp6.PushBack({ 47,0,8,8 });
		HPBar[i].hp5.PushBack({ 55,0,8,8 });
		HPBar[i].hp4.PushBack({ 63,0,8,8 });
		HPBar[i].hp3.PushBack({ 71,0,8,8 });
		HPBar[i].hp2.PushBack({ 79,0,8,8 });
		HPBar[i].hp1.PushBack({ 87,0,8,8 });
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
	//Assign a sprite to each chunk based on current HP
	for (int i = 0; i < 16; i++)
	{
		if (App->player->getHP() >= App->player->maxHp - (8 * i))
		{
			HPBar[i].hpState = &HPBar[i].hp8;
		}
		else if (App->player->getHP() == App->player->maxHp - (8 * i) - 1)
		{
			HPBar[i].hpState = &HPBar[i].hp7;
		}
		else if (App->player->getHP() == App->player->maxHp - (8 * i) - 2)
		{
			HPBar[i].hpState = &HPBar[i].hp6;
		}
		else if (App->player->getHP() == App->player->maxHp - (8 * i) - 3)
		{
			HPBar[i].hpState = &HPBar[i].hp5;
		}
		else if (App->player->getHP() == App->player->maxHp - (8 * i) - 4)
		{
			HPBar[i].hpState = &HPBar[i].hp4;
		}
		else if (App->player->getHP() == App->player->maxHp - (8 * i) - 5)
		{
			HPBar[i].hpState = &HPBar[i].hp3;
		}
		else if (App->player->getHP() == App->player->maxHp - (8 * i) - 6)
		{
			HPBar[i].hpState = &HPBar[i].hp2;
		}
		else if (App->player->getHP() == App->player->maxHp - (8 * i) - 7)
		{
			HPBar[i].hpState = &HPBar[i].hp1;
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



	//Blit each HP chunk in order
	for (int i = 0; i < 16; i++)
	{
		HPBar[i].hpRect = HPBar[i].hpState->GetCurrentFrame();
		App->render->Blit(texture, x + 8, y + 64 + (8 * i), &HPBar[i].hpRect);
	}

	App->render->Blit(texture, x + 8, y + 56, &hpRectUp);
	App->render->Blit(texture, x + 8, y + 192, &hpRectDown);

	return Update_Status::UPDATE_CONTINUE;
}


