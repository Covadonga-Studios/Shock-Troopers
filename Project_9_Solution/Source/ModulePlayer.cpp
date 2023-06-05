#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModuleUI.h"
#include "SDL/include/SDL_scancode.h"
#include <stdio.h>



ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	// idle animation - just one sprite
	downAnimLeg.PushBack({ 18,330,33,31 });
	downAnimLeg.PushBack({ 51,330,33,31 });
	downAnimLeg.PushBack({ 84,330,33,31 });
	downAnimLeg.PushBack({ 117,330,33,31 });
	downAnimLeg.PushBack({ 150,330,33,31 });
	downAnimLeg.PushBack({ 183,330,33,31 });
	downAnimLeg.PushBack({ 216,330,33,31 });
	downAnimLeg.PushBack({ 249,330,33,31 });
	downAnimLeg.speed = 0.15f;

	upAnimLeg.PushBack({ 18,454,33,31 });
	upAnimLeg.PushBack({ 51,454,33,31 });
	upAnimLeg.PushBack({ 84,454,33,31 });
	upAnimLeg.PushBack({ 117,454,33,31 });
	upAnimLeg.PushBack({ 150,454,33,31 });
	upAnimLeg.PushBack({ 183,454,33,31 });
	upAnimLeg.PushBack({ 216,454,33,31 });
	upAnimLeg.PushBack({ 249,454,33,31 });
	upAnimLeg.speed = 0.15f;

	leftAnimLeg.PushBack({ 18,516,33,31 });
	leftAnimLeg.PushBack({ 51,516,33,31 });
	leftAnimLeg.PushBack({ 84,516,33,31 });
	leftAnimLeg.PushBack({ 117,516,33,31 });
	leftAnimLeg.PushBack({ 150,516,33,31 });
	leftAnimLeg.PushBack({ 183,516,33,31 });
	leftAnimLeg.PushBack({ 216,516,33,31 });
	leftAnimLeg.PushBack({ 249,516,33,31 });
	leftAnimLeg.speed = 0.15f;

	rightAnimLeg.PushBack({ 18,392,33,31 });
	rightAnimLeg.PushBack({ 51,392,33,31 });
	rightAnimLeg.PushBack({ 84,392,33,31 });
	rightAnimLeg.PushBack({ 117,392,33,31 });
	rightAnimLeg.PushBack({ 150,392,33,31 });
	rightAnimLeg.PushBack({ 183,392,33,31 });
	rightAnimLeg.PushBack({ 216,392,33,31 });
	rightAnimLeg.PushBack({ 249,392,33,31 });
	rightAnimLeg.speed = 0.15f;

	upRightAnimLeg.PushBack({ 18,423,33,31 });
	upRightAnimLeg.PushBack({ 51,423,33,31 });
	upRightAnimLeg.PushBack({ 84,423,33,31 });
	upRightAnimLeg.PushBack({ 117,423,33,31 });
	upRightAnimLeg.PushBack({ 150,423,33,31 });
	upRightAnimLeg.PushBack({ 183,423,33,31 });
	upRightAnimLeg.PushBack({ 216,423,33,31 });
	upRightAnimLeg.PushBack({ 249,423,33,31 });
	upRightAnimLeg.speed = 0.15f;

	upLeftAnimLeg.PushBack({ 18,485,33,31 });
	upLeftAnimLeg.PushBack({ 51,485,33,31 });
	upLeftAnimLeg.PushBack({ 84,485,33,31 });
	upLeftAnimLeg.PushBack({ 117,485,33,31 });
	upLeftAnimLeg.PushBack({ 150,485,33,31 });
	upLeftAnimLeg.PushBack({ 183,485,33,31 });
	upLeftAnimLeg.PushBack({ 216,485,33,31 });
	upLeftAnimLeg.PushBack({ 249,485,33,31 });
	upLeftAnimLeg.speed = 0.15f;

	downRightAnimLeg.PushBack({ 18,361,33,31 });
	downRightAnimLeg.PushBack({ 51,361,33,31 });
	downRightAnimLeg.PushBack({ 84,361,33,31 });
	downRightAnimLeg.PushBack({ 117,361,33,31 });
	downRightAnimLeg.PushBack({ 150,361,33,31 });
	downRightAnimLeg.PushBack({ 183,361,33,31 });
	downRightAnimLeg.PushBack({ 216,361,33,31 });
	downRightAnimLeg.PushBack({ 249,361,33,31 });
	downRightAnimLeg.speed = 0.15f;

	downLeftAnimLeg.PushBack({ 18,547,33,31 });
	downLeftAnimLeg.PushBack({ 51,547,33,31 });
	downLeftAnimLeg.PushBack({ 84,547,33,31 });
	downLeftAnimLeg.PushBack({ 117,547,33,31 });
	downLeftAnimLeg.PushBack({ 150,547,33,31 });
	downLeftAnimLeg.PushBack({ 183,547,33,31 });
	downLeftAnimLeg.PushBack({ 216,547,33,31 });
	downLeftAnimLeg.PushBack({ 249,547,33,31 });
	downLeftAnimLeg.speed = 0.15f;

	downAnimLegReverse.PushBack({ 249,330,33,31 });
	downAnimLegReverse.PushBack({ 216,330,33,31 });
	downAnimLegReverse.PushBack({ 183,330,33,31 });
	downAnimLegReverse.PushBack({ 150,330,33,31 });
	downAnimLegReverse.PushBack({ 117,330,33,31 });
	downAnimLegReverse.PushBack({ 84,330,33,31 });
	downAnimLegReverse.PushBack({ 51,330,33,31 });
	downAnimLegReverse.PushBack({ 18,330,33,31 });
	downAnimLegReverse.speed = 0.15f;

	upAnimLegReverse.PushBack({ 249,454,33,31 });
	upAnimLegReverse.PushBack({ 216,454,33,31 });
	upAnimLegReverse.PushBack({ 183,454,33,31 });
	upAnimLegReverse.PushBack({ 150,454,33,31 });
	upAnimLegReverse.PushBack({ 117,454,33,31 });
	upAnimLegReverse.PushBack({ 84,454,33,31 });
	upAnimLegReverse.PushBack({ 51,454,33,31 });
	upAnimLegReverse.PushBack({ 18,454,33,31 });
	upAnimLegReverse.speed = 0.15f;


	leftAnimLegReverse.PushBack({ 249,516,33,31 });
	leftAnimLegReverse.PushBack({ 216,516,33,31 });
	leftAnimLegReverse.PushBack({ 183,516,33,31 });
	leftAnimLegReverse.PushBack({ 150,516,33,31 });
	leftAnimLegReverse.PushBack({ 117,516,33,31 });
	leftAnimLegReverse.PushBack({ 84,516,33,31 });
	leftAnimLegReverse.PushBack({ 51,516,33,31 });
	leftAnimLegReverse.PushBack({ 18,516,33,31 });
	leftAnimLegReverse.speed = 0.15f;

	rightAnimLegReverse.PushBack({ 249,392,33,31 });
	rightAnimLegReverse.PushBack({ 216,392,33,31 });
	rightAnimLegReverse.PushBack({ 183,392,33,31 });
	rightAnimLegReverse.PushBack({ 150,392,33,31 });
	rightAnimLegReverse.PushBack({ 117,392,33,31 });
	rightAnimLegReverse.PushBack({ 84,392,33,31 });
	rightAnimLegReverse.PushBack({ 51,392,33,31 });
	rightAnimLegReverse.PushBack({ 18,392,33,31 });
	rightAnimLegReverse.speed = 0.15f;

	upRightAnimLegReverse.PushBack({ 249,423,33,31 });
	upRightAnimLegReverse.PushBack({ 216,423,33,31 });
	upRightAnimLegReverse.PushBack({ 183,423,33,31 });
	upRightAnimLegReverse.PushBack({ 150,423,33,31 });
	upRightAnimLegReverse.PushBack({ 117,423,33,31 });
	upRightAnimLegReverse.PushBack({ 84,423,33,31 });
	upRightAnimLegReverse.PushBack({ 51,423,33,31 });
	upRightAnimLegReverse.PushBack({ 18,423,33,31 });
	upRightAnimLegReverse.speed = 0.15f;

	upLeftAnimLegReverse.PushBack({ 249,485,33,31 });
	upLeftAnimLegReverse.PushBack({ 216,485,33,31 });
	upLeftAnimLegReverse.PushBack({ 183,485,33,31 });
	upLeftAnimLegReverse.PushBack({ 150,485,33,31 });
	upLeftAnimLegReverse.PushBack({ 117,485,33,31 });
	upLeftAnimLegReverse.PushBack({ 84,485,33,31 });
	upLeftAnimLegReverse.PushBack({ 51,485,33,31 });
	upLeftAnimLegReverse.PushBack({ 18,485,33,31 });
	upLeftAnimLegReverse.speed = 0.15f;

	downRightAnimLegReverse.PushBack({ 249,361,33,31 });
	downRightAnimLegReverse.PushBack({ 216,361,33,31 });
	downRightAnimLegReverse.PushBack({ 183,361,33,31 });
	downRightAnimLegReverse.PushBack({ 150,361,33,31 });
	downRightAnimLegReverse.PushBack({ 117,361,33,31 });
	downRightAnimLegReverse.PushBack({ 84,361,33,31 });
	downRightAnimLegReverse.PushBack({ 51,361,33,31 });
	downRightAnimLegReverse.PushBack({ 18,361,33,31 });
	downRightAnimLegReverse.speed = 0.15f;

	downLeftAnimLegReverse.PushBack({ 249,547,33,31 });
	downLeftAnimLegReverse.PushBack({ 216,547,33,31 });
	downLeftAnimLegReverse.PushBack({ 183,547,33,31 });
	downLeftAnimLegReverse.PushBack({ 150,547,33,31 });
	downLeftAnimLegReverse.PushBack({ 117,547,33,31 });
	downLeftAnimLegReverse.PushBack({ 84,547,33,31 });
	downLeftAnimLegReverse.PushBack({ 51,547,33,31 });
	downLeftAnimLegReverse.PushBack({ 18,547,33,31 });
	downLeftAnimLegReverse.speed = 0.15f;

	idleAnimDown.PushBack({ 14,181,36,34 });
	idleAnimDown.PushBack({ 50,181,36,34 });
	idleAnimDown.PushBack({ 86,181,36,34 });
	idleAnimDown.PushBack({ 50,181,36,34 });
	idleAnimDown.speed = 0.13f;

	idleAnimUp.PushBack({ 14,146,36,34 });
	idleAnimUp.PushBack({ 50,146,36,34 });
	idleAnimUp.PushBack({ 86,146,36,34 });
	idleAnimUp.PushBack({ 50,146,36,34 });
	idleAnimUp.speed = 0.13f;

	idleAnimLeft.PushBack({ 14,45,36,34 });
	idleAnimLeft.PushBack({ 50,45,36,34 });
	idleAnimLeft.PushBack({ 86,45,36,34 });
	idleAnimLeft.PushBack({ 50,45,36,34 });
	idleAnimLeft.speed = 0.13f;

	idleAnimRight.PushBack({ 14,11,36,34 });
	idleAnimRight.PushBack({ 50,11,36,34 });
	idleAnimRight.PushBack({ 86,11,36,34 });
	idleAnimRight.PushBack({ 50,11,36,34 });
	idleAnimRight.speed = 0.13f;

	idleAnimDownLeft.PushBack({ 14,79,36,34 });
	idleAnimDownLeft.PushBack({ 50,79,36,34 });
	idleAnimDownLeft.PushBack({ 86,79,36,34 });
	idleAnimDownLeft.PushBack({ 50,79,36,34 });
	idleAnimDownLeft.speed = 0.13f;

	idleAnimDownRight.PushBack({ 14,113,36,34 });
	idleAnimDownRight.PushBack({ 50,113,36,34 });
	idleAnimDownRight.PushBack({ 86,113,36,34 });
	idleAnimDownRight.PushBack({ 50,113,36,34 });
	idleAnimDownRight.speed = 0.13f;

	idleAnimUpLeft.PushBack({ 14,249,36,34 });
	idleAnimUpLeft.PushBack({ 50,249,36,34 });
	idleAnimUpLeft.PushBack({ 86,249,36,34 });
	idleAnimUpLeft.PushBack({ 50,249,36,34 });
	idleAnimUpLeft.speed = 0.13f;

	idleAnimUpRight.PushBack({ 14,215,36,34 });
	idleAnimUpRight.PushBack({ 50,215,36,34 });
	idleAnimUpRight.PushBack({ 86,215,36,34 });
	idleAnimUpRight.PushBack({ 50,215,36,34 });
	idleAnimUpRight.speed = 0.13f;

	shootUpAnim.PushBack({ 123,146,36,34 });
	shootUpAnim.PushBack({ 159,146,36,34 });
	shootUpAnim.PushBack({ 195,146,36,34 });
	shootUpAnim.speed = 0.1f;

	shootDownAnim.PushBack({ 124,176,36,34 });
	shootDownAnim.PushBack({ 160,177,36,34 });
	shootDownAnim.PushBack({ 195,177,36,34 });
	shootDownAnim.speed = 0.1f;

	shootLeftAnim.PushBack({ 123,45,36,34 });
	shootLeftAnim.PushBack({ 158,45,36,34 });
	shootLeftAnim.PushBack({ 194,45,36,34 });
	shootLeftAnim.speed = 0.1f;

	shootRightAnim.PushBack({ 122,13,36,34 });
	shootRightAnim.PushBack({ 159,13,36,34 });
	shootRightAnim.PushBack({ 195,13,36,34 });
	shootRightAnim.speed = 0.1f;

	shootDownLeftAnim.PushBack({ 126,79,36,34 });
	shootDownLeftAnim.PushBack({ 162,79,36,34 });
	shootDownLeftAnim.PushBack({ 198,79,36,34 });
	shootDownLeftAnim.speed = 0.1f;

	shootDownRightAnim.PushBack({ 122,113,36,34 });
	shootDownRightAnim.PushBack({ 158,113,36,34 });
	shootDownRightAnim.PushBack({ 194,113,36,34 });
	shootDownRightAnim.speed = 0.1f;

	shootUpLeftAnim.PushBack({ 125,247,36,34 });
	shootUpLeftAnim.PushBack({ 160,247,36,34 });
	shootUpLeftAnim.PushBack({ 196,247,36,34 });
	shootUpLeftAnim.speed = 0.1f;

	shootUpRightAnim.PushBack({ 122,212,36,34 });
	shootUpRightAnim.PushBack({ 156,214,36,34 });
	shootUpRightAnim.PushBack({ 192,215,36,34 });
	shootUpRightAnim.speed = 0.1f;

	///DODGE////////DODGE////////DODGE////////DODGE////////DODGE////////DODGE////////DODGE////////DODGE////////DODGE////////DODGE////////DODGE////////DODGE////////DODGE////////DODGE////////DODGE/////
	upDodge.PushBack({ 308,309, 41, 51 });
	upDodge.PushBack({ 349,309, 41, 51 });
	upDodge.PushBack({ 390,309, 41, 51 });
	upDodge.PushBack({ 431,309, 41, 51 });
	upDodge.PushBack({ 472,309, 41, 51 });
	upDodge.PushBack({ 513,309, 41, 51 });
	upDodge.PushBack({ 554,309, 41, 51 });
	upDodge.PushBack({ 595,309, 41, 51 });
	upDodge.speed = 0.35f;

	rightUpDodge.PushBack({ 308,360, 41, 51 });
	rightUpDodge.PushBack({ 349,360, 41, 51 });
	rightUpDodge.PushBack({ 390,360, 41, 51 });
	rightUpDodge.PushBack({ 431,360, 41, 51 });
	rightUpDodge.PushBack({ 472,360, 41, 51 });
	rightUpDodge.PushBack({ 513,360, 41, 51 });
	rightUpDodge.PushBack({ 554,360, 41, 51 });
	rightUpDodge.PushBack({ 595,360, 41, 51 });
	rightUpDodge.speed = 0.35f;

	leftUpDodge.PushBack({ 308,360, 41, 51 }, true);
	leftUpDodge.PushBack({ 349,360, 41, 51 }, true);
	leftUpDodge.PushBack({ 390,360, 41, 51 }, true);
	leftUpDodge.PushBack({ 431,360, 41, 51 }, true);
	leftUpDodge.PushBack({ 472,360, 41, 51 }, true);
	leftUpDodge.PushBack({ 513,360, 41, 51 }, true);
	leftUpDodge.PushBack({ 554,360, 41, 51 }, true);
	leftUpDodge.PushBack({ 595,360, 41, 51 }, true);
	leftUpDodge.speed = 0.35f;

	rightDodge.PushBack({ 308,411, 41, 51 });
	rightDodge.PushBack({ 349,411, 41, 51 });
	rightDodge.PushBack({ 390,411, 41, 51 });
	rightDodge.PushBack({ 431,411, 41, 51 });
	rightDodge.PushBack({ 472,411, 41, 51 });
	rightDodge.PushBack({ 513,411, 41, 51 });
	rightDodge.PushBack({ 554,411, 41, 51 });
	rightDodge.PushBack({ 595,411, 41, 51 });
	rightDodge.speed = 0.35f;

	leftDodge.PushBack({ 308,411, 41, 51 }, true);
	leftDodge.PushBack({ 349,411, 41, 51 }, true);
	leftDodge.PushBack({ 390,411, 41, 51 }, true);
	leftDodge.PushBack({ 431,411, 41, 51 }, true);
	leftDodge.PushBack({ 472,411, 41, 51 }, true);
	leftDodge.PushBack({ 513,411, 41, 51 }, true);
	leftDodge.PushBack({ 554,411, 41, 51 }, true);
	leftDodge.PushBack({ 595,411, 41, 51 }, true);
	leftDodge.speed = 0.35f;

	rightDownDodge.PushBack({ 308,462, 41, 51 });
	rightDownDodge.PushBack({ 349,462, 41, 51 });
	rightDownDodge.PushBack({ 390,462, 41, 51 });
	rightDownDodge.PushBack({ 431,462, 41, 51 });
	rightDownDodge.PushBack({ 472,462, 41, 51 });
	rightDownDodge.PushBack({ 513,462, 41, 51 });
	rightDownDodge.PushBack({ 554,462, 41, 51 });
	rightDownDodge.PushBack({ 595,462, 41, 51 });
	rightDownDodge.speed = 0.35f;

	leftDownDodge.PushBack({ 308,462, 41, 51 }, true);
	leftDownDodge.PushBack({ 349,462, 41, 51 }, true);
	leftDownDodge.PushBack({ 390,462, 41, 51 }, true);
	leftDownDodge.PushBack({ 431,462, 41, 51 }, true);
	leftDownDodge.PushBack({ 472,462, 41, 51 }, true);
	leftDownDodge.PushBack({ 513,462, 41, 51 }, true);
	leftDownDodge.PushBack({ 554,462, 41, 51 }, true);
	leftDownDodge.PushBack({ 595,462, 41, 51 }, true);
	leftDownDodge.speed = 0.35f;

	downDodge.PushBack({ 308,513, 41, 51 });
	downDodge.PushBack({ 349,513, 41, 51 });
	downDodge.PushBack({ 390,513, 41, 51 });
	downDodge.PushBack({ 431,513, 41, 51 });
	downDodge.PushBack({ 472,513, 41, 51 });
	downDodge.PushBack({ 513,513, 41, 51 });
	downDodge.PushBack({ 554,513, 41, 51 });
	downDodge.PushBack({ 595,513, 41, 51 });
	downDodge.speed = 0.35f;

	idleAnimDownLeg.PushBack({ 18, 299, 33, 31 });
	idleAnimDownRightLeg.PushBack({ 51, 299, 33, 31 });
	idleAnimRightLeg.PushBack({ 84, 299, 33, 31 });
	idleAnimUpRightLeg.PushBack({ 117, 299, 33, 31 });
	idleAnimUpLeg.PushBack({ 150, 299, 33, 31 });
	idleAnimUpLeftLeg.PushBack({ 183, 299, 33, 31 });
	idleAnimLeftLeg.PushBack({ 216, 299, 33, 31 });
	idleAnimDownLeftLeg.PushBack({ 249, 299, 33, 31 });

	dissapear.PushBack({ 0,0,0,0 });

	//Death//Death//Death//Death//Death//Death//Death//Death//Death

	deathback.PushBack({ 580, 11, 54, 54 });
	deathback.PushBack({ 635, 11, 54, 54 });
	deathback.PushBack({ 690, 11, 54, 54 });
	deathback.PushBack({ 745, 11, 54, 54 });
	deathback.PushBack({ 800, 11, 54, 54 });
	deathback.PushBack({ 855, 11, 54, 54 });
	deathback.PushBack({ 910, 11, 54, 54 });
	deathback.PushBack({ 965, 11, 54, 54 });
	deathback.speed = 0.1f;
	deathback.loop = false;

	deathbackright.PushBack({ 580, 66, 54, 54 });
	deathbackright.PushBack({ 635, 66, 54, 54 });
	deathbackright.PushBack({ 690, 66, 54, 54 });
	deathbackright.PushBack({ 745, 66, 54, 54 });
	deathbackright.PushBack({ 800, 66, 54, 54 });
	deathbackright.PushBack({ 855, 66, 54, 54 });
	deathbackright.PushBack({ 910, 66, 54, 54 });
	deathbackright.PushBack({ 965, 66, 54, 54 });
	deathbackright.speed = 0.1f;
	deathbackright.loop = false;

	deathright.PushBack({ 580, 121, 54, 54 });
	deathright.PushBack({ 635, 121, 54, 54 });
	deathright.PushBack({ 690, 121, 54, 54 });
	deathright.PushBack({ 745, 121, 54, 54 });
	deathright.PushBack({ 800, 121, 54, 54 });
	deathright.PushBack({ 855, 121, 54, 54 });
	deathright.PushBack({ 965, 121, 54, 54 });
	deathright.speed = 0.1f;
	deathright.loop = false;

	deathleft.PushBack({ 580, 121, 54, 54 }, true);
	deathleft.PushBack({ 635, 121, 54, 54 }, true);
	deathleft.PushBack({ 690, 121, 54, 54 }, true);
	deathleft.PushBack({ 745, 121, 54, 54 }, true);
	deathleft.PushBack({ 800, 121, 54, 54 }, true);
	deathleft.PushBack({ 855, 121, 54, 54 }, true);
	deathleft.PushBack({ 965, 121, 54, 54 }, true);
	deathleft.speed = 0.1f;
	deathleft.loop = false;

	deathfrontright.PushBack({ 580, 176, 54, 54 });
	deathfrontright.PushBack({ 635, 176, 54, 54 });
	deathfrontright.PushBack({ 690, 176, 54, 54 });
	deathfrontright.PushBack({ 745, 176, 54, 54 });
	deathfrontright.PushBack({ 800, 176, 54, 54 });
	deathfrontright.PushBack({ 855, 176, 54, 54 });
	deathfrontright.PushBack({ 910, 176, 54, 54 });
	deathfrontright.PushBack({ 965, 176, 54, 54 });
	deathfrontright.speed = 0.1f;
	deathfrontright.loop = false;


	deathfront.PushBack({ 580, 231, 54, 54 });
	deathfront.PushBack({ 635, 231, 54, 54 });
	deathfront.PushBack({ 690, 231, 54, 54 });
	deathfront.PushBack({ 745, 231, 54, 54 });
	deathfront.PushBack({ 800, 231, 54, 54 });
	deathfront.PushBack({ 855, 231, 54, 54 });
	deathfront.PushBack({ 910, 231, 54, 54 });
	deathfront.PushBack({ 965, 231, 54, 54 });
	deathfront.speed = 0.1f;
	deathfront.loop = false;


	//Win//Win//Win//Win//Win//Win//Win//Win//Win//Win//Win//Win//Win//Win//Win//Win//Win//Win//Win//Win

	Win.PushBack({ 1294, 311, 40, 56 });
	Win.PushBack({ 1334, 311, 40, 56 });
	Win.PushBack({ 1374, 311, 40, 56 });
	Win.PushBack({ 1414, 311, 40, 56 });
	Win.PushBack({ 1454, 311, 40, 56 });
	Win.PushBack({ 1494, 311, 40, 56 });
	Win.PushBack({ 1534, 311, 40, 56 });
	Win.PushBack({ 1574, 311, 40, 56 });
	Win.PushBack({ 1294, 367, 40, 56 });
	Win.PushBack({ 1334, 367, 40, 56 });
	Win.PushBack({ 1375, 367, 40, 56 });
	Win.PushBack({ 1416, 367, 40, 56 });
	Win.PushBack({ 1494, 367, 40, 56 });
	Win.loop = false;
	Win.speed = 0.1f;

	//Hurt//Hurt//Hurt//Hurt//Hurt//Hurt//Hurt//Hurt//Hurt//Hurt//Hurt//Hurt//Hurt//Hurt//Hurt//Hurt//Hurt//Hurt//Hurt//Hurt

	Hurtup.PushBack({ 1646, 19, 29, 56 });
	Hurtup.PushBack({ 1675, 19, 29, 56 });
	Hurtup.PushBack({ 1705, 19, 29, 56 });
	Hurtup.PushBack({ 1733, 19, 29, 56 });
	Hurtup.speed = 0.1f;
	Hurtup.loop = false;

	Hurtdown.PushBack({ 1646, 244, 29, 56 });
	Hurtdown.PushBack({ 1675, 244, 29, 56 });
	Hurtdown.PushBack({ 1705, 244, 29, 56 });
	Hurtdown.PushBack({ 1733, 244, 29, 56 });
	Hurtdown.speed = 0.1f;
	Hurtdown.loop = false;

	Hurtright.PushBack({ 1646, 131, 29, 56 });
	Hurtright.PushBack({ 1675, 131, 29, 56 });
	Hurtright.PushBack({ 1705, 131, 29, 56 });
	Hurtright.PushBack({ 1733, 131, 29, 56 });
	Hurtright.speed = 0.1f;
	Hurtright.loop = false;

	Hurtleft.PushBack({ 1646, 131, 29, 56 },true);
	Hurtleft.PushBack({ 1675, 131, 29, 56 },true);//mirror
	Hurtleft.PushBack({ 1705, 131, 29, 56 },true);
	Hurtleft.PushBack({ 1733, 131, 29, 56 },true);
	Hurtleft.speed = 0.1f;
	Hurtleft.loop = false;

	Hurtupleft.PushBack({ 1646,76, 29, 56 }, true);
	Hurtupleft.PushBack({ 1675,76, 29, 56 }, true);//mirror
	Hurtupleft.PushBack({ 1705,76, 29, 56 }, true);
	Hurtupleft.PushBack({ 1733,76, 29, 56 }, true);
	Hurtupleft.speed = 0.1f;
	Hurtupleft.loop = false;

	Hurtupright.PushBack({ 1646, 76, 29, 56 });
	Hurtupright.PushBack({ 1675, 76, 29, 56 });
	Hurtupright.PushBack({ 1705, 76, 29, 56 });
	Hurtupright.PushBack({ 1733, 76, 29, 56 });
	Hurtupright.speed = 0.1f;
	Hurtupright.loop = false;

	Hurtdownright.PushBack({ 1646, 188, 29, 56 });
	Hurtdownright.PushBack({ 1675, 188, 29, 56 });
	Hurtdownright.PushBack({ 1705, 188, 29, 56 });
	Hurtdownright.PushBack({ 1733, 188, 29, 56 });
	Hurtdownright.speed = 0.1f;
	Hurtdownright.loop = false;

	Hurtdownleft.PushBack({ 1646, 188, 29, 56 }, true);
	Hurtdownleft.PushBack({ 1675, 188, 29, 56 }, true);
	Hurtdownleft.PushBack({ 1705, 188, 29, 56 }, true);//mirror
	Hurtdownleft.PushBack({ 1733, 188, 29, 56 }, true);
	Hurtdownleft.speed = 0.1f;
	Hurtdownleft.loop = false;



	explosion1.PushBack({ 146, 841, 32, 32 });
	explosion1.PushBack({ 179, 841, 32, 32 });
	explosion1.PushBack({ 212, 841, 32, 32 });
	explosion1.PushBack({ 245, 841, 32, 32 });
	explosion1.PushBack({ 146, 874, 32, 32 });
	explosion1.PushBack({ 179, 874, 32, 32 });
	explosion1.PushBack({ 212, 874, 32, 32 });
	explosion1.PushBack({ 245, 874, 32, 32 });


	

	explosion2.PushBack({ 902, 690, 64, 64 });
	explosion2.PushBack({ 967, 690, 64, 64 });
	explosion2.PushBack({ 1032, 690, 64, 64 });
	explosion2.PushBack({ 1097, 690, 64, 64 });
	explosion2.PushBack({ 1162, 690, 64, 64 });
	explosion2.PushBack({ 1227, 690, 64, 64 });
	explosion2.PushBack({ 1292, 690, 64, 64 });
	explosion2.PushBack({ 902, 755, 64, 64 });
	explosion2.PushBack({ 967, 755, 64, 64 });
	explosion2.PushBack({ 1032, 755, 64, 64 });
	explosion2.PushBack({ 1097, 755, 64, 64 });
	explosion2.PushBack({ 1162, 755, 64, 64 });
	explosion2.PushBack({ 1227, 755, 64, 64 });
	explosion2.PushBack({ 1292, 755, 64, 64 });
	explosion2.PushBack({ 902, 820, 64, 64 });
	explosion2.PushBack({ 967, 820, 64, 64 });
	explosion2.PushBack({ 1032, 820, 64, 64 });
	explosion2.PushBack({ 1097, 820, 64, 64 });
	explosion2.PushBack({ 1162, 820, 64, 64 });
	explosion2.PushBack({ 1227, 820, 64, 64 });
	explosion2.PushBack({ 1292, 820, 64, 64 });
	explosion2.PushBack({ 902, 885, 64, 64 });
	explosion2.PushBack({ 967, 885, 64, 64 });
	explosion2.PushBack({ 1032, 885, 64, 64 });
	explosion2.PushBack({ 1097, 885, 64, 64 });
	explosion2.PushBack({ 1162, 885, 64, 64 });
	explosion2.PushBack({ 1227, 885, 64, 64 });
	explosion2.PushBack({ 1292, 885, 64, 64 });

	




	//FOGONAZO //FOGONAZO //FOGONAZO //FOGONAZO //FOGONAZO //FOGONAZO //FOGONAZO //FOGONAZO //FOGONAZO //FOGONAZO 

	fogonazoDown.PushBack({ 845, 1856, 60, 61 });
	fogonazoDown.PushBack({ 906, 1841, 60, 61 });
	fogonazoDown.PushBack({ 967, 1841, 60, 61 });

	fogonazoDownRight.PushBack({ 1028, 1841, 60, 61 });
	fogonazoDownRight.PushBack({ 1089, 1841, 60, 61 });
	fogonazoDownRight.PushBack({ 1150, 1841, 60, 61 });

	fogonazoDownLeft.PushBack({ 1028, 1841, 60, 61 }, true);
	fogonazoDownLeft.PushBack({ 1089, 1841, 60, 61 }, true);
	fogonazoDownLeft.PushBack({ 1150, 1841, 60, 61 }, true);

	fogonazoUp.PushBack({ 1211, 1841, 60, 61 });
	fogonazoUp.PushBack({ 1272, 1841, 60, 61 });
	fogonazoUp.PushBack({ 1333, 1841, 60, 61 });
	
	fogonazoUpRight.PushBack({ 1394, 1841, 60, 61 });
	fogonazoUpRight.PushBack({ 1455, 1841, 60, 61 });
	fogonazoUpRight.PushBack({ 1516, 1841, 60, 61 });

	fogonazoUpLeft.PushBack({ 1394, 1841, 60, 61 }, true);
	fogonazoUpLeft.PushBack({ 1455, 1841, 60, 61 }, true);
	fogonazoUpLeft.PushBack({ 1516, 1841, 60, 61 }, true);

	fogonazoRight.PushBack({ 1577, 1841, 60, 61 });
	fogonazoRight.PushBack({ 1638, 1841, 60, 61 });
	fogonazoRight.PushBack({ 1699, 1841, 60, 61 });

	fogonazoLeft.PushBack({ 1577, 1841, 60, 61 }, true);
	fogonazoLeft.PushBack({ 1638, 1841, 60, 61 }, true);
	fogonazoLeft.PushBack({ 1699, 1841, 60, 61 }, true);


	//MISSILE LAUNCHER //MISSILE LAUNCHER //MISSILE LAUNCHER //MISSILE LAUNCHER //MISSILE LAUNCHER //MISSILE LAUNCHER //MISSILE LAUNCHER //MISSILE LAUNCHER //MISSILE LAUNCHER 



	//STRUCTURES //STRUCTURES //STRUCTURES //STRUCTURES //STRUCTURES //STRUCTURES //STRUCTURES //STRUCTURES 

	

	//MEDICS //MEDICS //MEDICS //MEDICS //MEDICS //MEDICS //MEDICS //MEDICS 


	//GRENADE //GRENADE //GRENADE //GRENADE //GRENADE //GRENADE //GRENADE //GRENADE 
	grenadeThrowRight.PushBack({ 230, 11, 36, 34 });
	grenadeThrowRight.PushBack({ 266, 11, 36, 34 });
	grenadeThrowRight.PushBack({ 302, 11, 36, 34 });
	grenadeThrowRight.PushBack({ 338, 11, 36, 34 });
	grenadeThrowRight.PushBack({ 374, 11, 36, 34 });
	grenadeThrowRight.speed = 0.25f;

	grenadeThrowLeft.PushBack({ 230, 45, 36, 34 });
	grenadeThrowLeft.PushBack({ 266, 45, 36, 34 });
	grenadeThrowLeft.PushBack({ 302, 45, 36, 34 });
	grenadeThrowLeft.PushBack({ 338, 45, 36, 34 });
	grenadeThrowLeft.PushBack({ 374, 45, 36, 34 });
	grenadeThrowLeft.speed = 0.25f;

	grenadeThrowDownLeft.PushBack({ 230, 79, 36, 34 });
	grenadeThrowDownLeft.PushBack({ 266, 79, 36, 34 });
	grenadeThrowDownLeft.PushBack({ 302, 79, 36, 34 });
	grenadeThrowDownLeft.PushBack({ 338, 79, 36, 34 });
	grenadeThrowDownLeft.PushBack({ 374, 79, 36, 34 });
	grenadeThrowDownLeft.speed = 0.25f;

	grenadeThrowDownRight.PushBack({ 230, 113, 36, 34 });
	grenadeThrowDownRight.PushBack({ 266, 113, 36, 34 });
	grenadeThrowDownRight.PushBack({ 302, 113, 36, 34 });
	grenadeThrowDownRight.PushBack({ 338, 113, 36, 34 });
	grenadeThrowDownRight.PushBack({ 374, 113, 36, 34 });
	grenadeThrowDownRight.speed = 0.25f;

	grenadeThrowUp.PushBack({ 230, 147, 36, 34 });
	grenadeThrowUp.PushBack({ 266, 147, 36, 34 });
	grenadeThrowUp.PushBack({ 302, 147, 36, 34 });
	grenadeThrowUp.PushBack({ 338, 147, 36, 34 });
	grenadeThrowUp.PushBack({ 374, 147, 36, 34 });
	grenadeThrowUp.speed = 0.25f;

	grenadeThrowDown.PushBack({ 230, 181, 36, 34 });
	grenadeThrowDown.PushBack({ 266, 181, 36, 34 });
	grenadeThrowDown.PushBack({ 302, 181, 36, 34 });
	grenadeThrowDown.PushBack({ 338, 181, 36, 34 });
	grenadeThrowDown.PushBack({ 374, 181, 36, 34 });
	grenadeThrowDown.speed = 0.25f;

	grenadeThrowUpRight.PushBack({ 230, 215, 36, 34 });
	grenadeThrowUpRight.PushBack({ 266, 215, 36, 34 });
	grenadeThrowUpRight.PushBack({ 302, 215, 36, 34 });
	grenadeThrowUpRight.PushBack({ 338, 215, 36, 34 });
	grenadeThrowUpRight.PushBack({ 374, 215, 36, 34 });
	grenadeThrowUpRight.speed = 0.25f;

	grenadeThrowUpLeft.PushBack({ 230, 249, 36, 34 });
	grenadeThrowUpLeft.PushBack({ 266, 249, 36, 34 });
	grenadeThrowUpLeft.PushBack({ 302, 249, 36, 34 });
	grenadeThrowUpLeft.PushBack({ 338, 249, 36, 34 });
	grenadeThrowUpLeft.PushBack({ 374, 249, 36, 34 });
	grenadeThrowUpLeft.speed = 0.25f;


	

}	

