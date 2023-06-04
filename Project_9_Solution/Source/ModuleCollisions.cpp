#include "ModuleCollisions.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleInput.h"
#include "SDL/include/SDL_Scancode.h"

ModuleCollisions::ModuleCollisions(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[Collider::Type::WALL][Collider::Type::WALL] = false;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY_SHOT] = true;

	matrix[Collider::Type::PLAYER][Collider::Type::WALL] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::FLAME] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ITEM] = true;

	matrix[Collider::Type::UP_PLAYER][Collider::Type::WALL] = true;
	matrix[Collider::Type::UP_PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::UP_PLAYER][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::UP_PLAYER][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::UP_PLAYER][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::UP_PLAYER][Collider::Type::FLAME] = false;
	matrix[Collider::Type::UP_PLAYER][Collider::Type::MISSILE] = false;

	matrix[Collider::Type::LEFT_PLAYER][Collider::Type::WALL] = true;
	matrix[Collider::Type::LEFT_PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::LEFT_PLAYER][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::LEFT_PLAYER][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::LEFT_PLAYER][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::LEFT_PLAYER][Collider::Type::FLAME] = false;
	matrix[Collider::Type::LEFT_PLAYER][Collider::Type::MISSILE] = false;

	matrix[Collider::Type::RIGHT_PLAYER][Collider::Type::WALL] = true;
	matrix[Collider::Type::RIGHT_PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::RIGHT_PLAYER][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::RIGHT_PLAYER][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::RIGHT_PLAYER][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::RIGHT_PLAYER][Collider::Type::FLAME] = false;
	matrix[Collider::Type::RIGHT_PLAYER][Collider::Type::MISSILE] = false;

	matrix[Collider::Type::DOWN_PLAYER][Collider::Type::WALL] = true;
	matrix[Collider::Type::DOWN_PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::DOWN_PLAYER][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::DOWN_PLAYER][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::DOWN_PLAYER][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::DOWN_PLAYER][Collider::Type::FLAME] = false;
	matrix[Collider::Type::DOWN_PLAYER][Collider::Type::MISSILE] = false;


	matrix[Collider::Type::ENEMY][Collider::Type::WALL] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::MISSILE] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::GRENADE] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::FLAME] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ITEM] = false;


	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::WALL] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ITEM] = false;

	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::WALL] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::MISSILE] = false;

	matrix[Collider::Type::MISSILE][Collider::Type::WALL] = false;
	matrix[Collider::Type::MISSILE][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::MISSILE][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::MISSILE][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::MISSILE][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::MISSILE][Collider::Type::ITEM] = false;

	matrix[Collider::Type::GRENADE][Collider::Type::WALL] = false;
	matrix[Collider::Type::GRENADE][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::GRENADE][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::GRENADE][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::GRENADE][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::GRENADE][Collider::Type::ITEM] = false;

	matrix[Collider::Type::FLAME][Collider::Type::WALL] = false;
	matrix[Collider::Type::FLAME][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::FLAME][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::FLAME][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::FLAME][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::FLAME][Collider::Type::UP_PLAYER] = false;
	matrix[Collider::Type::FLAME][Collider::Type::RIGHT_PLAYER] = false;
	matrix[Collider::Type::FLAME][Collider::Type::DOWN_PLAYER] = false;
	matrix[Collider::Type::FLAME][Collider::Type::LEFT_PLAYER] = false;
	matrix[Collider::Type::FLAME][Collider::Type::ITEM] = false;

	matrix[Collider::Type::ITEM][Collider::Type::WALL] = false;
	matrix[Collider::Type::ITEM][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ITEM][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ITEM][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::ITEM][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::ITEM][Collider::Type::UP_PLAYER] = false;
	matrix[Collider::Type::ITEM][Collider::Type::RIGHT_PLAYER] = false;
	matrix[Collider::Type::ITEM][Collider::Type::DOWN_PLAYER] = false;
	matrix[Collider::Type::ITEM][Collider::Type::LEFT_PLAYER] = false;
}

// Destructor
ModuleCollisions::~ModuleCollisions()
{

}

Update_Status ModuleCollisions::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for(uint i = 0; i < MAX_COLLIDERS ; ++i)
	{
		if(colliders[i] != nullptr && colliders[i]->pendingToDelete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	Collider* c1;
	Collider* c2;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if(colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for(uint k = i+1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if(colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if(matrix[c1->type][c2->type] && c1->Intersects(c2->rect))
			{
				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c1->listeners[i] != nullptr) c1->listeners[i]->OnCollision(c1, c2);
				
				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c2->listeners[i] != nullptr) c2->listeners[i]->OnCollision(c2, c1);
			}
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleCollisions::Update()
{
	if (App->input->keys[SDL_SCANCODE_F1] == KEY_DOWN)
		debug = !debug;

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleCollisions::PostUpdate()
{
	if (debug)
		DebugDraw();

	return Update_Status::UPDATE_CONTINUE;
}

void ModuleCollisions::DebugDraw()
{
	Uint8 alpha = 80;
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
			continue;
		
		switch(colliders[i]->type)
		{
			case Collider::Type::WALL: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
			case Collider::Type::PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
			case Collider::Type::ENEMY: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
			case Collider::Type::PLAYER_SHOT: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
			case Collider::Type::ENEMY_SHOT: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
			case Collider::Type::UP_PLAYER: // yellow
				App->render->DrawQuad(colliders[i]->rect, 100, 20, 0, alpha);
				break;
			case Collider::Type::DOWN_PLAYER: // yellow
				App->render->DrawQuad(colliders[i]->rect, 50, 100, 0, alpha);
				break;
			case Collider::Type::LEFT_PLAYER: // yellow
				App->render->DrawQuad(colliders[i]->rect, 30, 120, 0, alpha);
				break;
			case Collider::Type::RIGHT_PLAYER: // yellow
				App->render->DrawQuad(colliders[i]->rect, 90, 80, 0, alpha);
				break;
			case Collider::Type::MISSILE: // yellow
				App->render->DrawQuad(colliders[i]->rect, 255, 80, 0, alpha);
				break;
			case Collider::Type::FLAME: // yellow
				App->render->DrawQuad(colliders[i]->rect, 0, 80, 0, alpha);
				break;
			case Collider::Type::GRENADE: // yellow
				App->render->DrawQuad(colliders[i]->rect, 0, 80, 255, alpha);
				break;
			case Collider::Type::ITEM: // yellow
				App->render->DrawQuad(colliders[i]->rect, 255, 80, 255, alpha);
				break;
		}
	}
}

// Called before quitting
bool ModuleCollisions::CleanUp()
{
	LOG("Freeing all colliders");

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}


Collider* ModuleCollisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener)
{
	Collider* ret = nullptr;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, listener);
			break;
		}
	}

	return ret;
}

void ModuleCollisions::RemoveCollider(Collider* collider)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == collider)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}
}