#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Entity.h"
#include "Bullet.h"
#include "GameState.h"

#ifndef CLASSDEMOAPP_H
#define CLASSDEMOAPP_H

class SpInvd{
public:
	SpInvd();
	~SpInvd();

	void Init();
	bool UpdateAndRender();

	void Render();
	void Update(float elapsed);
private:
	const Uint8* keys;
	bool done;
	GameState state;
	float lastFrameTicks;
	SDL_Window* displayWindow;
	GLuint font;

	Entity enemyOne[10];
	Entity enemyTwo[10];
	Entity enemyThree[10];
	Entity enemyFour[10];


	int numEnemy;

	void reset();

	void RenderMainMenu();
	void RenderGame();
	void RenderGameOver();

	void UpdateGameLevel(float elapsed);

	bool bumprightwall();
	bool bumpleftwall();
	float delay;
	Entity user;

	bool userhit();
	bool eachuserhit(Entity enemy);
	float userhitdelay;
	bool enemyhit(Entity enemy);


	int score;
	int lives;

};
#endif