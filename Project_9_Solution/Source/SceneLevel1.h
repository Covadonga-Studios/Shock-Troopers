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

private: 
	Animation door;
	Animation helicopterArriving;
	Animation* currentAnimation;
	
};

#endif