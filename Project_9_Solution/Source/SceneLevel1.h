#ifndef __SCENE_LEVEL1_H__
#define __SCENE_LEVEL1_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneLevel1 : public Module
{
public:
	//Constructor
	SceneLevel1(bool startEnabled);

	//Destructor
	~SceneLevel1();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

	// Disables the player and the enemies
	bool CleanUp();

public:
	
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* bgTexture2 = nullptr;
	SDL_Texture* bgTexture3 = nullptr;
	SDL_Texture* bridgebg = nullptr;
	SDL_Texture* defaultspritesheet = nullptr;
	SDL_Texture* defaultspritesheet2 = nullptr;
	
	Collider* collider = nullptr;
	int offsetheli = 0;
	bool helispawn = false;
	bool doorspawn = false;
	bool wave1 = false;
	bool wave2 = false;
	bool wave3 = false;
	bool wave4 = false;
	bool wave5 = false;
	bool wave6 = false;
	bool wave7 = false;
	bool wave8 = false;
	bool wave9 = false;
	bool wave10 = false;
	bool wave11 = false;
	bool wave12 = false;
	bool wave13 = false;
	bool wave14 = false;
	bool wave15 = false;
	bool wave16 = false;
	bool wave17 = false;
	bool wave18 = false;
	bool wave19 = false;
	bool wave20 = false;
	bool wave21 = false;
	bool wave22 = false;
	bool wave23 = false;


private: 
	Animation door;
	Animation helicopterArriving;
	Animation* currentAnimation;
	
};

#endif