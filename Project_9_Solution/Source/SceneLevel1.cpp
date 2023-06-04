#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleUI.h"
#include "Enemy_Helicopter.h"

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

	App->player->Enable();
	App->enemies->Enable();
	App->UI->Enable();
	App->collisions->Enable();
	App->particles->Enable();


	App->render->camera.x = 32;
	App->render->camera.y = 0;

	bgTexture = App->textures->Load("Assets/Sprites/TilesetPart1.png");
	bgTexture2 = App->textures->Load("Assets/Sprites/Tileset part 2(1_2).png");
	bgTexture3 = App->textures->Load("Assets/Sprites/background segundo vertical.png");
	bridgebg = App->textures->Load("Assets/Sprites/shocktro030.png");
	defaultspritesheet = App->textures->Load("Assets/Sprites/spritesheet2.29.png");
	defaultspritesheet2 = App->textures->Load("Assets/Sprites/spritesheet2.29.png");
	
	
	App->audio->PlayMusic("Assets/Music/stage1.ogg", 1.0f);;

	//Bottomside collider
	
	 App->collisions->AddCollider({ 0, -2000, 10, 2424 }, Collider::Type::WALL);
	 //collider = App->collisions->AddCollider({ 0, 215, 600, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 360, -1310, 10, 2424 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, -1548, 1000, 10 }, Collider::Type::WALL);

	
	// Enemies ---
	//-1548

	//Structures: 0 -> MedicTent, 1 ->tower1, 2 ->tower2
	//Itempickup: 0 -> Hpboost, 1 -> diamond, 2 ->bomb, 3 -> flamethrower, 4 -> threeway
	//Brownship (el huevon verde): 0 -> Parachute right spawn, 1 -> Parachute left spawn, 2 -> Corriendo hacia abajo, 3 -> Slideando abajo de la montaña 4-> quietito 5-> prismaticos
	//RedBird (el huevon blanco): 0 -> roll right, 1 -> roll left, 3-> roll down right, 4 -> roll down left
	//Los tres barriles el 0 es sideways y el uno hacia abajo
		
	
	//PRIMERA OLEADA
		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 90, -30,0);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 270, -60, 1);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 22, -100,0);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 338, -100, 1);

	//OLEADA DE BARRILES 
		
		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 100, -230, 2);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 250, -250, 4);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 10, -230, 0);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 200, -180, 4);

		App->enemies->AddEnemy(Enemy_Type::BARREL3, 230, -230, 1);

	//OLEADA PRIMER BLANCO

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 100, -330, 2);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 50, -330, 2);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 300, -330, 1);

		App->enemies->AddEnemy(Enemy_Type::REDBIRD, 250, -330, 1);

	//PRIMERA OLEADA bis

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 50, -480, 0);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 250, -480, 1);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 0, -520, 0);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 300, -520, 1);
	
	//INTERMEDIO

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 0, -610, 0);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 300, -610, 1);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 150, -720, 4);

	//OLEADA BARRILES + BARRICADAS

		App->enemies->AddEnemy(Enemy_Type::BARREL, 60, -830, 0);

		App->enemies->AddEnemy(Enemy_Type::BARREL, 220, -830, 0);

		App->enemies->AddEnemy(Enemy_Type::BARREL3, 60, -850, 2);

		App->enemies->AddEnemy(Enemy_Type::BARREL3, 240, -850, 2);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 80, -900, 5);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 280, -900, 5);

	//OLEADA BARRICADA SACOS 

		App->enemies->AddEnemy(Enemy_Type::BARRICADE, 72, -1080, 5);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 22, -980,0);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 338, -1030, 1);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 22, -1030,0);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 338, -1080, 1);

		App->enemies->AddEnemy(Enemy_Type::BARRICADE, 198, -1210, 5);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 22, -1210, 0);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 22, -1160, 0);

	//OLEADA TANKES + LANZACOHETES 

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 180, -1280, 4);

		App->enemies->AddEnemy(Enemy_Type::TANK, 100, -1330, 0);

		App->enemies->AddEnemy(Enemy_Type::TANK, 240, -1331, 0);

		App->enemies->AddEnemy(Enemy_Type::BAZOOKA, 32, -1230, 0);

		App->enemies->AddEnemy(Enemy_Type::BAZOOKA, 318, -1271, 0);

		App->enemies->AddEnemy(Enemy_Type::BAZOOKA, 32, -1330, 0);

		App->enemies->AddEnemy(Enemy_Type::BAZOOKA, 318, -1331, 0);

	//PUERTA OLEADA

		App->enemies->AddEnemy(Enemy_Type::TANK, 150, -1550, 0);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 95, -1550, 2);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 200, -1550, 2);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 0, -1400, 0);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 0, -1450, 0);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 250, -1400, 0);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 250, -1450, 0);

	//CAMINO AL PUENTE


		wave2 = false;
		doorspawn = false;
		helispawn = false;

	

	helicopterArriving.PushBack({ 1515, 1056, 55, 38 });
	helicopterArriving.PushBack({ 1571, 1056, 55, 38 });

	currentAnimation = &helicopterArriving;
	return ret;
}

Update_Status SceneLevel1::Update()
{
	if (App->player->position.y < -1300 && doorspawn == false)
	{
		App->enemies->AddEnemy(Enemy_Type::DOOR, 103, -1536);
		doorspawn = true;
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel1::PostUpdate()
{
	// Draw everything --------------------------------------
	//collider->SetPos(App->render->camera.x,App->render->camera.y + 215);
	SDL_Rect rect = currentAnimation->GetCurrentFrame();

	if (offsetheli >= 390 && helispawn == false)
	{
		App->enemies->AddEnemy(Enemy_Type::HELICOPTER, 988, -1649);
		helispawn = true;
	}

	

	App->render->Blit(bgTexture, 0, -1820, NULL);

	

	App->render->Blit(bridgebg, 891, -1548, NULL);
	if (App->player->position.x > 930 && offsetheli < 390)
	{
		offsetheli += 2;
		App->render->Blit(defaultspritesheet, 871 + offsetheli, -1470, &rect);
	}
	
	App->render->Blit(bgTexture2, 0, -1548, NULL);
	App->render->Blit(bgTexture3, 2048, -1548 - 2020 + 238, NULL);


	currentAnimation->Update();
	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	App->player->Disable();
	App->enemies->Disable();
	App->UI->Disable();
	App->collisions->Disable();
	App->particles->Disable();

	

	return true;
}