ModulePlayer::~ModulePlayer()
{

}
bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Sprites/spritesheet2.28.png");
	currentAnimation = &idleAnimUp;
	legAnimation = &upAnimLeg;
	isDead = false;
	winCon = false;
	isHurt = false;


	laserFx = App->audio->LoadFx("Assets/Fx/Player Shot.wav");
	explosionFx = App->audio->LoadFx("Assets/Fx/explosion.wav");
	flamethrowerFx = App->audio->LoadFx("Assets/Fx/Flamethrower.wav");
	milkyhurtvoice = App->audio->LoadFx("Assets/Fx/milkyhurtvoice.wav");
	hp = 120;
	score = 000;
	timer = 99;
	weapon = 0;

	position.x = 180;
	position.y = 120;

	destroyed = false;

	collider = App->collisions->AddCollider({ position.x, position.y, 32, 47 }, Collider::Type::PLAYER, this);
	colliderUp = App->collisions->AddCollider({ position.x, position.y - 3, 32, 3 }, Collider::Type::UP_PLAYER, this);
	colliderDown = App->collisions->AddCollider({ position.x, position.y + 47, 32, 3 }, Collider::Type::DOWN_PLAYER, this);
	colliderRight = App->collisions->AddCollider({ position.x + 6, position.y, 3, 4 }, Collider::Type::RIGHT_PLAYER, this);
	colliderLeft = App->collisions->AddCollider({ position.x , position.y, 3, 4 }, Collider::Type::LEFT_PLAYER, this);

	deathfront.Reset();
	deathback.Reset();
	deathright.Reset();
	deathleft.Reset();
	deathfrontright.Reset();
	deathfrontleft.Reset();
	deathbackright.Reset();
	deathbackleft.Reset();

	Win.Reset();


	return ret;
}



