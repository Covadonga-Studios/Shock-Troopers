#pragma once
#include "Module.h"
#include "Animation.h"

struct SDL_Texture;


class ModuleUI : public Module
{
public:
	
	//Constructor
	ModuleUI(bool startEnabled);


	//Destructor
	~ModuleUI();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	Update_Status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	Update_Status PostUpdate() override;

public:


	// The UI spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;

	
	//Create a chunk of 8 HP for the HP bar
	struct HPBarChunk
	{
		Animation hp8;
		Animation hp7;
		Animation hp6;
		Animation hp5;
		Animation hp4;
		Animation hp3;
		Animation hp2;
		Animation hp1;
		Animation hp0;
		Animation* hpState = nullptr;
		SDL_Rect hpRect;
	};
	//the total HP bar is an array of 16 chunks
	HPBarChunk HPBar[16];
	SDL_Rect hpRectUp;
	SDL_Rect hpRectDown;


	//Score
	int scoreFont = -1;
	char scoreText[10] = { "\0" };

	//Timer
	int timerFont = -1;
	int timerCounter = 0;
	char timerText[10] = { "\0" };
	SDL_Rect timerRect;
};