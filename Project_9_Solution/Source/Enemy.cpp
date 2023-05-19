#include "Enemy.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "Animation.h"

Enemy::Enemy(int x, int y) : position(x, y)
{
	spawnPos = position;
}

Enemy::~Enemy()
{
	if (collider != nullptr && collider->pendingToDelete == false)
		collider->pendingToDelete = true;
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Update()
{
	if (currentAnim != nullptr)
		currentAnim->Update();

	
}

void Enemy::Draw()
{
	bool mirror = currentAnim->GetMirror();

	if (currentAnim != nullptr)
		if (mirror == true)
		{
			App->render->BlitMirror(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));


		}
		else
		{
			App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
		}

	
}

void Enemy::OnCollision(Collider* collider)
{
	hp--;
	if (hp <= 0) 
	{
		App->audio->PlayFx(destroyedFx);

		SetToDelete();
	}

}

void Enemy::SetToDelete()
{
	App->player->score += 500;
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}