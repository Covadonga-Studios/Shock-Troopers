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

	texture = App->textures->Load("Assets/Sprites/UI_EMELENTS.png");
	palmeratexture = App->textures->Load("Assets/Sprites/palmeras.png");

	char lookupTable[] = { "0123456789:;(=)? abcdefghijklmnopqrstuvwxyz@!.-." };
	generalFont = App->fonts->Load("Assets/Fonts/Small letter font.png", lookupTable, 3);
	char lookupTableTimer[] = { "0123456789" };
	timerFont = App->fonts->Load("Assets/Fonts/TIME number.png", lookupTableTimer);
	
	portraitRed.PushBack({ 240,16,16,16 });
	portraitWhite.PushBack({ 240,33,16,16 });

	weapon[0].PushBack({ 0,10,31,15 });
	weapon[1].PushBack({ 32,10,31,15 });
	weapon[2].PushBack({ 64,10,31,15 });

	infinityRect = { 119, 0, 16, 8 };

	timerRect = { 0, 0, 30, 8 };
	grenadeRect = { 241, 0, 15, 15 };
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

	//Temporal. normal 0, flame 1,, 3way 2
	int weapontype = App->player->weapon;

	currentWeapon = &weapon[weapontype];


	sprintf_s(scoreText, 10, "%08d", App->player->getScore());

	sprintf_s(timerText, 10, "%2d", App->player->getTimer());

	sprintf_s(grenadeText, 10, "%02d", App->player->grenadeCounter);
	
	sprintf_s(xText, 10, "%5d", App->player->position.x);
	sprintf_s(yText, 10, "%5d", App->player->position.y);


	//replace with the actual ammo variable when we have it
	sprintf_s(ammoText, 10, "%02d", App->player->bullets);


	
	App->render->Blit(palmeratexture, -42, -1300, NULL);
	
	App->fonts->BlitText(41, 8, generalFont, scoreText);
	App->fonts->BlitText(145, 17, timerFont, timerText);
	App->fonts->BlitText(24, 208, generalFont, grenadeText);

	
	if (App->collisions->debug)
	{
		App->fonts->BlitText(200, 8, generalFont, DebugText);
		App->fonts->BlitText(200, 24, generalFont, xText);
		App->fonts->BlitText(248, 24, generalFont, yText);


	}

	int x = App->render->camera.x;
	int y = App->render->camera.y;
	App->render->Blit(texture, x + 138, y + 8, &timerRect);

	//Blit each HP chunk in order
	for (int i = 0; i < 16; i++)
	{
		HPBar[i].hpRect = HPBar[i].hpState->GetCurrentFrame();
		App->render->Blit(texture, x + 8, y + 64 + (8 * i), &HPBar[i].hpRect);
	}

	if (red)
	{
		portrait = &portraitRed;
	}
	else
	{
		portrait = &portraitWhite;
	}
	if (portraitTimer == 2)
	{
		portraitTimer = 0;
		red = !red;
	}
	portraitTimer++;
		
	App->render->Blit(texture, x + 8, y + 16, &portrait->GetCurrentFrame());


	App->render->Blit(texture, x + 9, y + 201, &grenadeRect);


	weaponRect = currentWeapon->GetCurrentFrame();
	App->render->Blit(texture, x + 50, y + 201, &weaponRect);

	if (weapontype == 0)
	{
		App->render->Blit(texture, x + 84, y + 208, &infinityRect);
	}
	else
	{
		App->fonts->BlitText(84, 208, generalFont, ammoText);
	}



	App->render->Blit(texture, x + 8, y + 56, &hpRectUp);
	App->render->Blit(texture, x + 8, y + 192, &hpRectDown);

	return Update_Status::UPDATE_CONTINUE;
}