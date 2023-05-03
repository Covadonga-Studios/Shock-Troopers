#include "Enemy_BrownShip.h"
#include "Module.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"
#include "stdio.h"

Enemy_BrownShip::Enemy_BrownShip(int x, int y) : Enemy(x, y)
{
	fly.PushBack({5,72,21,22});
	currentAnim = &fly;
	
	path.PushBack({-1.0f, -0.5f}, 100);
	path.PushBack({-1.0f, 0.5f}, 80);
	path.PushBack({-1.0f, 1.0f}, 80);
	
	collider = App->collisions->AddCollider({0, 0, 24, 24}, Collider::Type::ENEMY, (Module*)App->enemies);
}

float Dircalculation(float Dx, float Dy) 
{
	float dir = sqrt(Dx * Dx + Dy * Dy);
	return dir;
}

void Enemy_BrownShip::Update()
{
	shootCooldown++;

	if (shootCooldown > 150)
	{

		float dx = (App->player->position.x + App->player->collider->rect.w/2 - position.x);
		float dy = (App->player->position.y + App->player->collider->rect.h/2 - position.y);
		float dir = Dircalculation(dx, dy);

		float dirx = (dx * 1.5f / dir);
		float diry = (dy * 1.5f / dir);
		
		
		App->particles->AddParticle(App->particles->laser, position.x - 20, position.y,dirx, diry, Collider::Type::ENEMY_SHOT);
		shootCooldown = 0;
	}
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
