#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleUI.h"

SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel1::~SceneLevel1()
{

}

// Load assets
bool SceneLevel1::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/TilesetPart1.png");
	bgTexture2 = App->textures->Load("Assets/Sprites/Tileset part 2(1_2).png");
	bgTexture3 = App->textures->Load("Assets/Sprites/background segundo vertical.png");
	App->audio->PlayMusic("Assets/Music/stage1.ogg", 1.0f);;

	//Bottomside collider
	
	 App->collisions->AddCollider({ 0, -2000, 10, 2424 }, Collider::Type::WALL);
	 //collider = App->collisions->AddCollider({ 0, 215, 600, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 360, -1310, 10, 2424 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, -1548, 1000, 10 }, Collider::Type::WALL);
	// Enemies ---
	//-1548

	App->enemies->AddEnemy(Enemy_Type::TANK, 70, 0);

	App->enemies->AddEnemy(Enemy_Type::BAZOOKA, 250, 150);

	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 140, -200);

	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 250, - 150);



	App->enemies->AddEnemy(Enemy_Type::HELICOPTER, 950, -1548);

	
	

	App->player->Enable();
	App->enemies->Enable();
	App->UI->Enable();
	App->collisions->Enable();
	

	return ret;
}

Update_Status SceneLevel1::Update()
{
	

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel1::PostUpdate()
{
	// Draw everything --------------------------------------
	//collider->SetPos(App->render->camera.x,App->render->camera.y + 215);
	 

	App->render->Blit(bgTexture, 0, -1820, NULL);
	App->render->Blit(bgTexture2, 0, -1548, NULL);
	App->render->Blit(bgTexture3, 2048, -1548 - 2020 + 238, NULL);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	App->player->Disable();
	App->enemies->Disable();
	App->UI->Disable();
	App->collisions->Disable();

	// TODO 5 (old): Remove All Memory Leaks - no solution here guys ;)

	return true;
}