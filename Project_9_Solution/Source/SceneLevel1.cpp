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


	App->audio->PlayMusic("Assets/Music/Stage 1.ogg", 1.0f);;

	//Bottomside collider

	App->collisions->AddCollider({ 0, -2000, 10, 2424 }, Collider::Type::WALL);
	//collider = App->collisions->AddCollider({ 0, 215, 600, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 360, -1310, 10, 2424 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, -1548, 1000, 10 }, Collider::Type::WALL);
	//PUENTE 1 COLLIDER
	App->collisions->AddCollider({ 870, -1561, 304, 141 }, Collider::Type::WALL);
	//PUENTE 2 COLLIDER
	App->collisions->AddCollider({ 2047, -2739, 105, 124 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 2246, -2722, 167, 122 }, Collider::Type::WALL);

	//colliders montañas
	App->collisions->AddCollider({ 2047, -2562, 47, 300 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 2090, -2522, 40, 230 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 2130, -2439, 30, 95 }, Collider::Type::WALL);

	App->collisions->AddCollider({ 2371, -2540, 47, 280 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 2335, -2500, 40, 200 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 2315, -2420, 30, 95 }, Collider::Type::WALL);
	// Enemies ---
	//-1548

	//Structures: 
	// 0 -> MedicTent
	// 1 ->tower1
	// 2 ->tower2

	//Itempickup: 
	// 0 -> Hpboost
	// 1 -> diamond
	// 2 ->bomb
	// 3 -> flamethrower
	// 4 -> threeway

	//Brownship (el huevon verde): 
	// 0 -> Parachute right spawn
	// 1 -> Parachute left spawn
	// 2 -> Corriendo hacia abajo
	// 3 -> Slideando abajo de la montaña
	// 4-> quietito 
	// 5-> prismaticos
	// 6 -> andando izauierda
	// 7-> corriendo izquierda

	//RedBird (el huevon blanco): 
	// 0 -> roll right 
	// 1 -> roll left
	// 3-> roll down right
	// 4 -> roll down left

	//Los tres barriles el 0 es sideways y el uno hacia abajo


	App->enemies->AddEnemy(Enemy_Type::STRUCTURES, 150, -300, 0);


	wave1 = false;
	wave2 = false;
	wave3 = false;
	wave4 = false;
	wave5 = false;
	wave6 = false;
	wave7 = false;
	wave8 = false;
	wave9 = false;
	wave10 = false;
	wave11 = false;
	wave12 = false;
	wave13 = false;
	wave14 = false;
	wave15 = false;
	wave16 = false;
	wave17 = false;
	wave18 = false;
	wave19 = false;
	wave20 = false;
	wave21 = false;
	wave22 = false;
	wave23 = false;

	doorspawn = false;
	helispawn = false;

	App->render->cameraMode = 0;

	helicopterArriving.PushBack({ 1515, 1056, 55, 38 });
	helicopterArriving.PushBack({ 1571, 1056, 55, 38 });

	currentAnimation = &helicopterArriving;
	return ret;
}

