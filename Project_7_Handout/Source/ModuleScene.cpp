#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"

ModuleScene::ModuleScene()
{

}

ModuleScene::~ModuleScene()
{

}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/background.png");
	App->audio->PlayMusic("Assets/stage1.ogg", 1.0f);

	//Bottomside collider
	App->collisions->AddCollider({ 0, 224, 3930, 16 }, Collider::Type::WALL);

	//First two columns colliders
	App->collisions->AddCollider({ 1375, 0, 111, 96 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1375, 145, 111, 96 }, Collider::Type::WALL);

	// Enemies ---
	App->enemies->AddEnemy(ENEMY_TYPE::MECH, 600, 190);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 700, 80);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 725, 80);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 740, 80);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 765, 80);
	// TODO 1: Add a new wave of red birds

	App->enemies->AddEnemy(ENEMY_TYPE::BROWNSHIP, 800, 80);
	App->enemies->AddEnemy(ENEMY_TYPE::BROWNSHIP, 845, 80);
	App->enemies->AddEnemy(ENEMY_TYPE::BROWNSHIP, 880, 80);
	App->enemies->AddEnemy(ENEMY_TYPE::BROWNSHIP, 925, 80);
	// TODO 2: Add a new wave of brown cookies

	// TODO 4: Create a new enemy type: The Mech


	return ret;
}

update_status ModuleScene::Update()
{
	//App->render->camera.x = App->player->position.x;

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleScene::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}