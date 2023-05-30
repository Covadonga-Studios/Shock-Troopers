#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	texture = App->textures->Load("Assets/Sprites/spritesheet2.26.png");

	// Explosion particle
	explosion.anim.PushBack({274, 296, 33, 30});
	explosion.anim.PushBack({313, 296, 33, 30});
	explosion.anim.PushBack({346, 296, 33, 30});
	explosion.anim.PushBack({382, 296, 33, 30});
	explosion.anim.PushBack({419, 296, 33, 30});
	explosion.anim.PushBack({457, 296, 33, 30});
	explosion.anim.loop = false;
	explosion.anim.speed = 0.3f;

	laser.anim.PushBack({ 331,719,7,7});
	laser.anim.PushBack({ 340,719,7,7 });
	laser.anim.PushBack({ 349,719,7,7 });
	laser.lifetime = 180;
	laser.anim.speed = 0.2f;

	PlayerShotUp.anim.PushBack({ 120, 0, 13, 13 });
	PlayerShotUp.anim.PushBack({ 133, 0, 13, 13 });
	PlayerShotUp.speed.x = 5;
	PlayerShotUp.lifetime = 180;
	PlayerShotUp.anim.speed = 0.2f;


	PlayerShotUpRight.anim.PushBack({ 146, 0, 13, 13 });
	PlayerShotUpRight.anim.PushBack({ 159, 0, 13, 13 });
	PlayerShotUpRight.speed.x = 5;
	PlayerShotUpRight.lifetime = 180;
	PlayerShotUpRight.anim.speed = 0.2f;


	PlayerShotRight.anim.PushBack({ 172, 0, 13, 13 });
	PlayerShotRight.anim.PushBack({ 185, 0, 13, 13 });
	PlayerShotRight.speed.x = 5;
	PlayerShotRight.lifetime = 180;
	PlayerShotRight.anim.speed = 0.2f;


	PlayerShotDownRight.anim.PushBack({ 198, 0, 13, 13 });
	PlayerShotDownRight.anim.PushBack({ 211, 0, 13, 13 });
	PlayerShotDownRight.speed.x = 5;
	PlayerShotDownRight.lifetime = 180;
	PlayerShotDownRight.anim.speed = 0.2f;


	PlayerShotDown.anim.PushBack({ 224, 0, 13, 13 });
	PlayerShotDown.anim.PushBack({ 237, 0, 13, 13 });
	PlayerShotDown.speed.x = 5;
	PlayerShotDown.lifetime = 180;
	PlayerShotDown.anim.speed = 0.2f;


	PlayerShotDownLeft.anim.PushBack({ 198, 0, 13, 13 }, true);
	PlayerShotDownLeft.anim.PushBack({ 211, 0, 13, 13 }, true);
	PlayerShotDownLeft.speed.x = 5;
	PlayerShotDownLeft.lifetime = 180;
	PlayerShotDownLeft.anim.speed = 0.2f;


	PlayerShotLeft.anim.PushBack({ 172, 0, 13, 13 }, true);
	PlayerShotLeft.anim.PushBack({ 185, 0, 13, 13 }, true);
	PlayerShotLeft.speed.x = 5;
	PlayerShotLeft.lifetime = 180;
	PlayerShotLeft.anim.speed = 0.2f;

	PlayerShotUpLeft.anim.PushBack({ 146, 0, 13, 13 }, true);
	PlayerShotUpLeft.anim.PushBack({ 159, 0, 13, 13 }, true);
	PlayerShotUpLeft.speed.x = 5;
	PlayerShotUpLeft.lifetime = 180;
	PlayerShotUpLeft.anim.speed = 0.2f;

	grenade.anim.PushBack({398, 580, 53,110 });
	grenade.anim.PushBack({ 451, 580, 53,110 });
	grenade.anim.PushBack({ 504, 580, 53,110 });
	grenade.anim.PushBack({ 557, 580, 53,110 });
	grenade.anim.PushBack({ 610, 580, 53,110 });
	grenade.anim.PushBack({ 663, 580, 53,110 });
	grenade.anim.PushBack({ 716, 580, 53,110 });
	grenade.anim.PushBack({ 398, 689, 53,110 });
	grenade.anim.PushBack({ 451, 689, 53,110 });
	grenade.anim.PushBack({ 504, 689, 53,110 });
	grenade.anim.PushBack({ 557, 689, 53,110 });
	grenade.anim.PushBack({ 610, 689, 53,110 });
	grenade.anim.PushBack({ 663, 689, 53,110 });
	grenade.anim.PushBack({ 716, 689, 53,110 });
	grenade.anim.PushBack({ 398, 798, 53,110 });
	grenade.anim.PushBack({ 451, 798, 53,110 });
	grenade.anim.PushBack({ 504, 798, 53,110 });
	grenade.anim.PushBack({ 557, 798, 53,110 });
	grenade.anim.PushBack({ 610, 798, 53,110 });
	grenade.anim.PushBack({ 663, 798, 53,110 });
	grenade.anim.PushBack({ 716, 798, 53,110 });
	grenade.anim.PushBack({ 398, 907, 53,110 });
	grenade.anim.PushBack({ 451, 907, 53,110 });
	grenade.anim.PushBack({ 504, 907, 53,110 });
	grenade.anim.PushBack({ 557, 907, 53,110 });
	grenade.anim.PushBack({ 610, 907, 53,110 });
	grenade.anim.PushBack({ 663, 907, 53,110 });
	grenade.anim.PushBack({ 716, 907, 53,110 });
	grenade.immortal = true;
	grenade.lifetime = 90;
	grenade.anim.speed = 0.3f;


	Grenade.anim.PushBack({ 1523, 551, 13, 23 });
	Grenade.anim.PushBack({ 1536, 551, 21, 23 });
	Grenade.anim.PushBack({ 1560, 551, 26, 23 });
	Grenade.anim.PushBack({ 1586, 551, 25, 23 });
	Grenade.anim.PushBack({ 1523, 575, 13, 23 });
	Grenade.anim.PushBack({ 1536, 575, 21, 23 });
	Grenade.anim.PushBack({ 1560, 575, 26, 23 });
	Grenade.anim.PushBack({ 1586, 575, 25, 23 });
	Grenade.lifetime = 20;
	Grenade.anim.speed = 0.3f;
	missile.anim.PushBack({ 146, 0, 13, 13 });

	//MISSILES//MISSILES//MISSILES//MISSILES//MISSILES//MISSILES//MISSILES//MISSILES//MISSILES//MISSILES//MISSILES//MISSILES//MISSILES//MISSILES//MISSILES//MISSILES

	missileLeft.anim.PushBack({ 1043, 1969, 94, 23 });
	missileLeft.anim.PushBack({ 1138, 1969, 94, 23 });
	missileLeft.anim.PushBack({ 1233, 1969, 94, 23 });
	missileLeft.anim.PushBack({ 1328, 1969, 94, 23 });
	missileLeft.anim.PushBack({ 1423, 1969, 94, 23 });
	missileLeft.anim.PushBack({ 1518, 1969, 94, 23 });
	missileLeft.anim.PushBack({ 1613, 1969, 94, 23 });
	missileLeft.anim.PushBack({ 1708, 1969, 94, 23 });
	missileLeft.anim.PushBack({ 1803, 1969, 94, 23 });
	missileLeft.anim.PushBack({ 1898, 1969, 94, 23 });
	missileLeft.lifetime = 180;

	missileRight.anim.PushBack({ 1043, 1969, 94, 23 }, true);
	missileRight.anim.PushBack({ 1138, 1969, 94, 23 }, true);
	missileRight.anim.PushBack({ 1233, 1969, 94, 23 }, true);
	missileRight.anim.PushBack({ 1328, 1969, 94, 23 }, true);
	missileRight.anim.PushBack({ 1423, 1969, 94, 23 }, true);
	missileRight.anim.PushBack({ 1518, 1969, 94, 23 }, true);
	missileRight.anim.PushBack({ 1613, 1969, 94, 23 }, true);
	missileRight.anim.PushBack({ 1708, 1969, 94, 23 }, true);
	missileRight.anim.PushBack({ 1803, 1969, 94, 23 }, true);
	missileRight.anim.PushBack({ 1898, 1969, 94, 23 }, true);
	missileRight.lifetime = 180;
	

	missileDownRight.anim.PushBack({ 1151 + 2, 1995, 55, 52 });
	missileDownRight.anim.PushBack({ 1207 + 2, 1995, 55, 52 });
	missileDownRight.anim.PushBack({ 1263 + 2, 1995, 55, 52 });
	missileDownRight.anim.PushBack({ 1319 + 2, 1995, 55, 52 });
	missileDownRight.anim.PushBack({ 1375 + 2, 1995, 55, 52 });
	missileDownRight.anim.PushBack({ 1431 + 2, 1995, 55, 52 });
	missileDownRight.anim.PushBack({ 1487 + 2, 1995, 55, 52 });
	missileDownRight.anim.PushBack({ 1543 + 2, 1995, 55, 52 });
	missileDownRight.anim.PushBack({ 1599 + 2, 1995, 55, 52 });
	missileDownRight.anim.PushBack({ 1655 + 2, 1995, 55, 52 });
	missileDownRight.anim.PushBack({ 1711 + 2, 1995, 55, 52 });
	missileDownRight.anim.PushBack({ 1767 + 2, 1995, 55, 52 });
	missileDownRight.anim.PushBack({ 1823 + 2, 1995, 55, 52 });
	missileDownRight.anim.PushBack({ 1879 + 2, 1995, 55, 52 });
	missileDownRight.anim.PushBack({ 1935 + 2, 1995, 55, 52 });
	missileDownRight.lifetime = 180;

	missileUp.anim.PushBack({ 1692, 1866, 23, 86 });
	missileUp.anim.PushBack({ 1716, 1866, 23, 86 });
	missileUp.anim.PushBack({ 1740, 1866, 23, 86 });
	missileUp.anim.PushBack({ 1764, 1866, 23, 86 });
	missileUp.anim.PushBack({ 1788, 1866, 23, 86 });
	missileUp.anim.PushBack({ 1812, 1866, 23, 86 });
	missileUp.anim.PushBack({ 1836, 1866, 23, 86 });
	missileUp.anim.PushBack({ 1860, 1866, 23, 86 });
	missileUp.anim.PushBack({ 1884, 1866, 23, 86 });
	missileUp.anim.PushBack({ 1908, 1866, 23, 86 });
	missileUp.anim.PushBack({ 1932, 1866, 23, 86 });
	missileUp.anim.PushBack({ 1956, 1866, 23, 86 });
	missileUp.lifetime = 180;

	missileDown.anim.PushBack({ 1692, 1779, 23, 86 });
	missileDown.anim.PushBack({ 1716, 1779, 23, 86 });
	missileDown.anim.PushBack({ 1740, 1779, 23, 86 });
	missileDown.anim.PushBack({ 1764, 1779, 23, 86 });
	missileDown.anim.PushBack({ 1788, 1779, 23, 86 });
	missileDown.anim.PushBack({ 1812, 1779, 23, 86 });
	missileDown.anim.PushBack({ 1836, 1779, 23, 86 });
	missileDown.anim.PushBack({ 1860, 1779, 23, 86 });
	missileDown.anim.PushBack({ 1884, 1779, 23, 86 });
	missileDown.anim.PushBack({ 1908, 1779, 23, 86 });
	missileDown.anim.PushBack({ 1932, 1779, 23, 86 });
	missileDown.anim.PushBack({ 1956, 1779, 23, 86 });
	missileDown.lifetime = 180;
	

	missileDownLeft.anim.PushBack({ 1151 + 2, 1995, 55, 52 },true);
	missileDownLeft.anim.PushBack({ 1207 + 2, 1995, 55, 52 },true);
	missileDownLeft.anim.PushBack({ 1263 + 2, 1995, 55, 52 },true);
	missileDownLeft.anim.PushBack({ 1319 + 2, 1995, 55, 52 },true);
	missileDownLeft.anim.PushBack({ 1375 + 2, 1995, 55, 52 },true);
	missileDownLeft.anim.PushBack({ 1431 + 2, 1995, 55, 52 },true);
	missileDownLeft.anim.PushBack({ 1487 + 2, 1995, 55, 52 },true);
	missileDownLeft.anim.PushBack({ 1543 + 2, 1995, 55, 52 },true);
	missileDownLeft.anim.PushBack({ 1599 + 2, 1995, 55, 52 },true);
	missileDownLeft.anim.PushBack({ 1655 + 2, 1995, 55, 52 },true);
	missileDownLeft.anim.PushBack({ 1711 + 2, 1995, 55, 52 },true);
	missileDownLeft.anim.PushBack({ 1767 + 2, 1995, 55, 52 },true);
	missileDownLeft.anim.PushBack({ 1823 + 2, 1995, 55, 52 },true);
	missileDownLeft.anim.PushBack({ 1879 + 2, 1995, 55, 52 },true);
	missileDownLeft.anim.PushBack({ 1935 + 2, 1995, 55, 52 },true);
	missileDownLeft.lifetime = 180;

	blueBullet.anim.PushBack({ 311, 739, 13, 64 });
	blueBullet.anim.PushBack({ 325, 739, 13, 64 });
	blueBullet.anim.PushBack({ 339, 739, 13, 64 });
	blueBullet.anim.PushBack({ 353, 739, 13, 64 });
	blueBullet.anim.speed = 0.1f;

	return true;
}

