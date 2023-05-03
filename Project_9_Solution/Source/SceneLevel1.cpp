#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"

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
	App->audio->PlayMusic("Assets/Music/stage1.ogg", 1.0f);

	//Bottomside collider
	
	collider = App->collisions->AddCollider({ 0, 0, 10, 224 }, Collider::Type::WALL);
	// Enemies ---
	

	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 100, 100);

	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 150, 150);

	
	

	App->player->Enable();
	App->enemies->Enable();

	return ret;
}

Update_Status SceneLevel1::Update()
{
	collider->SetPos(App->render->camera.x, App->render->camera.y);

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel1::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, -1820, NULL);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	App->player->Disable();
	App->enemies->Disable();

	// TODO 5 (old): Remove All Memory Leaks - no solution here guys ;)

	return true;
}