void ModulePlayer::GamepadUpdate()
{
	GamePad& pad = App->input->pads[0];

	if (pad.l_x < -0.2f && pad.l_x < 0.0f) {
		App->input->keys[SDL_SCANCODE_A] = Key_State::KEY_REPEAT;
	}
	if (pad.l_x > 0.2f && pad.l_x > 0.0f) {
		App->input->keys[SDL_SCANCODE_D] = Key_State::KEY_REPEAT;
	}
	if (pad.l_y > 0.2f && pad.l_y > 0.0f) {
		App->input->keys[SDL_SCANCODE_S] = Key_State::KEY_REPEAT;
	}
	if (pad.l_y < -0.2f && pad.l_y < 0.0f) {
		App->input->keys[SDL_SCANCODE_W] = Key_State::KEY_REPEAT;
	}
	if (pad.r2 == 1) {
		App->input->keys[SDL_SCANCODE_SPACE] = Key_State::KEY_REPEAT;
	}
}

void ModulePlayer::MoveUpdate()
{

	if (leftLock == true && upLock == true && downLock == true && rightLock == true) 
	{
		leftLock == true;
		upLock == true; 
		downLock == true; 
		rightLock == true;
	}

	if (isHurt == false && isDead == false && winCon == false)
		if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT &&
			App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT &&
			isDodging == false)
		{
			moveDir = UPLEFT;
			if (leftLock == false &&
				upLock == false) {
				position.x -= speed;
				position.y -= speed;
			}
			else if (leftLock == false) 
			{
				position.x -= speed;
			}
			else if (upLock == false) 
			{
				position.y -= speed;
			}

		;

			if (App->input->keys[SDL_SCANCODE_SPACE] != Key_State::KEY_REPEAT && isShooting == false)
				bulletDir = UPLEFT;
			if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_REPEAT && (bulletDir == DOWNRIGHT || bulletDir == DOWN || bulletDir == RIGHT))
			{
				if (legAnimation != &downRightAnimLegReverse)
				{
					downRightAnimLegReverse.Reset();
					legAnimation = &downRightAnimLegReverse;
				}
			}
			else {
				if (legAnimation != &upLeftAnimLeg)
				{
					upLeftAnimLeg.Reset();
					legAnimation = &upLeftAnimLeg;
				}
			}
		}
		else if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT &&
			App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT &&
			
			isDodging == false)
		{
			moveDir = DOWNLEFT;
			if (leftLock == false &&
				downLock == false) 
			{
				position.x -= speed;
				position.y += speed;
			}
			else if (leftLock == false)
			{
				position.x -= speed;
			}
			else if (downLock == false)
			{
				position.y += speed;
			}
	

			if (App->input->keys[SDL_SCANCODE_SPACE] != Key_State::KEY_REPEAT && isShooting == false)
				bulletDir = DOWNLEFT;
			if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_REPEAT && (bulletDir == UP || bulletDir == UPRIGHT))
			{
				if (legAnimation != &upRightAnimLegReverse)
				{
					upRightAnimLegReverse.Reset();
					legAnimation = &upRightAnimLegReverse;
				}
			}
			else if (bulletDir == UPLEFT) {
				legAnimation = &downLeftAnimLeg;
			}

			else {
				if (legAnimation != &downLeftAnimLeg)
				{
					downLeftAnimLeg.Reset();
					legAnimation = &downLeftAnimLeg;
				}
			}
		}

		else if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT &&
			App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT &&
			isDodging == false)
		{
			moveDir = DOWNRIGHT;
			if (rightLock == false &&
				downLock == false)
			{
				position.x += speed;
				position.y += speed;
			}
			else if (rightLock == false)
			{
				position.x += speed;
			}
			else if (downLock == false)
			{
				position.y += speed;
			}


			if (App->input->keys[SDL_SCANCODE_SPACE] != Key_State::KEY_REPEAT && isShooting == false)
				bulletDir = DOWNRIGHT;
			if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_REPEAT && (bulletDir == UP || bulletDir == UPLEFT))
			{
				if (legAnimation != &upLeftAnimLegReverse)
				{
					upLeftAnimLegReverse.Reset();
					legAnimation = &upLeftAnimLegReverse;
				}
			}
			else if (bulletDir == UPRIGHT) {
				if (bulletDir == UPRIGHT) {
					legAnimation = &downRightAnimLeg;
				}
			}
			else {
				if (legAnimation != &downRightAnimLeg)
				{
					legAnimation = &downRightAnimLeg;
				}
			}
		}
		else if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT &&
			App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT &&
			isDodging == false)
		{
			moveDir = UPRIGHT;
			if (rightLock == false &&
				upLock == false)
			{
				position.x += speed;
				position.y -= speed;
			}
			else if (rightLock == false)
			{
				position.x += speed;
			}
			else if (upLock == false)
			{
				position.y -= speed;
			}


			if (App->input->keys[SDL_SCANCODE_SPACE] != Key_State::KEY_REPEAT && isShooting == false)
				bulletDir = UPRIGHT;
			if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_REPEAT && (bulletDir == DOWNLEFT || bulletDir == DOWN || bulletDir == LEFT))
			{
				if (legAnimation != &downLeftAnimLegReverse)
				{
					downLeftAnimLegReverse.Reset();
					legAnimation = &downLeftAnimLegReverse;
				}
			}
			else {
				if (legAnimation != &upRightAnimLeg)
				{
					upRightAnimLeg.Reset();
					legAnimation = &upRightAnimLeg;
				}
			}
		}
		else if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT &&
			
			isDodging == false)
		{
			moveDir = LEFT;

			if (leftLock == false)
			position.x -= speed;

			if (App->input->keys[SDL_SCANCODE_SPACE] != Key_State::KEY_REPEAT && isShooting == false)
				bulletDir = LEFT;
			if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_REPEAT && (bulletDir == RIGHT || bulletDir == UPRIGHT || bulletDir == DOWNRIGHT))
			{
				if (legAnimation != &rightAnimLegReverse)
				{
					rightAnimLegReverse.Reset();
					legAnimation = &rightAnimLegReverse;
				}
			}
			else {
				if (legAnimation != &leftAnimLeg)
				{
					leftAnimLeg.Reset();
					legAnimation = &leftAnimLeg;
				}
			}
		}
		else if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT &&
		
			isDodging == false)
		{
			moveDir = RIGHT;
			if (rightLock == false) {
				position.x += speed;
			}
		
			if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_REPEAT && (bulletDir == LEFT || bulletDir == UPLEFT || bulletDir == DOWNLEFT))
			{
				if (legAnimation != &leftAnimLegReverse)
				{
					leftAnimLegReverse.Reset();
					legAnimation = &leftAnimLegReverse;
				}
			}
			else {
				if (legAnimation != &rightAnimLeg)
				{
					rightAnimLeg.Reset();
					legAnimation = &rightAnimLeg;
				}
			}

			if (App->input->keys[SDL_SCANCODE_SPACE] != Key_State::KEY_REPEAT && isShooting == false)
				bulletDir = RIGHT;

		}
		else if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT &&
		
			isDodging == false)
		{
			moveDir = DOWN;

			if (downLock == false)
			position.y += speed;

			if (App->input->keys[SDL_SCANCODE_SPACE] != Key_State::KEY_REPEAT && isShooting == false)
				bulletDir = DOWN;
			if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_REPEAT && (bulletDir == UP || bulletDir == UPRIGHT || bulletDir == UPLEFT))
			{
				if (legAnimation != &upAnimLegReverse)
				{
					upAnimLegReverse.Reset();
					legAnimation = &upAnimLegReverse;
				}
			}
			else {
				if (legAnimation != &downAnimLeg)
				{
					downAnimLeg.Reset();
					legAnimation = &downAnimLeg;
				}
			}
		}
		else if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT &&
			isDodging == false)
		{
			moveDir = UP;

			if (upLock == false)
			position.y -= speed;

			if (App->input->keys[SDL_SCANCODE_SPACE] != Key_State::KEY_REPEAT && isShooting == false)
				bulletDir = UP;
			if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_REPEAT && (bulletDir == DOWN || bulletDir == DOWNRIGHT || bulletDir == DOWNLEFT))
			{
				if (legAnimation != &downAnimLegReverse)
				{
					downAnimLegReverse.Reset();
					legAnimation = &downAnimLegReverse;
				}
			}
			else {
				if (legAnimation != &upAnimLeg)
				{
					upAnimLeg.Reset();
					legAnimation = &upAnimLeg;
				}
			}
		}
		else if ((App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE && App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE && App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE & App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE) && (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_REPEAT)) {
			moveDir = bulletDir;
		}

			if (App->render->camera.y + SCREEN_HEIGHT < position.y + 47)
			{

				App->player->downLock = true;

				position.y--;
				
				isDodging = false;
			}

			if (App->render->camera.y  > position.y )
			{

				App->player->upLock = true;

				position.y++;

				isDodging = false;
			}

			if (App->render->camera.x > position.x)
			{

				App->player->leftLock = true;

				position.x++;

				isDodging = false;
			}
			if (App->render->camera.x + SCREEN_WIDTH < position.x +33)
			{

				App->player->rightLock = true;

				position.x--;

				isDodging = false;
			}

			

}

