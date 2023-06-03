#include "ModuleEnemies.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"

#include "Enemy.h"
#include "Enemy_RedBird.h"
#include "Enemy_BrownShip.h"
#include "Enemy_Mech.h"
#include "Enemy_Barrel.h"
#include "Enemy_Tank.h"
#include "Enemy_TankStop.h"
#include "Enemy_Bazooka.h"
#include "Enemy_Helicopter.h"
#include "Enemy_ThreeBarrels.h"
#include "Enemy_BlackSoldier.h"
#include "Enemy_FinalBoss.h"
#include "Enemy_Barricade.h"
#include "Enemy_Door.h"
#include "Enemy_Tanquecoche.h"
#include "Enemy_Itempickup.h"
#include "Enemy_Camillers.h"
#include "Enemy_Structures.h"

#define SPAWN_MARGIN 50


ModuleEnemies::ModuleEnemies(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

ModuleEnemies::~ModuleEnemies()
{

}

bool ModuleEnemies::Start()
{
	texture = App->textures->Load("Assets/Sprites/spritesheet2.28.png");
	texture2 = App->textures->Load("Assets/Sprites/spritesheet2.28.png");
	texture3 = App->textures->Load("Assets/Sprites/spritesheet2.28.png");
	enemyDestroyedFx = App->audio->LoadFx("Assets/Fx/explosion.wav");

	return true;
}


Update_Status ModuleEnemies::PreUpdate()
{
	// Remove all enemies scheduled for deletion
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->pendingToDelete)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleEnemies::Update()
{
	HandleEnemiesSpawn();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
			enemies[i]->Update();
	}

	HandleEnemiesDespawn();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleEnemies::PostUpdate()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Draw();
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(Enemy_Type type, int x, int y, int enemyMode)
{
	bool ret = false;

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(spawnQueue[i].type == Enemy_Type::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			spawnQueue[i].enemyMode = enemyMode;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::HandleEnemiesSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type != Enemy_Type::NO_TYPE)
		{
			switch (App->render->cameraMode)
			{
			default:
				if (/*abs(spawnQueue[i].x - App->player->position.x) < 150 &&*/ abs(spawnQueue[i].y - App->player->position.y) < 100)
				{
					LOG("Spawning enemy at %d", spawnQueue[i].x * SCREEN_SIZE);

					SpawnEnemy(spawnQueue[i]);
					spawnQueue[i].type = Enemy_Type::NO_TYPE; // Removing the newly spawned enemy from the queue
				}
				break;
				break;

			case 1:
				if (/*abs(spawnQueue[i].x - App->player->position.x) < 150 &&*/ abs(spawnQueue[i].y - App->player->position.y) < 100)
				{
					LOG("Spawning enemy at %d", spawnQueue[i].x * SCREEN_SIZE);

					SpawnEnemy(spawnQueue[i]);
					spawnQueue[i].type = Enemy_Type::NO_TYPE; // Removing the newly spawned enemy from the queue
				}
				break;
			}
			// Spawn a new enemy if the screen has reached a spawn position
		
		}
	}
}

void ModuleEnemies::HandleEnemiesDespawn()
{
	// Iterate existing enemies
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			// Delete the enemy when it has reached the end of the screen
			if (enemies[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);

				enemies[i]->SetToDelete();
			}
		}
	}
}

void ModuleEnemies::SpawnEnemy(const EnemySpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] == nullptr)
		{
			switch (info.type)
			{
				case Enemy_Type::REDBIRD:
					enemies[i] = new Enemy_RedBird(info.x, info.y);
					break;
				case Enemy_Type::BROWNSHIP:
					enemies[i] = new Enemy_BrownShip(info.x, info.y);
					break;
				case Enemy_Type::MECH:
					enemies[i] = new Enemy_Mech(info.x, info.y);
					break;
				case Enemy_Type::BARREL:
					enemies[i] = new Enemy_Barrel(info.x, info.y);
					break;
				case Enemy_Type::TANK:
					enemies[i] = new Enemy_Tank(info.x, info.y);
					break;
				case Enemy_Type::TANKSTOP:
					enemies[i] = new Enemy_TankStop(info.x, info.y);
					break;
				case Enemy_Type::BAZOOKA:
					enemies[i] = new Enemy_Bazooka(info.x, info.y);
					break;
				case Enemy_Type::HELICOPTER:
					enemies[i] = new Enemy_Helicopter(info.x, info.y);
					break;
				case Enemy_Type::BARREL3:
					enemies[i] = new Enemy_ThreeBarrels(info.x, info.y);
					break;
				case Enemy_Type::BLACKSOLDIER:
					enemies[i] = new Enemy_BlackSoldier(info.x, info.y);
					break;
				case Enemy_Type::FINALBOSS:
					enemies[i] = new Enemy_FinalBoss(info.x, info.y);
					break;
				case Enemy_Type::BARRICADE:
					enemies[i] = new Enemy_Barricade(info.x, info.y);
					break;
				case Enemy_Type::DOOR:
					enemies[i] = new Enemy_Door(info.x, info.y);
					break;
				case Enemy_Type::MISSILELAUNCHER:
					enemies[i] = new Enemy_Tanquecoche(info.x, info.y);
					break;
				case Enemy_Type::ITEMPICKUP:
					enemies[i] = new Enemy_Itempickup(info.x, info.y);
					break;
				case Enemy_Type::CAMILLER:
					enemies[i] = new Enemy_Camillers(info.x, info.y);
					break;
				case Enemy_Type::STRUCTURES:
					enemies[i] = new Enemy_Structures(info.x, info.y);
					break;

			}
			enemies[i]->texture = texture;
			enemies[i]->texture2 = texture2;
			enemies[i]->texture3 = texture3;
			enemies[i]->destroyedFx = enemyDestroyedFx;
			enemies[i]->enemyMode = info.enemyMode;
			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			enemies[i]->hp;
			enemies[i]->OnCollision(c2); //Notify the enemy of a collision
			break;
		}
	}
}