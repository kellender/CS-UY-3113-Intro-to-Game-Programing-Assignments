#pragma once
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

SDL_Window* displayWindow;

//look freinds!!!
enum GameState { STATE_MAIN_MENU, STATE_GAME_LEVEL, STATE_GAME_OVER };


#define FIXED_TIMESTEP 0.0166666f
#define MAX_TIMESTEPS 6
#define TOTAL_ENEMIES 15

#define SPRITE_COUNT_X 13
#define SPRITE_COUNT_Y 8

#define TILE_WIDTH 0.3f
#define TILE_HEIGHT 0.3f
float timeLeftOver = 0.0f;
#define TOTAL_ENEMIES 15
#define TOTAL_PRIZES 2
