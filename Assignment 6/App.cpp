#pragma once
#include "App.h"
#include "include.h"
#include "Vector.h"
#include "Matrix.h"
#include "Entity.h"

using namespace std;
float timeLeftOver = 0.0f;

bool collision(Entity &a, Entity b){
	Vector a1 = a.matrix * a.topleft;
	a1 = b.inverse * a1;
	Vector b1 = a.matrix * a.topright;
	b1 = b.inverse * b1;
	Vector c1 = a.matrix * a.bottomleft;
	c1 = b.inverse * c1;
	Vector d1 = a.matrix * a.bottomright;
	d1 = b.inverse * d1;

	Vector a2 = b.matrix * b.topleft;
	a2 = a.inverse * a2;
	Vector b2 = b.matrix * b.topright;
	b2 = a.inverse * b2;
	Vector c2 = b.matrix * b.bottomleft;
	c2 = a.inverse * c2;	
	Vector d2 = b.matrix * b.bottomright;
	d2 = a.inverse * d2;


	float smallx1 = min(min(a1.x, b1.x), min(c1.x, d1.x));
	float highx1 = max(max(a1.x, b1.x), max(c1.x, d1.x));
	float smally1 = min(min(a1.y, b1.y), min(c1.y, d1.y));
	float highy1 = max(max(a1.y, b1.y), max(c1.y, d1.y));

	float smallx2 = min(min(a2.x, b2.x), min(c2.x, d2.x));
	float highx2 = max(max(a2.x, b2.x), max(c2.x, d2.x));
	float smally2 = min(min(a2.y, b2.y), min(c2.y, d2.y));
	float highy2 = max(max(a2.y, b2.y), max(c2.y, d2.y));

	if (smallx1 <= b.right && highx1 >= b.left && smally1 <= b.top && highy1 >= b.bottom &&
		smallx2 <= a.right && highx2 >= a.left && smally2 <= a.top && highy2 >= a.bottom){

		float amount = 0.02f;
		if (a.x < b.x){
			a.x -= amount;
			if (a.y < b.y){
				a.y -= amount;
			}
			else if (a.y > b.y){
				a.y += amount;
			}
		}
		else if (a.x > b.x){
			a.x += amount;
			if (a.y < b.y){
				a.y -= amount;
			}
			else if (a.y > b.y){
				a.y += amount;
			}
		}
		else {
			if (a.y < b.y){
				a.y -= amount;
			}
			else if (a.y > b.y){
				a.y += amount;
			}
		}

		return true;
	}

	return false;
}

GLuint LoadTexture(const char *image_path, GLenum format) {
	SDL_Surface *surface = IMG_Load(image_path);

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, 4, surface->w, surface->h, 0, format, GL_UNSIGNED_BYTE, surface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SDL_FreeSurface(surface);

	return textureID;
}

void App::reset(){
	Mix_PlayMusic(music, 0);

	GLuint SheetSpriteTexture = LoadTexture("sheet.png", GL_RGBA);

	user = Entity(SheetSpriteTexture, 777.0f / 1024.0f, 712.0f / 1024.0f, 32.0f / 1024.0f, 26.0 / 1024.0f, 2.0f, 2.0f);

	user.x = 0.0f;
	user.y = -0.8f;

	//float xtemp = 0.3325f - 1.33f;
	for (int i = 0; i < ASTEROIDS; i++){
		asteroid[i] = Entity(SheetSpriteTexture, 224.0f / 1024.0f, 748.0f / 1024.0f, 101.0f / 1024.0f, 84.0 / 1024.0f, 1.0f, 1.0f);
		//asteroid[i].x = xtemp + i*0.665f;
		asteroid[i].x = (float)rand() / (float)RAND_MAX*2.66f - 1.33f;
		asteroid[i].y = (float)rand() / (float)RAND_MAX*2.0f - 1.0f;
		//asteroid[i].y = user.y + 0.15f;

		asteroid[i].randomize();
	}
}