Update_Status ModuleParticles::PreUpdate()
{
	// Remove all particles scheduled for deletion
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (particles[i] != nullptr && particles[i]->pendingToDelete)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->collider == c1 && particles[i]->immortal == false)
		{
				particles[i]->pendingToDelete = true;
				particles[i]->collider->pendingToDelete = true;
				break;		
		}
	}
}

Update_Status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if(particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if(particle->Update() == false)
		{
			particles[i]->SetToDelete();
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleParticles::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			
			
			
			if (particle->anim.GetMirror() == 1)
			{
				App->render->BlitMirror(texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));

			}
			else
			{
				App->render->Blit(texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));

			}
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Particle* ModuleParticles::AddParticle(const Particle& particle, int x, int y, float speedx, float speedy,bool immortal, Collider::Type colliderType,
		 uint delay, bool isColl, int w , int h, int offsetx, int offsety)
{
	Particle* newParticle = nullptr;

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			newParticle = new Particle(particle);
			newParticle->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			newParticle->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			newParticle->position.y = y;
			newParticle->speed.x = speedx;
			newParticle->speed.y = speedy;
			newParticle->immortal = immortal;
			//Adding the particle's collider
			if (colliderType != Collider::Type::NONE && isColl == false)
				newParticle->collider = App->collisions->AddCollider(newParticle->anim.GetCurrentFrame(), colliderType, this);
			
			if (isColl == true) 
			{
				newParticle->collider = App->collisions->AddCollider({x + offsetx,y + offsety,w,h}, colliderType, this);
			}
			
			newParticle->offsetxcoll = offsetx;
			newParticle->offsetycoll = offsety;
			particles[i] = newParticle;
			break;
		}
	}

	return newParticle;
}