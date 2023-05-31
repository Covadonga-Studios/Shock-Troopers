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
	grenadeImmunity++;

	if (currentAnim != nullptr)
		currentAnim->Update();

	if (currentAnim2 != nullptr)
		currentAnim2->Update();

	
}

float Enemy::Dircalculation(float Dx, float Dy)
{
	float dir = sqrt(Dx * Dx + Dy * Dy);
	return dir;
}

float Enemy::abss(float value)
{
	if (value < 0)
		return value * -1;
	else
		return value;
}

int Enemy::GetTargetDir(float dx, float dy)
{
	float diagonal = abss(dx / dy);


	if (diagonal >= 0.5f && diagonal <= 1.5f)
	{
		if (dx > 0 && dy > 0)
			return DOWNRIGHT;
		else if (dx > 0 && dy < 0)
			return UPRIGHT;
		else if (dx < 0 && dy > 0)
			return DOWNLEFT;
		else
			return UPLEFT;
	}
	else
	{
		if (abss(dx) > abss(dy))
		{
			if (dx >= 0)
				return RIGHT;
			else
				return LEFT;

		}
		else
		{
			if (dy >= 0)
				return DOWN;
			else
				return UP;
		}
	}


}


void Enemy::Draw()
{
	
	bool mirror = currentAnim->GetMirror();
	bool mirror2 = false;

	if (currentAnim2 != nullptr)
		mirror2 = currentAnim2->GetMirror();

	if (currentAnim2 != nullptr)
		if (mirror2 == true)
		{
			App->render->BlitMirror(texture2, position.x + offsettexture2x, position.y + offsettexture2y, &(currentAnim2->GetCurrentFrame()));

		}
		else
		{
			App->render->Blit(texture2, position.x + offsettexture2x, position.y + offsettexture2y, &(currentAnim2->GetCurrentFrame()));
		}

	if (currentAnim != nullptr)
		if (mirror == true)
		{
			App->render->BlitMirror(texture, position.x + offsettexture1x, position.y + offsettexture1y, &(currentAnim->GetCurrentFrame()));


		}
		else
		{
			App->render->Blit(texture, position.x + offsettexture1x, position.y + offsettexture1y, &(currentAnim->GetCurrentFrame()));
		}
	

	
}

void Enemy::OnCollision(Collider* collider)
{
	if (collider->type == Collider::Type::PLAYER_SHOT)
		hp--;

	if (collider->type == Collider::Type::GRENADE && grenadeImmunity > 120) 
	{
		hp =- 5;
		grenadeImmunity = 0;
	}
	

	if (hp <= 0) 
	{
		if (collider->type == Collider::Type::GRENADE)
			isOnFire = true;

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