App::App() {
	Init();

	keys = SDL_GetKeyboardState(NULL);

	glViewport(0, 0, 800, 600);
	glMatrixMode(GL_PROJECTION);
	//glOrtho(-1.33, 1.33, -1.0, 1.0, -1.0, 1.0);
	Matrix start(0.752f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.5f, 0.5f,
		0.0f, 0.0f, 0.0f, 1.0f);
	glMultMatrixf(start.ml);
	//glPushMatrix();

	done = false;
	lastFrameTicks = 0.0f;
	enemysize = 12;

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2096);
	music = Mix_LoadMUS("DarkMateria - The Worf Song.mp3");// thx to http://www.last.fm/music/DarkMateria/_/Frame+of+Mind for the music

	glMatrixMode(GL_MODELVIEW);
	Matrix initial;
	glLoadMatrixf(initial.ml);
	reset();

}

void App::Init() {
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);

}

App::~App() {
	Mix_FreeMusic(music);
	SDL_Quit();
}

void App::Render() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glClear(GL_COLOR_BUFFER_BIT);
	RenderGameLevel();
	SDL_GL_SwapWindow(displayWindow);
}

void App::RenderGameLevel(){

	user.draw();

	for (int i = 0; i < ASTEROIDS; i++){
		asteroid[i].draw();
	}

}


void App::Update(float elapsed) {
	for (int i = 0; i < ASTEROIDS; i++){
		collision(asteroid[i], user);
	}


	if (user.x < -1.53f){
		user.x = -user.x - 0.15f;
	}
	else if (user.x > 1.53f){
		user.x = -user.x + 0.15f;
	}
	if (user.y < -1.2f){
		user.y = -user.y - 0.15f;
	}
	else if (user.y > 1.2f){
		user.y = -user.y + 0.15f;
	}


	user.genMatrix();
	user.setVector();

	for (int i = 0; i < ASTEROIDS; i++){
		if (asteroid[i].x < -1.53f){
			asteroid[i].x = -asteroid[i].x - 0.15f;
		}
		else if (asteroid[i].x > 1.53f){
			asteroid[i].x = -asteroid[i].x + 0.15f;
		}

		if (asteroid[i].y < -1.2f){
			asteroid[i].y = -asteroid[i].y - 0.15f;
		}
		else if (asteroid[i].y > 1.2f){
			asteroid[i].y = -asteroid[i].y + 0.15f;
		}

		asteroid[i].x += asteroid[i].vector.x * elapsed;
		asteroid[i].y += asteroid[i].vector.y * elapsed;

		asteroid[i].genMatrix();
	}





	if (keys[SDL_SCANCODE_LEFT]){
		/*
		if (user.x - user.width*user.scalex > -1.33){
		user.x -= 0.75f * elapsed;
		}*/
		user.rotation += 2.5f * elapsed;
	}
	else if (keys[SDL_SCANCODE_RIGHT]){
		/*
		if (user.x + user.width*user.scalex < 1.33){
		user.x += 0.75f * elapsed;
		}*/
		user.rotation -= 2.5f * elapsed;
	}

	if (keys[SDL_SCANCODE_UP]){
		user.x += 0.75f * user.vector.x * elapsed;
		user.y += 0.75f * user.vector.y * elapsed;
	}
	else if (keys[SDL_SCANCODE_DOWN]){
		user.x -= 0.5f * user.vector.x * elapsed;
		user.y -= 0.5f * user.vector.y * elapsed;
	}

	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
			done = true;
		}



	}
}


bool App::UpdateAndRender() {
	//float ticks = (float)SDL_GetTicks() / 1000.0f;
	//float elapsed = ticks - lastFrameTicks;
	//lastFrameTicks = ticks;
	//Update(elapsed);
	//Render();

	float ticks = (float)SDL_GetTicks() / 1000.0f;
	float elapsed = ticks - lastFrameTicks;
	lastFrameTicks = ticks;

	float fixedElapsed = elapsed + timeLeftOver;
	if (fixedElapsed > FIXED_TIMESTEP * MAX_TIMESTEPS){
		fixedElapsed = FIXED_TIMESTEP * MAX_TIMESTEPS;
	}

	while (fixedElapsed >= FIXED_TIMESTEP){
		fixedElapsed -= FIXED_TIMESTEP;
		Update(FIXED_TIMESTEP);
		elapsed -= FIXED_TIMESTEP;
	}
	timeLeftOver = fixedElapsed;
	Render();

	return done;
}