void ModulePlayer::ShootingUpdate() 
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_REPEAT && isShooting == false && isDead == false && winCon == false)
	{
		isShooting = true;
	}


	if (isDodging == false && isHurt == false && isShooting == true && isDead == false && winCon == false)
	{

		switch (weapon)
		{
		case 0:
			if (App->player->shootCoolDown > 1 && isDodging == false && cartridge != 0) {
				switch (bulletDir)
				{
				case LEFT:
					App->particles->AddParticle(App->particles->PlayerShotLeft, position.x, position.y + 12, -10, 0, false, Collider::Type::PLAYER_SHOT);

					if (cartridge == 6)
					App->audio->PlayFx(laserFx);
					shootCoolDown = 0;
					break;
				case RIGHT:
					App->particles->AddParticle(App->particles->PlayerShotRight, position.x + 20, position.y + 12, 10, 0, false, Collider::Type::PLAYER_SHOT);

					if (cartridge == 6)
					App->audio->PlayFx(laserFx);
					shootCoolDown = 0;
					break;
				case DOWN:
					App->particles->AddParticle(App->particles->PlayerShotDown, position.x + 9, position.y + 26, 0, 10, false, Collider::Type::PLAYER_SHOT);

					if (cartridge == 6)
					App->audio->PlayFx(laserFx);
					shootCoolDown = 0;
					break;
				case UP:
					App->particles->AddParticle(App->particles->PlayerShotUp, position.x + 17, position.y, 0, -10, false, Collider::Type::PLAYER_SHOT);

					if (cartridge == 6)
					App->audio->PlayFx(laserFx);
					shootCoolDown = 0;
					break;
				case DOWNLEFT:
					App->particles->AddParticle(App->particles->PlayerShotDownLeft, position.x + 4, position.y + 18, -7, 7, false, Collider::Type::PLAYER_SHOT);

					if (cartridge == 6)
					App->audio->PlayFx(laserFx);
					shootCoolDown = 0;
					break;
				case DOWNRIGHT:
					App->particles->AddParticle(App->particles->PlayerShotDownRight, position.x + 20, position.y + 18, 7, 7, false, Collider::Type::PLAYER_SHOT);

					if (cartridge == 6)
					App->audio->PlayFx(laserFx);
					shootCoolDown = 0;
					break;
				case UPLEFT:
					App->particles->AddParticle(App->particles->PlayerShotUpLeft, position.x + 4, position.y + 1, -7, -7, false, Collider::Type::PLAYER_SHOT);

					if (cartridge == 6)
					App->audio->PlayFx(laserFx);
					shootCoolDown = 0;
					break;
				case UPRIGHT:
					App->particles->AddParticle(App->particles->PlayerShotUpRight, position.x + 20, position.y, 14, -14, false, Collider::Type::PLAYER_SHOT);

					if (cartridge == 6)
					App->audio->PlayFx(laserFx);
					shootCoolDown = 0;
					break;
				}
				cartridge--;
			}
			break;
		case 1:
			if (bullets <= 0)
			{
				weapon = 0;
			}

			if (App->player->shootCoolDown > 5 && isDodging == false) {
				switch (bulletDir)
				{
				case LEFT:
					App->particles->AddParticle(App->particles->flameThrower, position.x - 11, position.y - 3, -5, 0, true, Collider::Type::FLAME);
					App->audio->PlayFx(flamethrowerFx);
					shootCoolDown = 0;
					break;
				case RIGHT:
					App->particles->AddParticle(App->particles->flameThrower, position.x + 15, position.y - 3, 5, 0, true, Collider::Type::FLAME);
					App->audio->PlayFx(flamethrowerFx);
					shootCoolDown = 0;
					break;
				case DOWN:
					App->particles->AddParticle(App->particles->flameThrower, position.x - 2, position.y + 16, 0, 5, true, Collider::Type::FLAME);
					App->audio->PlayFx(flamethrowerFx);
					shootCoolDown = 0;
					break;
				case UP:
					App->particles->AddParticle(App->particles->flameThrower, position.x + 7, position.y - 13, 0, -5, true, Collider::Type::FLAME);
					App->audio->PlayFx(flamethrowerFx);
					shootCoolDown = 0;
					break;
				case DOWNLEFT:
					App->particles->AddParticle(App->particles->flameThrower, position.x - 11, position.y + 7, -4, 4, true, Collider::Type::FLAME);
					App->audio->PlayFx(flamethrowerFx);
					shootCoolDown = 0;
					break;
				case DOWNRIGHT:
					App->particles->AddParticle(App->particles->flameThrower, position.x + 10, position.y + 8, 5, 5, true, Collider::Type::FLAME);
					App->audio->PlayFx(flamethrowerFx);
					shootCoolDown = 0;
					break;
				case UPLEFT:
					App->particles->AddParticle(App->particles->flameThrower, position.x - 7, position.y - 11, -4, -4, true, Collider::Type::FLAME);
					App->audio->PlayFx(flamethrowerFx);
					shootCoolDown = 0;
					break;
				case UPRIGHT:
					App->particles->AddParticle(App->particles->flameThrower, position.x + 13, position.y - 11, 4, -4, true, Collider::Type::FLAME);
					App->audio->PlayFx(flamethrowerFx);
					shootCoolDown = 0;
					break;
				}
				bullets--;
			}
			break;
		case 2:
			if (bullets <= 0)
			{
				weapon = 0;
			}
			if (App->player->shootCoolDown > 7 && isDodging == false) {
				switch (bulletDir)
				{
				case LEFT:
					App->particles->AddParticle(App->particles->powerUpThreeBullets, position.x, position.y + 12, -5, 0, false, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->powerUpThreeBullets, position.x , position.y + 12, -5, -1, false, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->powerUpThreeBullets, position.x , position.y + 12, -5, 1, false, Collider::Type::PLAYER_SHOT);
					App->audio->PlayFx(laserFx);
					shootCoolDown = 0;
					break;
				case RIGHT:
					App->particles->AddParticle(App->particles->powerUpThreeBullets, position.x + 20, position.y + 12, 5, 0, false, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->powerUpThreeBullets, position.x + 20, position.y + 12, 5, 1, false, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->powerUpThreeBullets, position.x + 20, position.y + 12, 5, -1, false, Collider::Type::PLAYER_SHOT);
					App->audio->PlayFx(laserFx);
					shootCoolDown = 0;
					break;
				case DOWN:
					App->particles->AddParticle(App->particles->powerUpThreeBullets, position.x + 9, position.y + 26, 0, 5, false, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->powerUpThreeBullets, position.x + 9, position.y + 26, 1, 5, false, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->powerUpThreeBullets, position.x + 9, position.y + 26, -1, 5, false, Collider::Type::PLAYER_SHOT);
					App->audio->PlayFx(laserFx);
					shootCoolDown = 0;
					break;
				case UP:
					App->particles->AddParticle(App->particles->powerUpThreeBullets, position.x + 17, position.y, 0, -5, false, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->powerUpThreeBullets, position.x + 17, position.y, -1, -5, false, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->powerUpThreeBullets, position.x + 17, position.y, 1, -5, false, Collider::Type::PLAYER_SHOT);
					App->audio->PlayFx(laserFx);
					shootCoolDown = 0;
					break;
				case DOWNLEFT:
					App->particles->AddParticle(App->particles->powerUpThreeBullets, position.x + 4, position.y + 18, -5, 5, false, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->powerUpThreeBullets, position.x + 4, position.y + 18, -3, 5, false, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->powerUpThreeBullets, position.x + 4, position.y + 18, -5, 3, false, Collider::Type::PLAYER_SHOT);
					App->audio->PlayFx(laserFx);
					shootCoolDown = 0;
					break;
				case DOWNRIGHT:
					App->particles->AddParticle(App->particles->powerUpThreeBullets, position.x + 20, position.y + 18, 5, 5, false, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->powerUpThreeBullets, position.x + 20, position.y + 18, 3, 5, false, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->powerUpThreeBullets, position.x + 20, position.y + 12, 5, 3, false, Collider::Type::PLAYER_SHOT);
					App->audio->PlayFx(laserFx);
					shootCoolDown = 0;
					break;
				case UPLEFT:
					App->particles->AddParticle(App->particles->powerUpThreeBullets, position.x + 4, position.y + 1, -5, -5, false, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->powerUpThreeBullets, position.x + 4, position.y + 1, -3, -5, false, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->powerUpThreeBullets, position.x + 4, position.y + 1, -5, -3, false, Collider::Type::PLAYER_SHOT);
					App->audio->PlayFx(laserFx);
					shootCoolDown = 0;
					break;
				case UPRIGHT:
					App->particles->AddParticle(App->particles->powerUpThreeBullets, position.x + 20, position.y, 5, -5, false, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->powerUpThreeBullets, position.x + 20, position.y, 3, -5, false, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->powerUpThreeBullets, position.x + 20, position.y, 5, -3, false, Collider::Type::PLAYER_SHOT);
					App->audio->PlayFx(laserFx);
					shootCoolDown = 0;
					break;
				}
				bullets--;
			}
			break;
		}
	}

	if (isHurt == true || isDodging == true)
	{
		cartridge = 0;
	}
	switch (weapon)
	{
	case 0:
		if (cartridge == 0)
		{
			isShooting = false;
		}
		break;
	case 1:
		if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_UP && isShooting == true)
		{
			isShooting = false;
		}
		break;
	case 2:
		if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_UP && isShooting == true)
		{
			isShooting = false;
		}
		break;
	}
	

	if (cartridge >= 0 && shootCoolDown > 25)
	{
		cartridge = 6;
	}
}

