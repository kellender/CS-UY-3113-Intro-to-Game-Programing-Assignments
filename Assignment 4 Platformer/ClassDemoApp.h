#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Entity.h"
#include "GameState.h"

#ifndef CLASSDEMOAPP_H
#define CLASSDEMOAPP_H

class Plat{
public:
	Plat();
	~Plat();

	void Init();
	bool UpdateAndRender();

	void Render();
	void Update();
private:
	int jumped;
	int enemyCount;
	void createEnemy();
	const Uint8* keys;
	bool done;
	float animation;
	GameState state;
	float lastFrameTicks;
	SDL_Window* displayWindow;
	GLuint font;

	Entity blocks[10];
	Entity enemy[25];
	int enemysize;
	float gravity;

	void reset();

	void RenderMainMenu();
	void RenderGameLevel();
	void RenderGameOver();

	void UpdateGameLevel();

	bool bumprightwall();
	bool bumpleftwall();
	float delay;
	Entity user;

	int score;
};
#endif