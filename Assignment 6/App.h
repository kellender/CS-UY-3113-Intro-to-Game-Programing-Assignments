#pragma once
#include "include.h"
#include "Vector.h"
#include "Matrix.h"
#include "Entity.h"

#define FIXED_TIMESTEP 0.0166666f
#define MAX_TIMESTEPS 6
#define ASTEROIDS 6


using namespace std;




class App{
public:
	App();
	~App();

	void Init();
	bool UpdateAndRender();

	void Render();
	void Update(float elapsed);
private:
	const Uint8* keys;
	bool done;
	float lastFrameTicks;
	SDL_Window* displayWindow;

	Mix_Music* music;

	Entity asteroid[ASTEROIDS];
	int enemysize;

	void reset();

	void RenderGameLevel();

	bool bumprightwall();
	bool bumpleftwall();
	Entity user;

};