void ModulePlayer::AnimationLegTorsoUpdate() 
{
	if (App->input->keys[SDL_SCANCODE_SPACE] != Key_State::KEY_REPEAT &&
		isHurt == false && isShooting == false) {
		switch (moveDir)
		{
		case LEFT:
			currentAnimation = &idleAnimLeft;
			offsetx = 5;
			break;
		case RIGHT:
			currentAnimation = &idleAnimRight;
			offsetx = -2;
			break;
		case DOWN:
			currentAnimation = &idleAnimDown;
			offsety = -1;
			break;
		case UP:
			currentAnimation = &idleAnimUp;
			offsetx = 1;
			offsety = -1;
			break;
		case DOWNLEFT:
			currentAnimation = &idleAnimDownLeft;
			offsetx = 2;
			offsety = -1;
			break;
		case DOWNRIGHT:
			currentAnimation = &idleAnimDownRight;
			break;
		case UPLEFT:
			currentAnimation = &idleAnimUpLeft;
			offsetx = 4;
			offsety = -1;
			break;
		case UPRIGHT:
			currentAnimation = &idleAnimUpRight;
			offsetx = -1;
			offsety = -1;
			break;
		}
	}
	else 
	{
		switch (bulletDir)
		{
		case LEFT:
			currentAnimation = &shootLeftAnim;
			offsetx = 7;
			offsety = -1;
			break;
		case RIGHT:
			currentAnimation = &shootRightAnim;
			offsetx = -4;
			break;
		case DOWN:
			currentAnimation = &shootDownAnim;
			break;
		case UP:
			currentAnimation = &shootUpAnim;
			break;
		case DOWNLEFT:
			currentAnimation = &shootDownLeftAnim;
			break;
		case DOWNRIGHT:
			currentAnimation = &shootDownRightAnim;
			break;
		case UPLEFT:
			currentAnimation = &shootUpLeftAnim;
			break;
		case UPRIGHT:
			currentAnimation = &shootUpRightAnim;
			break;
		}
	}
	// If no up/down movement detected, set the current animation back to idle

	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE &&
		isHurt == false)
	{
		switch (moveDir)
		{
		case LEFT:
			legAnimation = &idleAnimLeftLeg;

			break;
		case RIGHT:
			legAnimation = &idleAnimRightLeg;

			break;
		case DOWN:
			legAnimation = &idleAnimDownLeg;
			break;
		case UP:
			legAnimation = &idleAnimUpLeg;
			break;
		case DOWNLEFT:
			legAnimation = &idleAnimDownLeftLeg;
			break;
		case DOWNRIGHT:
			legAnimation = &idleAnimDownRightLeg;
			break;
		case UPLEFT:
			legAnimation = &idleAnimUpLeftLeg;
			break;
		case UPRIGHT:
			legAnimation = &idleAnimUpRightLeg;
			break;
		}
	}
}

