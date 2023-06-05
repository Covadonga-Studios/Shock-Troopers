#pragma once
#ifndef __CHARACTER_SCREEN_H__
#define __CHARACTER_SCREEN_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class CharacterScreen: public Module
{
public:
	//Constructor
	CharacterScreen(bool startEnabled);

	//Destructor
	~CharacterScreen();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

public:
	int timerpass;
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture2 = nullptr;
	SDL_Texture* bgTexture3 = nullptr;
	SDL_Texture* boxTexture = nullptr;

	uint selectFx = 0;
	uint acceptFx = 0;

	int boxx = 136;
	int boxy = 30;

	bool canPass = false;
};

#endif