Update_Status SceneLevel1::Update()
{

	if (App->player->position.y >= 0 && wave1 == false) {

		//PRIMERA OLEADA
		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 90, -30, 0);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 270, -30, 1);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 22, -70, 0);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 338, -70, 1);



		wave1 = true;
	}


	if (App->player->position.y >= -100 && wave2 == false) {
		//OLEADA DE BARRILES 

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 100, -200, 2);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 250, -220, 4);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 10, -200, 0);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 200, -150, 4);

		App->enemies->AddEnemy(Enemy_Type::BARREL3, 230, -200, 1);
		//App->enemies->AddEnemy(Enemy_Type::ITEMPICKUP, 270, -190, 1);
		wave2 = true;
	}

	if (App->player->position.y >= -250 && wave3 == false) {
		//OLEADA PRIMER BLANCO

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 100, -300, 2);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 50, -300, 2);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 300, -300, 1);

		App->enemies->AddEnemy(Enemy_Type::REDBIRD, 250, -300, 1);
		wave3 = true;
	}

	if (App->player->position.y >= -400 && wave4 == false) {
		//PRIMERA OLEADA bis

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 50, -450, 0);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 250, -450, 1);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 0, -490, 0);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 300, -490, 1);
		wave4 = true;
	}

	if (App->player->position.y >= -530 && wave5 == false) {
		//INTERMEDIO

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 0, -580, 0);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 300, -580, 1);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 150, -690, 4);
		wave5 = true;
	}

	if (App->player->position.y >= -650 && wave6 == false) {
		//OLEADA BARRILES + BARRICADAS + CAJAS

		App->enemies->AddEnemy(Enemy_Type::MECH, 60, -700, 0);
		//App->enemies->AddEnemy(Enemy_Type::ITEMPICKUP, 76, -670, 3);

		App->enemies->AddEnemy(Enemy_Type::MECH, 220, -700, 0);
		//App->enemies->AddEnemy(Enemy_Type::ITEMPICKUP, 240, -670, 4);

		App->enemies->AddEnemy(Enemy_Type::BARREL, 80, -830, 0);

		App->enemies->AddEnemy(Enemy_Type::BARREL, 220, -830, 0);

		App->enemies->AddEnemy(Enemy_Type::BARREL3, 60, -820, 2);

		App->enemies->AddEnemy(Enemy_Type::BARREL3, 240, -820, 2);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 80, -870, 5);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 280, -870, 5);
		wave6 = true;
	}

	if (App->player->position.y >= -900 && wave7 == false) {
		//OLEADA BARRICADA SACOS 

		App->enemies->AddEnemy(Enemy_Type::BARRICADE, 72, -1050, 0);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 22, -950, 0);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 338, -1000, 1);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 22, -1000, 0);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 338, -1050, 1);

		App->enemies->AddEnemy(Enemy_Type::BARRICADE, 198, -1180, 0);
		//App->enemies->AddEnemy(Enemy_Type::ITEMPICKUP, 210, -1170, 0);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 22, -1180, 0);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 22, -1130, 0);
		wave7 = true;
	}

	if (App->player->position.y >= -1150 && wave8 == false) {
		//OLEADA TANKES + LANZACOHETES 

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 180, -1250, 4);

		App->enemies->AddEnemy(Enemy_Type::TANK, 100, -1300, 0);
		//	App->enemies->AddEnemy(Enemy_Type::ITEMPICKUP, 100, -1230, 4);

		App->enemies->AddEnemy(Enemy_Type::TANK, 240, -1301, 0);
		//App->enemies->AddEnemy(Enemy_Type::ITEMPICKUP, 240, -1231, 3);

		App->enemies->AddEnemy(Enemy_Type::BAZOOKA, 32, -1200, 0);

		App->enemies->AddEnemy(Enemy_Type::BAZOOKA, 318, -1241, 0);

		App->enemies->AddEnemy(Enemy_Type::BAZOOKA, 32, -1300, 0);

		App->enemies->AddEnemy(Enemy_Type::BAZOOKA, 318, -1301, 0);
		wave8 = true;
	}

	if (App->player->position.y >= -1300 && wave9 == false) {
		//OLEADA PREPUERTA

		App->enemies->AddEnemy(Enemy_Type::BARRICADE, 72, -1400, 5);
		//	App->enemies->AddEnemy(Enemy_Type::ITEMPICKUP, 92, -1380, 0);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 0, -1350, 0);
		wave9 = true;
	}

	if (App->player->position.y >= -1450 && wave10 == false) {
		//PUERTA OLEADA

		App->enemies->AddEnemy(Enemy_Type::TANK, 150, -1550, 0);
		//	App->enemies->AddEnemy(Enemy_Type::ITEMPICKUP, 150, -1450, 1);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 95, -1550, 2);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 200, -1550, 2);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 0, -1450, 0);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 0, -1500, 0);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 250, -1450, 0);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 250, -1500, 0);
		wave10 = true;
	}

	if (App->player->position.x >= 500 && wave11 == false) {
		//CAMINO AL PUENTE

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 450, -1600, 3);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 500, -1600, 3);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 550, -1600, 3);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 600, -1600, 3);


		wave11 = true;
	}

	if (App->player->position.x >= 650 && wave22 == false) {
		//PUENTE 1
		App->enemies->AddEnemy(Enemy_Type::BARREL3, 750, -1450, 0);

		App->enemies->AddEnemy(Enemy_Type::BARREL3, 750, -1400, 0);

		App->enemies->AddEnemy(Enemy_Type::TANKSTOP, 1000, -1420, 1);
		//	App->enemies->AddEnemy(Enemy_Type::ITEMPICKUP, 1025, -1380, 0);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 800, -1450, 5);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 800, -1400, 4);
		wave22 = true;
	}

	if (App->player->position.x >= 1050 && wave12 == false) {
		//PUENTE2 

		App->enemies->AddEnemy(Enemy_Type::MISSILELAUNCHER, 1150, -1410, 0);

		App->enemies->AddEnemy(Enemy_Type::MISSILELAUNCHER, 870, -1410, 1);

		App->enemies->AddEnemy(Enemy_Type::MECH, 1350, -1420, 0);
		//	App->enemies->AddEnemy(Enemy_Type::ITEMPICKUP, 1370, -1380, 3);

		wave12 = true;
	}

	if (App->player->position.x >= 1340 && wave13 == false) {
		//POST PUENTE OLEADA


		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 1440, -1420, 6);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 1440, -1490, 6);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 1440, -1360, 6);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 1540, -1420, 6);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 1540, -1360, 6);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 1540, -1490, 6);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 1450, -1600, 3);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 1500, -1600, 3);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 1550, -1600, 3);

		App->enemies->AddEnemy(Enemy_Type::TANKSTOP, 1700, -1420, 0);
		wave13 = true;
	}

	if (App->player->position.x >= 1650 && wave14 == false) {
		//TANKES POST PUENTE OLEADA


		//App->enemies->AddEnemy(Enemy_Type::ITEMPICKUP, 1750, -1370, 0);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 1650, -1600, 3);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 1700, -1600, 3);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 1750, -1600, 3);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 1800, -1600, 3);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 1850, -1600, 3);

		App->enemies->AddEnemy(Enemy_Type::TANKSTOP, 1850, -1520, 0);
		//App->enemies->AddEnemy(Enemy_Type::ITEMPICKUP, 1900, -1470, 4);

		App->enemies->AddEnemy(Enemy_Type::REDBIRD, 1800, -1420, 1);

		App->enemies->AddEnemy(Enemy_Type::TANKSTOP, 2000, -1420, 0);
		//App->enemies->AddEnemy(Enemy_Type::ITEMPICKUP, 2050, -1400, 1);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 1970, -1430, 6);

		App->enemies->AddEnemy(Enemy_Type::TANKSTOP, 2000, -1520, 0);
		App->enemies->AddEnemy(Enemy_Type::TANKSTOP, 2000, -1520, 1);
		wave14 = true;
	}

	if (App->player->position.x >= 2150 && wave15 == false) {

		//OLEADA DE PEÑA CORRIENDO

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 2200, -1500, 7);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 2250, -1500, 7);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 2300, -1500, 7);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 2350, -1500, 7);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 2200, -1400, 7);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 2250, -1400, 7);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 2300, -1400, 7);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 2350, -1400, 7);
		wave15 = true;
	}

	if (App->player->position.x >= 2150 && App->player->position.y >= 1550 && wave16 == false) {
		//PRIMERA OLEADA TERCERA PARTE

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 2200, -1600, 2);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 2250, -1600, 2);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 2300, -1600, 2);

		App->enemies->AddEnemy(Enemy_Type::REDBIRD, 2350, -1600, 4);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 2100, -1650, 2);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 2150, -1650, 2);
		wave16 = true;
	}

	if (App->player->position.y >= -1600 && wave17 == false) {
		//MONO MOMENTO OLEADAS

		App->enemies->AddEnemy(Enemy_Type::MECH, 2217, -1675, 0); //aqui iria el mono :'(

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 2200, -1731, 2);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 2240, -1751, 2);

		App->enemies->AddEnemy(Enemy_Type::MECH, 2200, -1750, 0);
		//App->enemies->AddEnemy(Enemy_Type::ITEMPICKUP, 2220, -1720, 0);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 2130, -1750, 2);
		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 2130, -1800, 2);
		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 2130, -1850, 2);
		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 2130, -1900, 2);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 2320, -1750, 2);
		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 2320, -1800, 2);
		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 2320, -1850, 2);
		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 2320, -1900, 2);
		wave17 = true;
	}

	if (App->player->position.y >= -1900 && wave18 == false) {
		//MEDICOZONA OLEADAS

		App->enemies->AddEnemy(Enemy_Type::STRUCTURES, 2262, -1890, 0);
		//App->enemies->AddEnemy(Enemy_Type::ITEMPICKUP, 2362, -1990, 0);

		App->enemies->AddEnemy(Enemy_Type::BARREL3, 2050, -1940, 2);
		App->enemies->AddEnemy(Enemy_Type::BARREL3, 2150, -1940, 2);

		App->enemies->AddEnemy(Enemy_Type::CAMILLER, 2250, -2000, 0);
		App->enemies->AddEnemy(Enemy_Type::CAMILLER, 2300, -2050, 0);
		App->enemies->AddEnemy(Enemy_Type::CAMILLER, 2250, -2100, 0);
		App->enemies->AddEnemy(Enemy_Type::CAMILLER, 2300, -2150, 0);
		wave18 = true;
	}

	if (App->player->position.y >= -2250 && wave19 == false) {
		//OLEADA DEL NEGRO

		App->enemies->AddEnemy(Enemy_Type::BLACKSOLDIER, 2227, -2360, 0);
		//	App->enemies->AddEnemy(Enemy_Type::ITEMPICKUP, 2227, -2360, 1);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 2047, -2440, 3);
		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 2382, -2440, 8);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 2047, -2400, 3);
		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 2382, -2400, 8);

		App->enemies->AddEnemy(Enemy_Type::MECH, 2120, -2584, 0);
		//	App->enemies->AddEnemy(Enemy_Type::ITEMPICKUP, 2140, -2554, 2);

		App->enemies->AddEnemy(Enemy_Type::MECH, 2210, -2584, 0);
		//	App->enemies->AddEnemy(Enemy_Type::ITEMPICKUP, 2230, -2554, 4);

		wave19 = true;
	}

	if (App->player->position.y >= -2750 && wave20 == false) {
		//PARTY POST PUENTE 

		App->enemies->AddEnemy(Enemy_Type::BARREL3, 2118, -2813, 1);
		App->enemies->AddEnemy(Enemy_Type::BARREL3, 2239, -2813, 1);
		//App->enemies->AddEnemy(Enemy_Type::ITEMPICKUP, 2249, -2793, 1);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 2099, -2840, 5);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 2178, -2874, 4);
		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 2258, -2874, 4);

		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 2099, -2927, 4);
		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 2227, -2927, 4);
		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 2324, -2927, 4);

		App->enemies->AddEnemy(Enemy_Type::STRUCTURES, 2065, -2921, 1);
		App->enemies->AddEnemy(Enemy_Type::STRUCTURES, 2340, -2921, 1);
		wave20 = true;
	}

	if (App->player->position.y >= -3150 && wave21 == false) {
		//BOSS ARENA1

		App->enemies->AddEnemy(Enemy_Type::STRUCTURES, 2343, -3129, 2);
		//App->enemies->AddEnemy(Enemy_Type::ITEMPICKUP, 2293, -3249, 0);

		App->enemies->AddEnemy(Enemy_Type::STRUCTURES, 2056, -3129, 2);

		wave21 = true;
	}

	if (App->player->position.y >= -3260 && wave23 == false) {
		//BOSS ARENA2


		App->enemies->AddEnemy(Enemy_Type::FINALBOSS, 2200, -3329, 0);
		wave23 = true;
	}

	///////////Separacion de spwneos////////////////////////Separacion de spwneos/////////////

	if (App->player->position.y < -1300 && doorspawn == false)
	{
		App->enemies->AddEnemy(Enemy_Type::DOOR, 103, -1536);
		doorspawn = true;

	}

	if (App->player->position.y < -1350 && App->render->cameraMode == 0)
	{
		App->player->kills = 0;
		App->render->cameraMode = 1;
		App->render->camera.x = 33;
		App->render->camera.y = -1536;
	}
	if (App->player->kills >= 3 && App->render->cameraMode == 1)
	{
		App->render->cameraMode = 2;
	}
	if (App->player->position.x >= 1030 && App->render->cameraMode == 2)
	{
		App->player->bigkill = 0;
		App->render->cameraMode = 3;
		App->render->camera.x = 877;
		App->render->camera.y = -1536;
	}
	if (App->player->bigkill == 1 && App->render->cameraMode == 3)
	{
		App->player->bigkill = 0;
		App->render->cameraMode = 4;
	}
	if (App->player->position.x >= 2150 && App->render->cameraMode == 4) {
		App->render->cameraMode = 5;
	}
	/*if (App->player->position.y <= -2280 && App->render->cameraMode == 5) {
		App->player->bigkill = 0;
		App->render->cameraMode = 6;
	}
	if (App->player->bigkill == 1 && App->render->cameraMode == 6) {

		App->render->cameraMode = 7;
	}*/
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