void ModulePlayer::DodgeUpdate() 
{
	GamePad& pad = App->input->pads[0];
	if ((App->input->keys[SDL_SCANCODE_N] == Key_State::KEY_DOWN || pad.a == true) && dodgeCoolDown > 30 && isHurt == false && isThrowing == false && isDead == false && winCon == false)
	{
		dodgeCoolDown = 0;
		isDodging = true;
	}



	if (dodgeCoolDown < 25 /*&& rightLock == false && leftLock == false && downLock == false && upLock == false*/ && isDodging == true)
	{

		collider->SetPos(position.x + 20000, position.y + 20000);


		switch (moveDir)
		{
		case LEFT:
			if (!leftLock)
			{
				currentAnimation = &leftDodge;
				position.x -= speed * 3;
			}

			break;
		case RIGHT:

			if (!rightLock)
			{
				currentAnimation = &rightDodge;
				position.x += speed * 3;
			}

			break;
		case DOWN:
			if (!downLock)
			{
				currentAnimation = &downDodge;
				position.y += speed * 3;
			}

			break;
		case UP:

			if (!upLock)
			{
				currentAnimation = &upDodge;
				position.y -= speed * 3;
			}

			break;
		case DOWNLEFT:

			if (!downLock && !leftLock)
			{
				currentAnimation = &leftDownDodge;
				position.x -= speed * 2;
				position.y += speed * 2;
			}


			break;
		case DOWNRIGHT:

			if (!downLock && !rightLock)
			{
				currentAnimation = &rightDownDodge;
				position.x += speed * 2;
				position.y += speed * 2;
			}


			break;
		case UPLEFT:

			if (!upLock && !leftLock)
			{
				currentAnimation = &leftUpDodge;
				position.x -= speed * 2;
				position.y -= speed * 2;
			}


			break;
		case UPRIGHT:

			if (!upLock && !rightLock)
			{
				currentAnimation = &rightUpDodge;
				position.x += speed * 2;
				position.y -= speed * 2;
			}

			break;
		}
		shootCoolDown = 0;
	}
	else
	{
		collider->SetPos(position.x, position.y);


		isDodging = false;
	}

	if (isDodging)
	{
		legAnimation = &dissapear;
	}

	if (!isDodging)
	{
		upDodge.Reset();
		downDodge.Reset();
		leftDodge.Reset();
		rightDodge.Reset();
		rightUpDodge.Reset();
		leftUpDodge.Reset();
		rightDownDodge.Reset();
		leftDownDodge.Reset();
	}
}

