#include "Enemy_BrownShip.h"
#include "Module.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"

Enemy_BrownShip::Enemy_BrownShip(int x, int y) : Enemy(x, y)
{
	fly.PushBack({5,72,21,22});
	currentAnim = &fly;
	path.PushBack({ -0.5f, 1 }, 100, &fly);
	path.PushBack({ 0.5f, -1 }, 100, &fly);
	
	// TODO 3: Have the Brown Cookies describe a path in the screen
	
	collider = App->collisions->AddCollider({0, 0, 24, 24}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_BrownShip::Update()
{
	shootCooldown++;
	/*path.Update();
	position = spawnPos + path.GetRelativePosition();*/

	if (shootCooldown > 70) 
	{
		
		App->particles->AddParticle(App->particles->laser, position.x - 20, position.y, 
		cos(atan2((App->player->position.y ) - position.y, (App->player->position.x ) - (position.x - 20))) * 4,
		sin(atan2((App->player->position.y ) - position.y, (App->player->position.x ) - (position.x - 20))) * 4, Collider::Type::ENEMY_SHOT);
		shootCooldown = 0;
	}


	
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
