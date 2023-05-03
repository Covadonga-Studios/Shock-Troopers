#include "Enemy_RedBird.h"

#include "Module.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"
#include "stdio.h"


Enemy_RedBird::Enemy_RedBird(int x, int y) : Enemy(x, y)
{
	flyAnim.PushBack({ 5,6,24,24 });
	flyAnim.PushBack({ 38, 6, 24, 24 });
	flyAnim.PushBack({ 71, 6, 24, 24 });
	flyAnim.PushBack({ 104, 6, 24, 24 });
	flyAnim.PushBack({ 137, 6, 24, 24 });
	flyAnim.PushBack({ 170, 6, 24, 24 });
	flyAnim.PushBack({ 203, 6, 24, 24 });
	flyAnim.PushBack({ 236, 6, 24, 24 });
	flyAnim.speed = 0.2f;


	currentAnim = &flyAnim;

	collider = App->collisions->AddCollider({0, 0, 24, 24}, Collider::Type::ENEMY, (Module*)App->enemies);
}

float Dircalculation2(float Dx, float Dy)
{
	float dir = sqrt(Dx * Dx + Dy * Dy);
	return dir;


}

void Enemy_RedBird::Update()
{

	shootCooldown++;

	if (shootCooldown > 150)
	{

		float dx = (App->player->position.x + App->player->collider->rect.w / 2 - position.x);
		float dy = (App->player->position.y + App->player->collider->rect.h / 2 - position.y);
		float dir = Dircalculation2(dx, dy);

		float dirx = (dx * 1.5f / dir);
		float diry = (dy * 1.5f / dir);


		App->particles->AddParticle(App->particles->PlayerShotRight, position.x - 20, position.y, dirx, diry, Collider::Type::ENEMY_SHOT);

		App->particles->AddParticle(App->particles->PlayerShotRight, position.x - 20, position.y, dirx, diry, Collider::Type::ENEMY_SHOT, 20);
		shootCooldown = 0;
	}


	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