void ModulePlayer::LoseWinLogicUpdate() 
{
	if (hp <= 0)
	{
		isDead = true;
	}

	if (isDead == true)
	{
		switch (moveDir)
		{
		case LEFT:
			currentAnimation = &deathleft;
			break;
		case RIGHT:
			currentAnimation = &deathright;
			break;
		case DOWN:
			currentAnimation = &deathback;
			break;
		case UP:
			currentAnimation = &deathfront;
			break;
		case DOWNLEFT:
			currentAnimation = &deathbackleft;
			break;
		case DOWNRIGHT:
			currentAnimation = &deathbackright;
			break;
		case UPLEFT:
			currentAnimation = &deathfrontleft;
			break;
		case UPRIGHT:
			currentAnimation = &deathfrontright;
			break;
		}

		legAnimation = &dissapear;
	}

	if (bigkill == 1 && App->render->cameraMode == 5) 
	{
		winCon = true;
	}

	if (isDead == true && currentAnimation->HasFinished() == true)
	{
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 90);
	}

	if (winCon == true)
	{
		currentAnimation = &Win;
		legAnimation = &dissapear;
		if (currentAnimation->HasFinished())
		{
			App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 90);
		}
	}

}

void ModulePlayer::GrenadeUpdate() 
{
	GamePad& pad = App->input->pads[0];
	if (App->input->keys[SDL_SCANCODE_M] == Key_State::KEY_DOWN || pad.b == true && isDodging == false && isDead == false && winCon == false) {
		isThrowing = true;
	}
	if (isThrowing == true && grenadeCoolDown > 40 && isDodging == false && grenadeCounter > 0)
	{
		switch (bulletDir)
		{
		case LEFT:
			App->particles->AddParticle(App->particles->Grenade, position.x, position.y, -2, -1, true, Collider::Type::NONE,0);
			
			App->particles->AddParticle(App->particles->grenade, position.x - 80, position.y - 50, 0, 0, true, Collider::Type::GRENADE, 20);
			App->particles->AddParticle(App->particles->grenade, position.x - 100, position.y - 80, 0, 0, true, Collider::Type::GRENADE, 30);
			App->particles->AddParticle(App->particles->grenade, position.x - 100, position.y - 30, 0, 0, true, Collider::Type::GRENADE, 30);
			App->particles->AddParticle(App->particles->grenade, position.x - 120, position.y - 100, 0, 0, true, Collider::Type::GRENADE, 40);
			App->particles->AddParticle(App->particles->grenade, position.x - 120, position.y, 0, 0, true, Collider::Type::GRENADE, 40);
			break;
		case RIGHT:
			App->particles->AddParticle(App->particles->Grenade, position.x, position.y, 2, -1, true, Collider::Type::NONE);

			App->particles->AddParticle(App->particles->grenade, position.x + 60, position.y - 50, 0, 0, true, Collider::Type::GRENADE, 20);
			App->particles->AddParticle(App->particles->grenade, position.x + 80, position.y - 80, 0, 0, true, Collider::Type::GRENADE, 30);
			App->particles->AddParticle(App->particles->grenade, position.x + 80, position.y - 30, 0, 0, true, Collider::Type::GRENADE, 30);
			App->particles->AddParticle(App->particles->grenade, position.x + 100, position.y - 100, 0, 0, true, Collider::Type::GRENADE, 40);
			App->particles->AddParticle(App->particles->grenade, position.x + 100, position.y, 0, 0, true, Collider::Type::GRENADE, 40);

			break;
		case DOWN:
			App->particles->AddParticle(App->particles->Grenade, position.x, position.y, 1, 3, true, Collider::Type::NONE);

			App->particles->AddParticle(App->particles->grenade, position.x, position.y + 20, 0, 0, true, Collider::Type::GRENADE, 20);
			App->particles->AddParticle(App->particles->grenade, position.x + 30, position.y + 30, 0, 0, true, Collider::Type::GRENADE, 30);
			App->particles->AddParticle(App->particles->grenade, position.x - 30, position.y + 30, 0, 0, true, Collider::Type::GRENADE, 30);
			App->particles->AddParticle(App->particles->grenade, position.x + 60, position.y + 40, 0, 0, true, Collider::Type::GRENADE, 40);
			App->particles->AddParticle(App->particles->grenade, position.x - 60, position.y + 40, 0, 0, true, Collider::Type::GRENADE, 40);
			break;
		case UP:
			App->particles->AddParticle(App->particles->Grenade, position.x, position.y, 1, -3, true, Collider::Type::NONE);

			App->particles->AddParticle(App->particles->grenade, position.x, position.y - 120, 0, 0, true, Collider::Type::GRENADE, 20);
			App->particles->AddParticle(App->particles->grenade, position.x + 30, position.y - 130, 0, 0, true, Collider::Type::GRENADE, 30);
			App->particles->AddParticle(App->particles->grenade, position.x - 30, position.y - 130, 0, 0, true, Collider::Type::GRENADE, 30);
			App->particles->AddParticle(App->particles->grenade, position.x + 60, position.y - 140, 0, 0, true, Collider::Type::GRENADE, 40);
			App->particles->AddParticle(App->particles->grenade, position.x - 60, position.y - 140, 0, 0, true, Collider::Type::GRENADE, 40);
			break;
		case DOWNLEFT:
			App->particles->AddParticle(App->particles->Grenade, position.x, position.y, -2, 2, true, Collider::Type::NONE);

			App->particles->AddParticle(App->particles->grenade, position.x - 40, position.y, 0, 0, true, Collider::Type::GRENADE, 20);
			App->particles->AddParticle(App->particles->grenade, position.x - 30, position.y + 20, 0, 0, true, Collider::Type::GRENADE, 30);
			App->particles->AddParticle(App->particles->grenade, position.x - 60, position.y - 30, 0, 0, true, Collider::Type::GRENADE, 30);
			App->particles->AddParticle(App->particles->grenade, position.x - 30, position.y + 40, 0, 0, true, Collider::Type::GRENADE, 40);
			App->particles->AddParticle(App->particles->grenade, position.x - 80, position.y - 40, 0, 0, true, Collider::Type::GRENADE, 40);
			break;
		case DOWNRIGHT:
			App->particles->AddParticle(App->particles->Grenade, position.x, position.y, 2, 2, true, Collider::Type::NONE);

			App->particles->AddParticle(App->particles->grenade, position.x + 40, position.y, 0, 0, true, Collider::Type::GRENADE, 20);
			App->particles->AddParticle(App->particles->grenade, position.x + 30, position.y + 20, 0, 0, true, Collider::Type::GRENADE, 30);
			App->particles->AddParticle(App->particles->grenade, position.x + 60, position.y - 30, 0, 0, true, Collider::Type::GRENADE, 30);
			App->particles->AddParticle(App->particles->grenade, position.x + 30, position.y + 40, 0, 0, true, Collider::Type::GRENADE, 40);
			App->particles->AddParticle(App->particles->grenade, position.x + 80, position.y - 40, 0, 0, true, Collider::Type::GRENADE, 40);

			break;
		case UPLEFT:
			App->particles->AddParticle(App->particles->Grenade, position.x, position.y, -2, -2, true, Collider::Type::NONE);

			App->particles->AddParticle(App->particles->grenade, position.x - 40, position.y - 109, 0, 0, true, Collider::Type::GRENADE, 20);
			App->particles->AddParticle(App->particles->grenade, position.x - 30, position.y - 109 - 20, 0, 0, true, Collider::Type::GRENADE, 30);
			App->particles->AddParticle(App->particles->grenade, position.x - 60, position.y - 109 + 30, 0, 0, true, Collider::Type::GRENADE, 30);
			App->particles->AddParticle(App->particles->grenade, position.x - 30, position.y - 109 - 40, 0, 0, true, Collider::Type::GRENADE, 40);
			App->particles->AddParticle(App->particles->grenade, position.x - 80, position.y - 109 + 40, 0, 0, true, Collider::Type::GRENADE, 40);
			break;
		case UPRIGHT:
			App->particles->AddParticle(App->particles->Grenade, position.x, position.y, 2, -2, true, Collider::Type::NONE);

			App->particles->AddParticle(App->particles->grenade, position.x + 40, position.y - 109, 0, 0, true, Collider::Type::GRENADE, 20);
			App->particles->AddParticle(App->particles->grenade, position.x + 30, position.y - 109 - 20, 0, 0, true, Collider::Type::GRENADE, 30);
			App->particles->AddParticle(App->particles->grenade, position.x + 60, position.y - 109 + 30, 0, 0, true, Collider::Type::GRENADE, 30);
			App->particles->AddParticle(App->particles->grenade, position.x + 30, position.y - 109 - 40, 0, 0, true, Collider::Type::GRENADE, 40);
			App->particles->AddParticle(App->particles->grenade, position.x + 80, position.y - 109 + 40, 0, 0, true, Collider::Type::GRENADE, 40);
			break;
		}
		grenadeCoolDown = 0;
		grenadeCounter--;
	}
	if (isThrowing == true && grenadeCounter > 0)
		switch (bulletDir)
		{
		case LEFT:
			currentAnimation = &grenadeThrowLeft;
			break;
		case RIGHT:
			currentAnimation = &grenadeThrowRight;
			break;
		case DOWN:
			currentAnimation = &grenadeThrowDown;
			break;
		case UP:
			currentAnimation = &grenadeThrowUp;
			break;
		case DOWNLEFT:
			currentAnimation = &grenadeThrowDownLeft;
			break;
		case DOWNRIGHT:
			currentAnimation = &grenadeThrowDownRight;
			break;
		case UPLEFT:
			currentAnimation = &grenadeThrowUpLeft;
			break;
		case UPRIGHT:
			currentAnimation = &grenadeThrowUpRight;
			break;
		}
	if (grenadeAnimationTimer >= 30) {
		isThrowing = false;
		grenadeThrowLeft.Reset();
		grenadeThrowRight.Reset();
		grenadeThrowUp.Reset();
		grenadeThrowDown.Reset();
		grenadeThrowDownRight.Reset();
		grenadeThrowDownLeft.Reset();
		grenadeThrowUpLeft.Reset();
		grenadeThrowUpRight.Reset();
		grenadeAnimationTimer = 0;
	}
}

