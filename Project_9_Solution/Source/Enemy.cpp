#include "Enemy.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "Animation.h"
#include "ModuleEnemies.h"

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
	flameImmunity++;
	drop++;

	if (drop > 50) 
	{
		drop = 0;
	}

	if (collider == nullptr && pendingToDelete == false ) {
		pendingToDelete = true;

	}

	if (currentAnim != nullptr)
		currentAnim->Update();

	if (currentAnim2 != nullptr)
		currentAnim2->Update();

	if (currentAnim3 != nullptr)
		currentAnim3->Update();

	if (die == true)
	SetToDelete();
	
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
	
	bool mirror = false;
	bool mirror2 = false;
	bool mirror3 = false;

	if (currentAnim3 != nullptr)
		mirror3 = currentAnim3->GetMirror();

	if (currentAnim3 != nullptr)
		if (mirror3 == true)
		{
			App->render->BlitMirror(texture3, position.x + offsettexture3x, position.y + offsettexture3y, &(currentAnim3->GetCurrentFrame()));

		}
		else
		{
			App->render->Blit(texture3, position.x + offsettexture3x, position.y + offsettexture3y, &(currentAnim3->GetCurrentFrame()));
		}

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
		mirror = currentAnim->GetMirror();

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

	if (this->collider->type == Collider::Type::ITEM && collider->type == Collider::Type::PLAYER)
		hp--;

	if (collider->type == Collider::Type::FLAME && flameImmunity > 7) 
	{
		hp -= 3;
		flameImmunity = 0;
	}
	

	if (collider->type == Collider::Type::GRENADE && grenadeImmunity > 120) 
	{
		hp -= 42;
		grenadeImmunity = 0;
	}
	

	if (hp <= 0 )
		
	{
		if (collider->type == Collider::Type::GRENADE || collider->type == Collider::Type::FLAME)
			isOnFire = true;

		App->audio->PlayFx(destroyedFx);
		if (dropped == false && this->collider->type != Collider::Type::ITEM)
	{

		switch (drop)
		{
		default:

			break;
		case 10:
			App->enemies->AddEnemy(Enemy_Type::ITEMPICKUP, position.x, position.y, 0);
			break;
		case 27:
			App->enemies->AddEnemy(Enemy_Type::ITEMPICKUP, position.x, position.y, 1);
			break;
		case 35:
			App->enemies->AddEnemy(Enemy_Type::ITEMPICKUP, position.x, position.y, 2);
			break;
		case 23:
			App->enemies->AddEnemy(Enemy_Type::ITEMPICKUP, position.x, position.y, 3);
			break;
		case 45:
			App->enemies->AddEnemy(Enemy_Type::ITEMPICKUP, position.x, position.y, 4);
			break;
		}
		dropped = true;
	}
		
	
	}

}

void Enemy::SetToDelete()
{
	pendingToDelete = true;
	App->player->kills++;
	//if (collider != nullptr)
		//collider->pendingToDelete = true;

	
}