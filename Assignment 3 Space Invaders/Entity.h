#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "Bullet.h"

#ifndef Entity_H
#define Entity_H

class Entity{
public:
	void draw(float stretch = 1.0f);
	void render();

	GLuint textureID;

	float u;
	float v;
	float scale;

	float x;
	float y;

	float width;
	float height;

	float d_x;
	float d_y;

	float waittime;

	bool alive;
	bool shot;

	Bullet bullet;
	Entity(){};
	Entity(GLuint textureID, float u, float v, float width, float height, float scale);
};
#endif