void ModulePlayer::DebugLogicUpdate() 
{
	if (App->input->keys[SDL_SCANCODE_F2] == Key_State::KEY_DOWN)
	{
		if (godMode == false)
			godMode = true;
		else
			godMode = false;
	}

	if (App->input->keys[SDL_SCANCODE_F3] == Key_State::KEY_DOWN)
	{
		winCon = true;

	}

	if (App->UI->tpMenubool == true) 
	{
		if (App->input->keys[SDL_SCANCODE_1] == Key_State::KEY_DOWN)
		{
			App->player->position.x = 150;
			App->player->position.y = -1425;
			App->render->camera.x = 150;
			App->render->camera.y = -1425;
			App->render->cameraMode = 1;
		}
		if (App->input->keys[SDL_SCANCODE_2] == Key_State::KEY_DOWN)
		{
			App->player->position.x = 662;
			App->player->position.y = -1415;
			App->render->camera.x = 662;
			App->render->camera.y = -1415;
			App->render->cameraMode = 2;
		}
		if (App->input->keys[SDL_SCANCODE_3] == Key_State::KEY_DOWN)
		{
			App->player->position.x = 2210;
			App->player->position.y = -2278;
			App->render->camera.x = 2210;
			App->render->camera.y = -2278;
			App->render->cameraMode = 5;
		}
		if (App->input->keys[SDL_SCANCODE_4] == Key_State::KEY_DOWN)
		{
			App->player->position.x = 1285;
			App->player->position.y = -1400;
			App->render->camera.x = 1285;
			App->render->camera.y = -1400;
			App->render->cameraMode = 4;
		}
		if (App->input->keys[SDL_SCANCODE_5] == Key_State::KEY_DOWN)
		{
			App->player->position.x = 2280;
			App->player->position.y = -1434;
			App->render->camera.x = 2280;
			App->render->camera.y = -1443;
			App->render->cameraMode = 5;
		}
		if (App->input->keys[SDL_SCANCODE_6] == Key_State::KEY_DOWN)
		{
			App->player->position.x = 2223;
			App->player->position.y = -3024;
			App->render->camera.x = 2223;
			App->render->camera.y = -3024;
			App->render->cameraMode = 5;
		}
	}


	if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN)
	{
		hp = 0;
	}
	if (App->input->keys[SDL_SCANCODE_F6] == Key_State::KEY_DOWN)
	{
		App->render->cameraMode++;
	}

	if (App->input->keys[SDL_SCANCODE_F7] == Key_State::KEY_DOWN)
	{
		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, position.x, position.y- 40);

	}
}

void ModulePlayer::HurtUpdate() 
{
	if (isHurt == true && isDead == false && winCon == false)
	{
		switch (moveDir)
		{
		case LEFT:
			currentAnimation = &Hurtleft;

			break;
		case RIGHT:
			currentAnimation = &Hurtright;

			break;
		case DOWN:
			currentAnimation = &Hurtdown;

			break;
		case UP:
			currentAnimation = &Hurtup;

			break;
		case DOWNLEFT:
			currentAnimation = &Hurtdownleft;

			break;
		case DOWNRIGHT:
			currentAnimation = &Hurtdownright;
			break;
		case UPLEFT:
			currentAnimation = &Hurtupleft;

			break;
		case UPRIGHT:
			currentAnimation = &Hurtupright;
			break;
		}
		if (hurtDuration > 45)
		{
			isHurt = false;
			Hurtleft.Reset();
			Hurtright.Reset();
			Hurtdown.Reset();
			Hurtup.Reset();
			Hurtdownleft.Reset();
			Hurtdownright.Reset();
			Hurtupleft.Reset();
			Hurtupright.Reset();
		}
		legAnimation = &dissapear;
	}
	
	if (hurtDuration == 120) 
	{
		invincible = false;
	}
	
	if (hurtDuration > 45 && hurtDuration < 120 && hurtDuration % 2 != 0 && invincible == true)
	{
		legAnimation = &dissapear;
		currentAnimation = &dissapear;
	}

	if (hp > maxHp) 
	{
		hp = maxHp;
	}

}

Update_Status ModulePlayer::Update()
{
	shootCoolDown++;
	dodgeCoolDown++;
	hurtDuration++;
	grenadeCoolDown++;
	timerCounter++;

	if (isThrowing == true) { grenadeAnimationTimer++; }

	GamepadUpdate();
	MoveUpdate();
	ShootingUpdate();
	AnimationLegTorsoUpdate();
	DodgeUpdate();

	//Update collider positions
	colliderUp->SetPos(position.x , position.y + 40);
	colliderDown->SetPos(position.x, position.y + 47);
	colliderRight->SetPos(position.x + 32, position.y + 43);
	colliderLeft->SetPos(position.x - 3, position.y + 43);

	//Turn off wall collisions for next tick to check if there is a collision
	rightLock = false;
	leftLock = false;
	downLock = false;
	upLock = false;

	LoseWinLogicUpdate();
	GrenadeUpdate();
	DebugLogicUpdate();
	HurtUpdate();

	
	currentAnimation->Update();
	legAnimation->Update();

	//Timer
	if (timerCounter == 240)
	{
		timerCounter = 0;
		if (timer != 0)
		{
			timer--;
		}
	}
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{

		SDL_Rect rectLeg = legAnimation->GetCurrentFrame();
		bool mirrorLeg = legAnimation->GetMirror();

		if (mirrorLeg == true)
		{
			App->render->BlitMirror(texture, position.x + offsetx, position.y + 20 + offsety, &rectLeg);
			offsetx = 0;
			offsety = 0;
		}
		else
		{
			App->render->Blit(texture, position.x + offsetx, position.y + 20 + offsety, &rectLeg);
			offsetx = 0;
			offsety = 0;
		}

		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		bool mirror = currentAnimation->GetMirror();

		if (mirror == true)
		{
			App->render->BlitMirror(texture, position.x + offsetx2, position.y + offsety2, &rect);
			offsetx2 = 0;
			offsety2 = 0;

		}
		else
		{
			App->render->Blit(texture, position.x + offsetx2, position.y + offsety2, &rect);
			offsetx2 = 0;
			offsety2 = 0;
		}
	}
	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{


	if (c1->type == Collider::Type::UP_PLAYER && (c2->type == Collider::Type::WALL || c2->type == Collider::Type::ENEMY) && App->render->freeCam == false)
	{
		upLock = true;
		if (isDodging && moveDir != LEFT && moveDir != RIGHT)
		{
			App->input->keys[SDL_SCANCODE_W] = Key_State::KEY_IDLE;
			isDodging = false;
			legAnimation = &upAnimLeg;
		}
			

		//isDodging = false;
	}

	if (c1->type == Collider::Type::DOWN_PLAYER && (c2->type == Collider::Type::WALL || c2->type == Collider::Type::ENEMY) && App->render->freeCam == false)
	{
		downLock = true;
		if (isDodging && moveDir != LEFT && moveDir != RIGHT)
		{
			App->input->keys[SDL_SCANCODE_S] = Key_State::KEY_IDLE;
			isDodging = false;
			legAnimation = &downAnimLeg;
		}

		//isDodging = false;
	}

	if (c1->type == Collider::Type::RIGHT_PLAYER && (c2->type == Collider::Type::WALL || c2->type == Collider::Type::ENEMY) && App->render->freeCam == false)
	{
		rightLock = true;
		if (isDodging && moveDir != UP && moveDir != DOWN)
		{
			App->input->keys[SDL_SCANCODE_D] = Key_State::KEY_IDLE;
			isDodging = false;
			legAnimation = &rightAnimLeg;
		}

		//isDodging = false;
	}

	if (c1->type == Collider::Type::LEFT_PLAYER && (c2->type == Collider::Type::WALL || c2->type == Collider::Type::ENEMY) && App->render->freeCam == false)
	{
		leftLock = true;
		if (isDodging && moveDir != UP && moveDir != DOWN)
		{
			App->input->keys[SDL_SCANCODE_A] = Key_State::KEY_IDLE;
			isDodging = false;
			legAnimation = &leftAnimLeg;
		}

		//isDodging = false;
	}


	if (c1->type == Collider::Type::PLAYER && (c2->type == Collider::Type::ENEMY_SHOT || c2->type == Collider::Type::MISSILE) && godMode == false && invincible == false && isDead == false && winCon == false)
	{
		App->audio->PlayFx(milkyhurtvoice);
		hp -= 22;
		isHurt = true;
		invincible = true;
		hurtDuration = 0;
	
	}
}
