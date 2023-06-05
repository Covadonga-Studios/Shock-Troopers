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
	texture = App->textures->Load("Assets/Sprites/spritesheet2.29.png");

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

	PlayerShotUp.anim.PushBack({ 821, 1734, 7, 13 });
	PlayerShotUp.anim.PushBack({ 834, 1734, 7, 13 });
	PlayerShotUp.speed.x = 5;
	PlayerShotUp.lifetime = 180;
	PlayerShotUp.anim.speed = 0.2f;

	PlayerShotDown.anim.PushBack({ 925, 1734, 7, 13 });
	PlayerShotDown.anim.PushBack({ 938, 1734, 7, 13 });
	PlayerShotDown.speed.x = 5;
	PlayerShotDown.lifetime = 180;
	PlayerShotDown.anim.speed = 0.2f;

	PlayerShotUpRight.anim.PushBack({ 845, 1734, 12, 12 });
	PlayerShotUpRight.anim.PushBack({ 858, 1734, 12, 12 });
	PlayerShotUpRight.speed.x = 5;
	PlayerShotUpRight.lifetime = 180;
	PlayerShotUpRight.anim.speed = 0.2f;

	PlayerShotUpLeft.anim.PushBack({ 845, 1734, 12, 12 }, true);
	PlayerShotUpLeft.anim.PushBack({ 858, 1734, 12, 12 }, true);
	PlayerShotUpLeft.speed.x = 5;
	PlayerShotUpLeft.lifetime = 180;
	PlayerShotUpLeft.anim.speed = 0.2f;


	PlayerShotRight.anim.PushBack({ 870, 1737, 13, 7 });
	PlayerShotRight.anim.PushBack({ 883, 1737, 13, 7 });
	PlayerShotRight.speed.x = 5;
	PlayerShotRight.lifetime = 180;
	PlayerShotRight.anim.speed = 0.2f;

	PlayerShotLeft.anim.PushBack({ 870, 1737, 13, 7 }, true);
	PlayerShotLeft.anim.PushBack({ 883, 1737, 13, 7 }, true);
	PlayerShotLeft.speed.x = 5;
	PlayerShotLeft.lifetime = 180;
	PlayerShotLeft.anim.speed = 0.2f;


	PlayerShotDownRight.anim.PushBack({ 897, 1735, 12, 12 });
	PlayerShotDownRight.anim.PushBack({ 910, 1735, 12, 12 });
	PlayerShotDownRight.speed.x = 5;
	PlayerShotDownRight.lifetime = 180;
	PlayerShotDownRight.anim.speed = 0.2f;

	PlayerShotDownLeft.anim.PushBack({ 897, 1735, 12, 12 }, true);
	PlayerShotDownLeft.anim.PushBack({ 910, 1735, 12, 12 }, true);
	PlayerShotDownLeft.speed.x = 5;
	PlayerShotDownLeft.lifetime = 180;
	PlayerShotDownLeft.anim.speed = 0.2f;

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



	Grenade.anim.PushBack({ 163, 1848, 12, 22 });
	Grenade.anim.PushBack({ 178, 1849, 19, 21 });
	Grenade.anim.PushBack({ 200, 1853, 24, 12 });
	Grenade.anim.PushBack({ 226, 1848, 22, 19 });
	Grenade.anim.PushBack({ 163, 1872, 12, 22 });
	Grenade.anim.PushBack({ 1536, 1873, 19, 21 });
	Grenade.anim.PushBack({ 1560, 1877, 24, 12 });
	Grenade.anim.PushBack({ 1586, 1872, 22, 19 });
	Grenade.lifetime = 40;
	Grenade.anim.speed = 0.3f;
	missile.anim.PushBack({ 146, 0, 13, 13 });

	//MISSILES//MISSILES//MISSILES//MISSILES//MISSILES//MISSILES//MISSILES//MISSILES//MISSILES//MISSILES//MISSILES//MISSILES//MISSILES//MISSILES//MISSILES//MISSILES

	missileLeft.anim.PushBack({ 1098, 1971, 94, 23 });
	missileLeft.anim.PushBack({ 1193, 1971, 94, 23 });
	missileLeft.anim.PushBack({ 1288, 1971, 94, 23 });
	missileLeft.anim.PushBack({ 1383, 1971, 94, 23 });
	missileLeft.anim.PushBack({ 1478, 1971, 94, 23 });
	missileLeft.anim.PushBack({ 1573, 1971, 94, 23 });
	missileLeft.anim.PushBack({ 1668, 1971, 94, 23 });
	missileLeft.anim.PushBack({ 1763, 1971, 94, 23 });
	missileLeft.anim.PushBack({ 1858, 1971, 94, 23 });
	missileLeft.anim.PushBack({ 1953, 1971, 94, 23 });
	missileLeft.lifetime = 180;

	missileRight.anim.PushBack({ 1098, 1971, 94, 23 }, true);
	missileRight.anim.PushBack({ 1193, 1971, 94, 23 }, true);
	missileRight.anim.PushBack({ 1288, 1971, 94, 23 }, true);
	missileRight.anim.PushBack({ 1383, 1971, 94, 23 }, true);
	missileRight.anim.PushBack({ 1478, 1971, 94, 23 }, true);
	missileRight.anim.PushBack({ 1573, 1971, 94, 23 }, true);
	missileRight.anim.PushBack({ 1668, 1971, 94, 23 }, true);
	missileRight.anim.PushBack({ 1763, 1971, 94, 23 }, true);
	missileRight.anim.PushBack({ 1858, 1971, 94, 23 }, true);
	missileRight.anim.PushBack({ 1953, 1971, 94, 23 }, true);
	missileRight.lifetime = 180;
	

	missileDownRight.anim.PushBack({ 1208, 1995, 55, 52 });
	missileDownRight.anim.PushBack({ 1264, 1995, 55, 52 });
	missileDownRight.anim.PushBack({ 1320, 1995, 55, 52 });
	missileDownRight.anim.PushBack({ 1376, 1995, 55, 52 });
	missileDownRight.anim.PushBack({ 1432, 1995, 55, 52 });
	missileDownRight.anim.PushBack({ 1488, 1995, 55, 52 });
	missileDownRight.anim.PushBack({ 1544, 1995, 55, 52 });
	missileDownRight.anim.PushBack({ 1599, 1995, 55, 52 });
	missileDownRight.anim.PushBack({ 1656, 1995, 55, 52 });
	missileDownRight.anim.PushBack({ 1712, 1995, 55, 52 });
	missileDownRight.anim.PushBack({ 1768, 1995, 55, 52 });
	missileDownRight.anim.PushBack({ 1824, 1995, 55, 52 });
	missileDownRight.anim.PushBack({ 1880, 1995, 55, 52 });
	missileDownRight.anim.PushBack({ 1936, 1995, 55, 52 });
	missileDownRight.anim.PushBack({ 1992, 1995, 55, 52 });
	missileDownRight.lifetime = 180;

	missileDownLeft.anim.PushBack({ 1208, 1995, 55, 52 }, true);
	missileDownLeft.anim.PushBack({ 1264, 1995, 55, 52 }, true);
	missileDownLeft.anim.PushBack({ 1320, 1995, 55, 52 }, true);
	missileDownLeft.anim.PushBack({ 1376, 1995, 55, 52 }, true);
	missileDownLeft.anim.PushBack({ 1432, 1995, 55, 52 }, true);
	missileDownLeft.anim.PushBack({ 1488, 1995, 55, 52 }, true);
	missileDownLeft.anim.PushBack({ 1544, 1995, 55, 52 }, true);
	missileDownLeft.anim.PushBack({ 1599, 1995, 55, 52 }, true);
	missileDownLeft.anim.PushBack({ 1656, 1995, 55, 52 }, true);
	missileDownLeft.anim.PushBack({ 1712, 1995, 55, 52 }, true);
	missileDownLeft.anim.PushBack({ 1768, 1995, 55, 52 }, true);
	missileDownLeft.anim.PushBack({ 1824, 1995, 55, 52 }, true);
	missileDownLeft.anim.PushBack({ 1880, 1995, 55, 52 }, true);
	missileDownLeft.anim.PushBack({ 1936, 1995, 55, 52 }, true);
	missileDownLeft.anim.PushBack({ 1992, 1995, 55, 52 }, true);
	missileDownLeft.lifetime = 180;

	missileUp.anim.PushBack({ 1760, 1884, 23, 86 });
	missileUp.anim.PushBack({ 1784, 1884, 23, 86 });
	missileUp.anim.PushBack({ 1808, 1884, 23, 86 });
	missileUp.anim.PushBack({ 1832, 1884, 23, 86 });
	missileUp.anim.PushBack({ 1856, 1884, 23, 86 });
	missileUp.anim.PushBack({ 1880, 1884, 23, 86 });
	missileUp.anim.PushBack({ 1904, 1884, 23, 86 });
	missileUp.anim.PushBack({ 1928, 1884, 23, 86 });
	missileUp.anim.PushBack({ 1952, 1884, 23, 86 });
	missileUp.anim.PushBack({ 1976, 1884, 23, 86 });
	missileUp.anim.PushBack({ 2000, 1884, 23, 86 });
	missileUp.anim.PushBack({ 2024, 1884, 23, 86 });
	missileUp.lifetime = 180;

	missileDown.anim.PushBack({ 1760, 1797, 23, 86 });
	missileDown.anim.PushBack({ 1784, 1797, 23, 86 });
	missileDown.anim.PushBack({ 1808, 1797, 23, 86 });
	missileDown.anim.PushBack({ 1832, 1797, 23, 86 });
	missileDown.anim.PushBack({ 1856, 1797, 23, 86 });
	missileDown.anim.PushBack({ 1880, 1797, 23, 86 });
	missileDown.anim.PushBack({ 1904, 1797, 23, 86 });
	missileDown.anim.PushBack({ 1928, 1797, 23, 86 });
	missileDown.anim.PushBack({ 1952, 1797, 23, 86 });
	missileDown.anim.PushBack({ 1976, 1797, 23, 86 });
	missileDown.anim.PushBack({ 2000, 1797, 23, 86 });
	missileDown.anim.PushBack({ 2024, 1797, 23, 86 });
	missileDown.lifetime = 180;

	missileUpRight.anim.PushBack({ 920, 1918, 55, 52 });
	missileUpRight.anim.PushBack({ 976, 1918, 55, 52 });
	missileUpRight.anim.PushBack({ 1032, 1918, 55, 52 });
	missileUpRight.anim.PushBack({ 1088, 1918, 55, 52 });
	missileUpRight.anim.PushBack({ 1144, 1918, 55, 52 });
	missileUpRight.anim.PushBack({ 1200, 1918, 55, 52 });
	missileUpRight.anim.PushBack({ 1256, 1918, 55, 52 });
	missileUpRight.anim.PushBack({ 1312, 1918, 55, 52 });
	missileUpRight.anim.PushBack({ 1368, 1918, 55, 52 });
	missileUpRight.anim.PushBack({ 1424, 1918, 55, 52 });
	missileUpRight.anim.PushBack({ 1480, 1918, 55, 52 });
	missileUpRight.anim.PushBack({ 1536, 1918, 55, 52 });
	missileUpRight.anim.PushBack({ 1592, 1918, 55, 52 });
	missileUpRight.anim.PushBack({ 1648, 1918, 55, 52 });
	missileUpRight.anim.PushBack({ 1704, 1918, 55, 52 });
	missileUpRight.lifetime = 180;

	missileUpLeft.anim.PushBack({ 920, 1918, 55, 52 }, true);
	missileUpLeft.anim.PushBack({ 976, 1918, 55, 52 }, true);
	missileUpLeft.anim.PushBack({ 1032, 1918, 55, 52 }, true);
	missileUpLeft.anim.PushBack({ 1088, 1918, 55, 52 }, true);
	missileUpLeft.anim.PushBack({ 1144, 1918, 55, 52 }, true);
	missileUpLeft.anim.PushBack({ 1200, 1918, 55, 52 }, true);
	missileUpLeft.anim.PushBack({ 1256, 1918, 55, 52 }, true);
	missileUpLeft.anim.PushBack({ 1312, 1918, 55, 52 }, true);
	missileUpLeft.anim.PushBack({ 1368, 1918, 55, 52 }, true);
	missileUpLeft.anim.PushBack({ 1424, 1918, 55, 52 }, true);
	missileUpLeft.anim.PushBack({ 1480, 1918, 55, 52 }, true);
	missileUpLeft.anim.PushBack({ 1536, 1918, 55, 52 }, true);
	missileUpLeft.anim.PushBack({ 1592, 1918, 55, 52 }, true);
	missileUpLeft.anim.PushBack({ 1648, 1918, 55, 52 }, true);
	missileUpLeft.anim.PushBack({ 1704, 1918, 55, 52 }, true);
	missileUpLeft.lifetime = 180;

	blueBullet.anim.PushBack({ 529, 57, 13, 64 });
	blueBullet.anim.PushBack({ 543, 57, 13, 64 });
	blueBullet.anim.PushBack({ 557, 57, 13, 64 });
	blueBullet.anim.PushBack({ 571, 57, 13, 64 });
	blueBullet.anim.speed = 0.1f;

	bulletHit.anim.PushBack({ 172, 925, 16, 32 });
	bulletHit.anim.PushBack({ 189, 925, 16, 32 });
	bulletHit.anim.PushBack({ 206, 925, 16, 32 });
	bulletHit.anim.PushBack({ 223, 925, 16, 32 });
	bulletHit.anim.PushBack({ 240, 925, 16, 32 });
	bulletHit.anim.PushBack({ 257, 925, 16, 32 });
	bulletHit.anim.PushBack({ 274, 925, 16, 32 });
	bulletHit.anim.PushBack({ 291, 925, 16, 32 });

	finalBulletDown.anim.PushBack({ 506, 1901, 48, 48 });
	finalBulletDown.anim.PushBack({ 555, 1901, 48, 48 });
	finalBulletDown.anim.PushBack({ 604, 1901, 48, 48 });
	finalBulletDown.anim.PushBack({ 653, 1901, 48, 48 });
	finalBulletDown.anim.PushBack({ 702, 1901, 48, 48 });
	finalBulletDown.anim.PushBack({ 751, 1901, 48, 48 });
	finalBulletDown.anim.speed = 0.1f;

	finalBulletDownLeft.anim.PushBack({ 506, 1950, 48, 48 });
	finalBulletDownLeft.anim.PushBack({ 555, 1950, 48, 48 });
	finalBulletDownLeft.anim.PushBack({ 604, 1950, 48, 48 });
	finalBulletDownLeft.anim.PushBack({ 653, 1950, 48, 48 });
	finalBulletDownLeft.anim.PushBack({ 702, 1950, 48, 48 });
	finalBulletDownLeft.anim.PushBack({ 751, 1950, 48, 48 });
	finalBulletDownLeft.anim.speed = 0.1f;

	finalBulletDownRight.anim.PushBack({ 506, 1950, 48, 48 }, true);
	finalBulletDownRight.anim.PushBack({ 555, 1950, 48, 48 }, true);
	finalBulletDownRight.anim.PushBack({ 604, 1950, 48, 48 }, true);
	finalBulletDownRight.anim.PushBack({ 653, 1950, 48, 48 }, true);
	finalBulletDownRight.anim.PushBack({ 702, 1950, 48, 48 }, true);
	finalBulletDownRight.anim.PushBack({ 751, 1950, 48, 48 }, true);
	finalBulletDownRight.anim.speed = 0.1f;

	finalBulletLeft.anim.PushBack({ 506, 1999, 48, 48 });
	finalBulletLeft.anim.PushBack({ 555, 1999, 48, 48 });
	finalBulletLeft.anim.PushBack({ 604, 1999, 48, 48 });
	finalBulletLeft.anim.PushBack({ 653, 1999, 48, 48 });
	finalBulletLeft.anim.PushBack({ 702, 1999, 48, 48 });
	finalBulletLeft.anim.PushBack({ 751, 1999, 48, 48 });
	finalBulletLeft.anim.speed = 0.1f;

	finalBulletRight.anim.PushBack({ 506, 1999, 48, 48 }, true);
	finalBulletRight.anim.PushBack({ 555, 1999, 48, 48 }, true);
	finalBulletRight.anim.PushBack({ 604, 1999, 48, 48 }, true);
	finalBulletRight.anim.PushBack({ 653, 1999, 48, 48 }, true);
	finalBulletRight.anim.PushBack({ 702, 1999, 48, 48 }, true);
	finalBulletRight.anim.PushBack({ 751, 1999, 48, 48 }, true);
	finalBulletRight.anim.speed = 0.1f;

	finalMissileDownRight.anim.PushBack({ 800, 2019, 50, 28 });
	finalMissileDownRight.anim.PushBack({ 851, 2019, 50, 28 });
	finalMissileDownRight.anim.PushBack({ 902, 2019, 50, 28 });
	finalMissileDownRight.anim.PushBack({ 953, 2019, 50, 28 });
	finalMissileDownRight.anim.PushBack({ 1004, 2019, 50, 28 });
	finalMissileDownRight.anim.PushBack({ 1055, 2019, 50, 28 });
	finalMissileDownRight.anim.PushBack({ 1106, 2019, 50, 28 });
	finalMissileDownRight.anim.PushBack({ 1157, 2019, 50, 28 });

	finalMissileDownLeft.anim.PushBack({ 800, 2019, 50, 28 }, true);
	finalMissileDownLeft.anim.PushBack({ 851, 2019, 50, 28 }, true);
	finalMissileDownLeft.anim.PushBack({ 902, 2019, 50, 28 }, true);
	finalMissileDownLeft.anim.PushBack({ 953, 2019, 50, 28 }, true);
	finalMissileDownLeft.anim.PushBack({ 1004, 2019, 50, 28 }, true);
	finalMissileDownLeft.anim.PushBack({ 1055, 2019, 50, 28 }, true);
	finalMissileDownLeft.anim.PushBack({ 1106, 2019, 50, 28 }, true);
	finalMissileDownLeft.anim.PushBack({ 1157, 2019, 50, 28 }, true);

	missileExplosion.anim.PushBack({ 301, 1250, 30, 28 });
	missileExplosion.anim.PushBack({ 332, 1250, 30, 28 });
	missileExplosion.anim.PushBack({ 363, 1250, 30, 28 });
	missileExplosion.anim.PushBack({ 394, 1250, 30, 28 });
	missileExplosion.anim.PushBack({ 425, 1250, 30, 28 });
	missileExplosion.anim.PushBack({ 456, 1250, 30, 28 });
	missileExplosion.anim.PushBack({ 487, 1250, 30, 28 });
	missileExplosion.anim.PushBack({ 518, 1250, 30, 28 });
	missileExplosion.anim.PushBack({ 549, 1250, 30, 28 });
	missileExplosion.anim.speed = 0.3f;
	missileExplosion.lifetime = 60;

	dust.anim.PushBack({ 383, 1040, 52, 52 });
	dust.anim.PushBack({ 436, 1040, 52, 52 });
	dust.anim.PushBack({ 489, 1040, 52, 52 });
	dust.anim.PushBack({ 542, 1040, 52, 52 });
	dust.anim.PushBack({ 595, 1040, 52, 52 });
	dust.anim.PushBack({ 648, 1040, 52, 52 });
	dust.anim.PushBack({ 701, 1040, 52, 52 });
	dust.anim.PushBack({ 754, 1040, 52, 52 });
	dust.anim.speed = 0.4f;
	dust.lifetime = 30;

	tankBullet.anim.PushBack({ 28, 925, 35, 32 });
	tankBullet.anim.PushBack({ 63, 925, 35, 32 });
	tankBullet.anim.PushBack({ 98, 925, 35, 32 });
	tankBullet.anim.PushBack({ 133, 925, 35, 32 });

	explosionDefault.anim.PushBack({ 1, 1093, 58, 62 });
	explosionDefault.anim.PushBack({ 60, 1093, 58, 62 });
	explosionDefault.anim.PushBack({ 119, 1093, 58, 62 });
	explosionDefault.anim.PushBack({ 178, 1093, 58, 62 });
	explosionDefault.anim.PushBack({ 237, 1093, 58, 62 });
	explosionDefault.anim.PushBack({ 296, 1093, 58, 62 });
	explosionDefault.anim.PushBack({ 355, 1093, 58, 62 });
	explosionDefault.anim.PushBack({ 414, 1093, 58, 62 });
	explosionDefault.anim.PushBack({ 473, 1093, 58, 62 });
	explosionDefault.anim.PushBack({ 532, 1093, 58, 62 });
	explosionDefault.anim.PushBack({ 591, 1093, 58, 62 });
	explosionDefault.anim.PushBack({ 650, 1093, 58, 62 });
	explosionDefault.anim.PushBack({ 709, 1093, 58, 62 });
	explosionDefault.anim.PushBack({ 768, 1093, 58, 62 });
	explosionDefault.anim.PushBack({ 827, 1093, 58, 62 });
	explosionDefault.anim.PushBack({ 886, 1093, 58, 62 });
	explosionDefault.anim.PushBack({ 945, 1093, 58, 62 });
	explosionDefault.anim.PushBack({ 1004, 1093, 58, 62 });
	explosionDefault.anim.PushBack({ 1063, 1093, 58, 62 });
	explosionDefault.anim.speed = 0.4f;
	explosionDefault.lifetime = 40;

	flameThrower.anim.PushBack({ 382, 1934, 30, 37 });
	flameThrower.anim.PushBack({ 413, 1934, 30, 37 });
	flameThrower.anim.PushBack({ 444, 1934, 30, 37 });
	flameThrower.anim.PushBack({ 475, 1934, 30, 37 });
	flameThrower.anim.PushBack({ 382, 1972, 30, 37 });
	flameThrower.anim.PushBack({ 413, 1972, 30, 37 });
	flameThrower.anim.PushBack({ 444, 1972, 30, 37 });
	flameThrower.anim.PushBack({ 475, 1972, 30, 37 });
	flameThrower.anim.PushBack({ 382, 2010, 30, 37 });
	flameThrower.anim.PushBack({ 413, 2010, 30, 37 });
	flameThrower.anim.PushBack({ 444, 2010, 30, 37 });
	flameThrower.anim.PushBack({ 475, 2010, 30, 37 });
	flameThrower.anim.speed = 0.35f;
	flameThrower.lifetime = 30;

	powerUpThreeBullets.anim.PushBack({ 542, 8, 13, 13 });
	powerUpThreeBullets.anim.PushBack({ 556, 8, 13, 13 });
	powerUpThreeBullets.anim.PushBack({ 542, 22, 13, 13 });
	powerUpThreeBullets.anim.PushBack({ 556, 22, 13, 13 });
	powerUpThreeBullets.anim.PushBack({ 542, 36, 13, 13 });
	powerUpThreeBullets.anim.PushBack({ 556, 36, 13, 13 });
	powerUpThreeBullets.anim.speed = 0.2f;
	powerUpThreeBullets.lifetime = 80;


	enemybulletdown.anim.PushBack({ 1955, 1, 32, 35 });
	enemybulletdown.anim.PushBack({ 1955, 37, 32, 35 });
	enemybulletdown.anim.PushBack({ 1955, 73, 32, 35 });
	enemybulletdown.anim.PushBack({ 1955, 109, 32, 35 });
	enemybulletdown.anim.speed = 0.1f;

	enemybulletrightdown.anim.PushBack({ 2016, 1, 27, 17 });
	enemybulletrightdown.anim.PushBack({ 2016, 19, 27, 17 });
	enemybulletrightdown.anim.PushBack({ 2016, 37, 27, 17 });
	enemybulletrightdown.anim.PushBack({ 2016, 55, 27, 17 });
	enemybulletrightdown.anim.speed = 0.1f;

	enemybulletleft.anim.PushBack({ 28, 925, 35, 32 });
	enemybulletleft.anim.PushBack({ 64, 925, 35, 32 });
	enemybulletleft.anim.PushBack({ 100, 925, 35, 32 });
	enemybulletleft.anim.PushBack({ 136, 925, 35, 32 });
	enemybulletleft.anim.speed = 0.1f;

	enemybulletupleft.anim.PushBack({ 1988, 1, 27, 17 });
	enemybulletupleft.anim.PushBack({ 1988, 19, 27, 17 });
	enemybulletupleft.anim.PushBack({ 1988, 37, 27, 17 });
	enemybulletupleft.anim.PushBack({ 1988, 55, 27, 17 });
	enemybulletupleft.anim.speed = 0.1f;

	enemybulletup.anim.PushBack({ 1922, 1, 32, 35 });
	enemybulletup.anim.PushBack({ 1922, 37, 32, 35 });
	enemybulletup.anim.PushBack({ 1922, 73, 32, 35 });
	enemybulletup.anim.PushBack({ 1922, 109, 32, 35 });
	enemybulletup.anim.speed = 0.1f;

	enemybulletrightup.anim.PushBack({ 1988, 1, 27, 17 }, true);
	enemybulletrightup.anim.PushBack({ 1988, 19, 27, 17 }, true);
	enemybulletrightup.anim.PushBack({ 1988, 37, 27, 17 }, true);
	enemybulletrightup.anim.PushBack({ 1988, 55, 27, 17 }, true);
	enemybulletrightup.anim.speed = 0.1f;

	enemybulletright.anim.PushBack({ 28, 925, 35, 32 }, true);
	enemybulletright.anim.PushBack({ 64, 925, 35, 32 }, true);
	enemybulletright.anim.PushBack({ 100, 925, 35, 32 }, true);
	enemybulletright.anim.PushBack({ 136, 925, 35, 32 }, true);
	enemybulletright.anim.speed = 0.1f;

	enemybulletdownleft.anim.PushBack({ 2016, 1, 27, 17 }, true);
	enemybulletdownleft.anim.PushBack({ 2016, 19, 27, 17 }, true);
	enemybulletdownleft.anim.PushBack({ 2016, 37, 27, 17 }, true);
	enemybulletdownleft.anim.PushBack({ 2016, 55, 27, 17 }, true);
	enemybulletdownleft.anim.speed = 0.1f;

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