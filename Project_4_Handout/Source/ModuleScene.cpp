#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleScene::ModuleScene()
{

	int shipmov = -3;
	// ground
	ground.x = 8;
	ground.y = 391;
	ground.w = 896;
	ground.h = 72;

	// Background / sky
	background.x = 72;
	background.y = 208;
	background.w = 768;
	background.h = 176;

	// flag animation
	flag.PushBack({848, 208, 40, 40});
	flag.PushBack({848, 256, 40, 40});
	flag.PushBack({848, 304, 40, 40});
	flag.speed = 0.08f;

	ship.x = 8;
	ship.y = 24;
	ship.w = 521;
	ship.h = 181;

}

ModuleScene::~ModuleScene()
{

}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	stageTexture = App->textures->Load("Assets/ken_stage.png");

	return ret;
}

update_status ModuleScene::Update()
{
	flag.Update();

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleScene::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(stageTexture, 0, 0, &background, 0.75f); // sea and sky
	
	App->render->Blit(stageTexture, 560, 8, &(flag.GetCurrentFrame()), 0.75f); // flag animation

	
	//App->render->Blit();
	App->render->Blit(stageTexture, 0, shipMov, &ship);
	// TODO 2: Draw the ship from the sprite sheet with some parallax effect

	// TODO 3: Animate the girl on the ship (see sprite sheet)
	
	App->render->Blit(stageTexture, 0, 170, &ground);
	if (shipMov < -3 && wait > 40) 
	{
		shipMov++;
		wait = 0;
	}
	else if (wait > 40 && shipMov < 3)
	{
		shipMov--;
		wait = 0;
	}
	wait++;
	return update_status::UPDATE_CONTINUE;
}